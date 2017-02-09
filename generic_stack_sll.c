#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NO_MORE -1
#define DATA_TYPE 1 // 1 - int, 2-string
#define MAX_STR_LEN 50

typedef struct stk_node {
    struct stk_node *next;
    void *val; 
} stk_node_t;

typedef struct STK {
    stk_node_t *top;
    int cur_sz; // can be avoided, just for stats

    // Generic Functions
    void (*disp)(void *);
    void (*free)(void *);
} STK_t;

STK_t *STK;

STK_t *stk_init(void (*disp)(void *), void (*free)(void *));
int stk_push(STK_t *, void *);
void *stk_pop(STK_t *);
void *stk_top(STK_t *);
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

void *read_fn();
void display_fn(void *);
void free_fn(void *);

int main()
{
    stk_node_t *n;
    int op, empty, full;
    void *val;

    STK = stk_init(display_fn, free_fn);
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
                //scanf("%d", &val);
		val = read_fn();
                stk_push(STK, val);
                break;
            case 3: /*Pop*/
                val = stk_pop(STK);
		if (val)
		{
		    printf("Ele popped: ");
		    STK->disp(val); 
		    printf("\r\n");
		    //printf("Ele popped: %d \r\n", n->val);
		}
		STK->free(val);
                break;
            case 4: /*Top*/
                val = stk_top(STK);
		if (val)
		{
		    printf("Top ele: ");
		    STK->disp(val);
		    printf("\r\n");
		    //printf("Top ele: %d \r\n", n->val);
		}
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

STK_t *stk_init(void (*disp)(void *), void (*free)(void *))
{
    STK_t *s;

    s = (STK_t *)calloc(1, sizeof(struct STK));
    s->disp = disp;
    s->free = free;
    return s;
}

int stk_push(STK_t *stk, void *val)
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

void *stk_pop(STK_t *stk)
{
    stk_node_t *n;
    void *val;

    if (stk_is_empty(stk)) // stk null check done in stk_is_empty
	return NULL;

    val = stk->top->val;
    n = stk->top;
    stk->top = n->next;
    free(n);
    stk->cur_sz--;
    // Node not freed, caller expected to free the node.
    return val;
}

void *stk_top(STK_t *stk)
{
    if (stk_is_empty(stk)) // stk null check done in stk_is_empty
	return NULL;

    return stk->top->val;
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
	stk->disp(n->val);
	//printf("%d ", n->val);
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
	stk->free(cur->val);
	free(cur);
	cur=nxt;
    }
    free(stk);
}


void *read_fn()
{
    int *n;
    char *s;

    switch (DATA_TYPE) {
	case 1:
    	    // Integer Type
    	    n = (int *)malloc(sizeof(int));
    	    if (!n)
    	    {
		printf("Allocation failure \r\n");
		return NULL;
    	    }
    	    scanf("%d", n);
    	    return (void *)n;
	    break;
	case 2:
    	// String Type
    	    s = (char *)malloc(MAX_STR_LEN);
    	    if (!s)
    	    {
		printf("Allocation failure \r\n");
		return NULL;
    	    }
            getchar();
            memset(s,'\n',MAX_STR_LEN);
// why not scanf %s? because fgets offers protection against buffer overflows
// http://stackoverflow.com/questions/26955466/difference-between-gets-vs-scanf-vs-fgets-in-c-programming
            fgets(s, MAX_STR_LEN, stdin);
            if(s[MAX_STR_LEN-1] != '\n')
            {
                printf("Input string is more than allowed limit \r\n");
                while ( getchar() != '\n' ); // flush any additional chars from stdin
                break;
            }
            s[strlen(s)-1] = '\0'; // remove '\n' at the end

    	    return (void *)s;
	    break;
	default:
	    return NULL;
	    break;
    }

    return NULL;
}

void display_fn(void *n)
{
    switch (DATA_TYPE) {
	case 1:
    	    // Integer Type
    	    printf("%d ", *((int*)n));
	    break;
	case 2:
            // String Type
    	    printf("%s ", (char *)n);
	    break;
	default:
	    break;
    }
}

void free_fn(void *n)
{
    // Could involve recursive frees inside n. 
    switch (DATA_TYPE) {
	case 1:
            // Integer Type
            free(n); 
	    break;
            //free((int *)n); 
	case 2:
    	    // String Type
            free(n);
	    break;
	default:
	    break;
    }
}
