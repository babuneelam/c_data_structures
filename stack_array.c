#include <stdio.h>
#include <stdlib.h>

#define NO_MORE -1
#define MAX_STK_SZ 100

typedef struct STK {
    int stk[MAX_STK_SZ]; // int declared here, but change date type as necessary
    int top;
} STK_t;

STK_t *STK;

STK_t *stk_init(void);
int stk_push(STK_t *, int);
int stk_pop(STK_t *); // return type is stack element type, here int
int stk_top(STK_t *); // return type is stack element type, here int
int stk_is_empty(STK_t *);
int stk_is_full(STK_t *);
void stk_display(STK_t *);
void stk_free(STK_t *);

char help_str[] = "Max Stack Size is 100. Allowed Operations: \n"
    "	-1 - Exit\r\n"
    "	 1 - print help(this list)\r\n"
    "	 2 <ele> - Push ele\r\n"
    "	 3 - Pop ele\r\n"
    "	 4 - Peek/Top Stack ele\r\n"
    "	 5 - Is Stack Empty?\r\n"
    "	 6 - Is Stack Full?\r\n"
    "	 7 - display list\r\n"
    ;

int main()
{
    int op, val, n;
    int empty, full;

    STK = stk_init();
    printf("%s",help_str);
    scanf("%d", &op);
    while(op != NO_MORE)
    {
        switch(op)
        {
	    case 1:
    		printf("%s",help_str);
                break;
            case 2: /*Push*/
                scanf("%d", &val);
                stk_push(STK, val);
                break;
            case 3: /*Pop*/
                n = stk_pop(STK);
		if (n >=0 )
		    printf("Ele popped: %d \r\n", n);
                break;
            case 4: /*Top*/
                n = stk_top(STK);
		if (n >= 0)
		    printf("Top ele: %d \r\n", n);
                break;
            case 5: /* Stack empty?*/
                empty = stk_is_empty(STK);
                if (empty)
                    printf("Stack is empty\r\n");
                else
                    printf("Stack is not empty\r\n");
                break;
            case 6: /* Is stack full? */
                full = stk_is_full(STK);
                if (full)
                    printf("Stack is full\r\n");
                else
                    printf("Stack is not full\r\n");
                break;
                break;
            case 7: /* display stack elements without popping any */
                stk_display(STK);
                break;
            default: /*error */
                printf("Invalid operation\r\n");
                break;
        }
        scanf("%d", &op);
    }

    stk_display(STK);
    stk_free(STK);
    STK=NULL;

    return 0;
}

STK_t *stk_init(void)
{
    STK_t *s;

    s = (STK_t *)calloc(1, sizeof(struct STK));
    return s;
}

int stk_push(STK_t *stk, int val)
{
    if (stk_is_full(stk))
    {
	printf("Stack size exceeded \r\n");
	return (-1);
    }
    stk->stk[stk->top++]=val;
    return 0;
}

int stk_pop(STK_t *stk)
{
    return (stk_is_empty(stk) ? -1 : stk->stk[--stk->top] );
	// TBD: what to return when empty? Assumed that 
	// stack elements are > 0.
}

int stk_top(STK_t *stk)
{
    return (stk_is_empty(stk) ? -1: stk->stk[stk->top-1] );
}

int stk_is_empty(STK_t *stk)
{
    return (stk->top ? 0 : 1);
}

int stk_is_full(STK_t *stk)
{
    return ((stk->top >= MAX_STK_SZ) ? 1 : 0);
}

void stk_display(STK_t *stk)
{
    int i;

    printf("List elements: \r\n");
    if (!stk->top)
        return;

    for(i=stk->top-1; i>=0; i--)
	printf("%d ", stk->stk[i]);
    printf("\n");
}

void stk_free(STK_t *stk)
{
    free(stk);
}


