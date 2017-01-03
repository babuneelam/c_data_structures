#include <stdio.h>
#include <stdlib.h>

#define NO_MORE -1

typedef struct Q_node {
    struct Q_node *next;
    int val; // int declared here, but change date type as necessary
} Q_node_t;

typedef struct Q_head {
    Q_node_t *head;
    Q_node_t *tail;
    int cur_sz; // can be avoided, just for stats
} Q_head_t;

Q_head_t *Q_head;

Q_head_t *Q_init(void);
int Q_enqueue(Q_head_t *, int);
Q_node_t *Q_dequeue(Q_head_t *);
Q_node_t *Q_top(Q_head_t *);
int Q_is_empty(Q_head_t *);
int Q_is_full(Q_head_t *);
void Q_display(Q_head_t *);
void Q_free(Q_head_t *);

char help_str[] = "Allowed Operations: \n"
    "	-1 - Exit\r\n"
    "	 1 - print help(this list)\r\n"
    "	 2 <ele> - Enqueue ele\r\n"
    "	 3 - Dequeue ele\r\n"
    "	 4 - Peek Q\r\n"
    "	 5 - Is Queue Empty?\r\n"
    "	 6 - Is Queue Full?\r\n"
    "	 7 - display list\r\n"
    ;

int main()
{
    Q_node_t *n;
    int op, val;
    int empty, full;

    Q_head = Q_init();
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
                Q_enqueue(Q_head, val);
                break;
            case 3: /*Dequeue*/
                n = Q_dequeue(Q_head);
		if (n)
		    printf("Ele Dequeued: %d \r\n", n->val);
		free(n);
                break;
            case 4: /*Peek*/
                n = Q_top(Q_head);
		if (n)
		    printf("Q next dequeue ele: %d \r\n", n->val);
                break;
            case 5: /* Queue empty?*/
                empty = Q_is_empty(Q_head);
                if (empty)
                    printf("Queue is empty\r\n");
                else
                    printf("Queue is not empty\r\n");
                break;
            case 6: /* Is queue full? */
                full = Q_is_full(Q_head);
                if (full)
                    printf("Queue is full\r\n");
                else
                    printf("Queue is not full\r\n");
                break;
                break;
            case 7: /* display queue elements without Dequeueing any */
                Q_display(Q_head);
                break;
            default: /*error */
                printf("Invalid operation\r\n");
                break;
        }
        scanf("%d", &op);
    }

    Q_display(Q_head);
    Q_free(Q_head);
    Q_head=NULL;

    return 0;
}

Q_head_t *Q_init(void)
{
    Q_head_t *q;

    q = (Q_head_t *)calloc(1, sizeof(struct Q_head));
    return q;
}

int Q_enqueue(Q_head_t *Q, int val)
{
    Q_node_t *n;

    if (!Q)
        return -1;

    n = (Q_node_t *)malloc(sizeof(struct Q_node));
    if (!n)
    {
	printf("Queue node Allocation failure \r\n");
	return -1;
    }
    n->val = val;
    n->next = NULL;
    if (Q->tail) {
	Q->tail->next = n;
	Q->tail = n;
    } else 
	Q->head = Q->tail = n;
    Q->cur_sz++;

    return 0;
}

Q_node_t *Q_dequeue(Q_head_t *Q)
{
    Q_node_t *n;

    if (Q_is_empty(Q)) //Q null check done in Q_is_empty
	return NULL;

    n = Q->head;
    Q->head= n->next;
    if (Q->tail == n)
	Q->tail = NULL;
    Q->cur_sz--;
    // Node not freed, caller expected to free the node.
    return n;
}

Q_node_t *Q_top(Q_head_t *Q)
{
    if (!Q)
	return NULL;
    return Q->head;
}

int Q_is_empty(Q_head_t *Q)
{
    if (!Q)
        return 0; // 0 returned so callers do no processing further
		  // returing an error code requires additional processing
		  // at the callers
    return (Q->head ? 0 : 1);
}

int Q_is_full(Q_head_t *Q)
{
    return 0; // FALSE always as linked list implementation
	      // doesn't have a size limitation
}

void Q_display(Q_head_t *Q)
{
    Q_node_t *n;

    if (!Q)
        return;
    printf("List elements: \r\n");
    if (!Q->head )
        return;

    n=Q->head;
    while (n)
    {
	printf("%d ", n->val);
	n=n->next;
    }
    printf("\n");
}

void Q_free(Q_head_t *Q)
{
    Q_node_t *cur,*nxt;

    if (!Q)
        return;
    cur=Q->head;
    while (cur)
    {
	nxt=cur->next;
	free(cur);
	cur=nxt;
    }
    free(Q);
}


