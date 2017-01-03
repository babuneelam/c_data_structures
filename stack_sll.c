#include <stdio.h>
#include <stdlib.h>

#define NO_MORE -1

typedef struct stk_node {
    struct stk_node *next;
    int val; // int declared here, but change date type as necessary
} stk_node_t;

typedef struct STK {
    stk_node_t *top;
    int cur_sz; // can be avoided, just for stats
} STK_t;

STK_t *STK;

STK_t *stk_init(void);
int stk_push(STK_t *, int);
stk_node_t *stk_pop(STK_t *);
stk_node_t *stk_top(STK_t *);
int stk_is_empty(STK_t *);
int stk_is_full(STK_t *);
void stk_display(STK_t *);
void stk_free(STK_t *);

char help_str[] = "Allowed Operations: \n"
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
    stk_node_t *n;
    int op, val;
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
		if (n)
		    printf("Ele popped: %d \r\n", n->val);
		free(n);
                break;
            case 4: /*Top*/
                n = stk_top(STK);
		if (n)
		    printf("Top ele: %d \r\n", n->val);
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
    stk_node_t *n;

    if (!stk)
	return -1;
    
    n = (stk_node_t *)malloc(sizeof(struct stk_node));
    if (!n)
    {
	printf("Stack node Allocation failure \r\n");
	return -1;
    }
    n->val = val;
    n->next = stk->top;
    stk->top = n;
    stk->cur_sz++;

    return 0;
}

stk_node_t *stk_pop(STK_t *stk)
{
    stk_node_t *n;

    if (stk_is_empty(stk)) // stk null check done in stk_is_empty
	return NULL;

    n = stk->top;
    stk->top = n->next;
    stk->cur_sz--;
    // Node not freed, caller expected to free the node.
    return n;
}

stk_node_t *stk_top(STK_t *stk)
{
    return stk->top;
}

int stk_is_empty(STK_t *stk)
{
    if (!stk)
	return -1;
    return (stk->top ? 0 : 1);
}

int stk_is_full(STK_t *stk)
{
    return 0; // FALSE always as linked list implementation
	      // doesn't have a size limitation
}

void stk_display(STK_t *stk)
{
    stk_node_t *n;

    if (!stk)
	return;

    printf("List elements: \r\n");
    if (!stk->top)
        return;

    n=stk->top;
    while (n)
    {
	printf("%d ", n->val);
	n=n->next;
    }
    printf("\n");
}

void stk_free(STK_t *stk)
{
    stk_node_t *cur,*nxt;

    if (!stk)
	return;
    cur=stk->top;
    while (cur)
    {
	nxt=cur->next;
	free(cur);
	cur=nxt;
    }
    free(stk);
}


