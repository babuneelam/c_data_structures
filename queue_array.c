#include <stdio.h>
#include <stdlib.h>

#define NO_MORE -1
#define MAX_Q_SZ 100

typedef struct Q {
    int data[MAX_Q_SZ]; // int declared here, but change date type as necessary
    int head; // read data & the move head
    int tail; // write data first & then move tail
    int cur_sz; // helps differentiate between empty & full Q status
} Q_t;

Q_t *Q;

Q_t *Q_init(void);
int Q_push(Q_t *, int);
int Q_pop(Q_t *); // return type is Q element type, here int
int Q_top(Q_t *); // return type is Q element type, here int
int Q_is_empty(Q_t *);
int Q_is_full(Q_t *);
void Q_display(Q_t *);
void Q_free(Q_t *);

char help_str[] = "Max Queue Size is 100. Allowed Operations: \n"
    "	-1 - Exit\r\n"
    "	 1 - print help(this list)\r\n"
    "	 2 <ele> - Enqueue ele\r\n"
    "	 3 - Dequeue ele\r\n"
    "	 4 - Peek/Top Queue ele\r\n"
    "	 5 - Is Queue Empty?\r\n"
    "	 6 - Is Queue Full?\r\n"
    "	 7 - display list\r\n"
    ;

int main()
{
    int op, val, n;
    int empty, full;

    Q = Q_init();
    printf("%s",help_str);
    scanf("%d", &op);
    while(op != NO_MORE)
    {
        switch(op)
        {
	    case 1:
    		printf("%s",help_str);
                break;
            case 2: /*Enqueue*/
                scanf("%d", &val);
                Q_enqueue(Q, val);
                break;
            case 3: /*Dequeue*/
                n = Q_dequeue(Q);
		if (n >=0 )
		    printf("Ele Dequeued: %d \r\n", n);
                break;
            case 4: /*Top/Peek*/
                n = Q_top(Q);
		if (n >= 0)
		    printf("Queue Top ele: %d \r\n", n);
                break;
            case 5: /* Queue empty?*/
                empty = Q_is_empty(Q);
                if (empty)
                    printf("Queue is empty\r\n");
                else
                    printf("Queue is not empty\r\n");
                break;
            case 6: /* Is Q full? */
                full = Q_is_full(Q);
                if (full)
                    printf("Queue is full\r\n");
                else
                    printf("Queue is not full\r\n");
                break;
                break;
            case 7: /* display Q elements without popping any */
                Q_display(Q);
                break;
            default: /*error */
                printf("Invalid operation\r\n");
                break;
        }
        scanf("%d", &op);
    }

    Q_display(Q);
    Q_free(Q);
    Q=NULL;

    return 0;
}

Q_t *Q_init(void)
{
    Q_t *s;

    s = (Q_t *)calloc(1, sizeof(struct Q));
    return s;
}

int Q_enqueue(Q_t *Q, int val)
{
    if (Q_is_full(Q))
    {
	printf("Queue size exceeded \r\n");
	return (-1);
    }
    Q->data[Q->tail]=val;
    if (++Q->tail == MAX_Q_SZ) // Move tail after writing data
	Q->tail=0;  // wrap around
    Q->cur_sz++;
    return 0;
}

int Q_dequeue(Q_t *Q)
{
    int n;

    if (Q_is_empty(Q))
	return (-1); 
	// TBD: what to return when empty? Assumed that 
	// Q elements are > 0.

    n = Q->data[Q->head]; // read data before moving head
    if (++Q->head == MAX_Q_SZ)
	Q->head =0;  // reset to the array beginning
    Q->cur_sz--;
    return n;
}

int Q_top(Q_t *Q)
{
    return (Q_is_empty(Q) ? -1: Q->data[Q->head] );
}

int Q_is_empty(Q_t *Q)
{
    return (Q->cur_sz ? 0 : 1);
}

int Q_is_full(Q_t *Q)
{
    return ((Q->cur_sz >= MAX_Q_SZ) ? 1 : 0);
}

void Q_display(Q_t *Q)
{
    int i, cnt;

    printf("List elements: \r\n");
    if (!Q->cur_sz)
        return;

    for(i=Q->head, cnt=1; cnt <= Q->cur_sz; i++, cnt++)
    {
        if (i == MAX_Q_SZ)
	    i=0;
	printf("%d ", Q->data[i]);
    }
    printf("\n");
}

void Q_free(Q_t *Q)
{
    free(Q);
}


