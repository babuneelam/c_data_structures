#include <stdio.h>
#include <stdlib.h>

#define NO_MORE -1
#define XOR(a,b) (xor_dll_node_t *)(((unsigned int)a) ^ ((unsigned int)b))

typedef struct xor_dll_node {
    struct xor_dll_node *next;
    int val; // int declared here, but change date type as necessary
} xor_dll_node_t;

xor_dll_node_t *xor_dll_head=NULL;

xor_dll_node_t *xor_dll_prepend(xor_dll_node_t *, int);
xor_dll_node_t *xor_dll_append(xor_dll_node_t *, int);
xor_dll_node_t *xor_dll_delete(xor_dll_node_t *, int);
xor_dll_node_t *xor_dll_search(xor_dll_node_t *, int );
xor_dll_node_t *xor_dll_reverse_iter(xor_dll_node_t *);
xor_dll_node_t *xor_dll_reverse_recur(xor_dll_node_t *);
void xor_dll_display(xor_dll_node_t *);
void xor_dll_free(xor_dll_node_t *);

char help_str[] = "Allowed Operations: \n"
    "	-1 - Exit\r\n"
    "	 1 - print help(this list)\r\n"
    "	 2 <ele> - Prepend ele\r\n"
    "	 3 <ele> - Append ele\r\n"
    "	 4 <ele> - Delete ele\r\n"
    "	 5 <ele> - search ele\r\n"
    "	 6 - display list\r\n"
    "	 7 - reverse list iteratively\r\n"
    "	 8 - reverse list recursively\r\n"
    ;

int main()
{
    xor_dll_node_t *n;
    int op, val;

    printf("%s",help_str);
    scanf("%d", &op);
    while(op != NO_MORE)
    {
        switch(op)
        {
	    case 1:
    		printf("%s",help_str);
                break;
            case 2: /*Prepend*/
                scanf("%d", &val);
                xor_dll_head = xor_dll_prepend(xor_dll_head, val);
                break;
            case 3: /*Append*/
                scanf("%d", &val);
                xor_dll_head = xor_dll_append(xor_dll_head, val);
                break;
            case 4: /*delete */
                scanf("%d", &val);
                xor_dll_head = xor_dll_delete(xor_dll_head, val);
                break;
            case 5: /* search */
                scanf("%d", &val);
                n = xor_dll_search(xor_dll_head, val);
                if (n)
                    printf("Found \r\n");
                else
                    printf("val %d not found in linked list\r\n", val);
                break;
            case 6: /* display entire linked list */
                xor_dll_display(xor_dll_head);
                break;
            case 7: /* reverse a list itereatively */
                xor_dll_head = xor_dll_reverse_iter(xor_dll_head);
                break;
            case 8: /* reverse a list recursively*/
                xor_dll_head = xor_dll_reverse_recur(xor_dll_head);
                break;
            default: /*error */
                printf("Invalid operation\r\n");
                break;
        }
        scanf("%d", &op);
    }

    xor_dll_display(xor_dll_head);
    xor_dll_free(xor_dll_head);
    xor_dll_head=NULL;

    return 0;
}

xor_dll_node_t *xor_dll_prepend(xor_dll_node_t *head, int val)
{
    xor_dll_node_t *n;

    n = (xor_dll_node_t *)malloc(sizeof(struct xor_dll_node));
    if (!n)
    {
	printf("Memory Allocation failure \r\n");
	return head;
    }
    n->val = val;
    n->next = XOR(NULL, head);
    if (head)
    	head->next = XOR(n, XOR(head->next, NULL)); // recompute head->next 

    return n;
}

xor_dll_node_t *xor_dll_append(xor_dll_node_t *head, int val)
{
    xor_dll_node_t *n, *cur, *prev, *tmp;

    n = (xor_dll_node_t *)malloc(sizeof(struct xor_dll_node));
    if (!n)
    {
	printf("Memory Allocation failure \r\n");
	return head;
    }
    n->val = val;

    if (!head)
    {
	n->next = XOR(NULL, NULL);
	return n;
    }

    prev = NULL;
    cur=head;
    while (XOR(cur->next, prev))
    {
	//cur = cur->nxt;
        tmp = prev;
	prev = cur;
        cur = XOR(cur->next, tmp);
    }
    cur->next = XOR(n, prev);
    n->next = XOR(cur, NULL);;

    return head;
}

xor_dll_node_t *xor_dll_delete(xor_dll_node_t *head, int val)
{
    xor_dll_node_t *cur, *prev, *nxt, *tmp;

    if (!head)
	return NULL;

    prev=NULL;
    cur=head;
    while (cur)
    {
	if (cur->val == val)
	{
 	    nxt = XOR(cur->next, prev);
	    if (nxt)
		nxt->next = XOR(prev, XOR(nxt->next, cur));
	    if (prev)
		prev->next = XOR(nxt, XOR(prev->next, cur));
	    else
		head = XOR(cur->next, NULL);;
	    free(cur);
	    return head;
	}
	//Implement cur=cur->next;
	tmp =prev;
	prev=cur;
	cur=XOR(cur->next, tmp);
    }
    printf("Not found\r\n");
    return head;
}

xor_dll_node_t *xor_dll_search(xor_dll_node_t *head, int val)
{
    xor_dll_node_t *cur, *prev, *tmp;

    if (!head)
        return NULL;

    prev = NULL;
    cur=head;
    while (cur)
    {
	if (cur->val == val)
	    return cur;
	//Implement cur=cur->next;
	tmp =prev;
	prev=cur;
	cur=XOR(cur->next, tmp);
    }
    return NULL;
}

void xor_dll_display(xor_dll_node_t *head)
{
    xor_dll_node_t *cur, *prev, *tmp;

    if (!head)
        return;

    printf("List elements: ");
    prev = NULL;
    cur=head;
    while (cur)
    {
	printf("%d ", cur->val);
	//Implement cur=cur->next;
	tmp =prev;
	prev=cur;
	cur=XOR(cur->next, tmp);
    }
    printf("\n");
}

xor_dll_node_t *xor_dll_reverse_iter(xor_dll_node_t *head)
{
/*
    xor_dll_node_t *prev, *cur, *nxt;

    prev=NULL;
    cur=head;
    while(cur)
    {
	nxt=cur->next;
	cur->next=prev;
        cur->prev=nxt;
	prev=cur;
	cur=nxt;
    }
    return prev;
*/
}


xor_dll_node_t *xor_dll_reverse_recur(xor_dll_node_t *head)
{
/*
    xor_dll_node_t *new_head, *nxt;

    if (!head)
	return NULL;
    if (!head->next)
	return head;
    nxt=head->next;
    new_head=xor_dll_reverse_recur(nxt);
    nxt->next=head;
    head->prev=nxt;
    head->next=NULL;
    return new_head;
*/
}

void xor_dll_free(xor_dll_node_t *head)
{
    xor_dll_node_t *cur,*nxt, *prev, *tmp;

    prev = NULL;
    cur=head;
    while (cur)
    {
	//Implement nxt=cur->next;
	tmp =prev;
	prev=cur;
	nxt =XOR(cur->next, tmp);

	free(cur);
	cur=nxt;
    }
}


