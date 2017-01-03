#include <stdio.h>
#include <stdlib.h>

#define NO_MORE -1

typedef struct dll_node {
    struct dll_node *next;
    struct dll_node *prev;
    int val; // int declared here, but change date type as necessary
} dll_node_t;

dll_node_t *dll_head=NULL;

dll_node_t *dll_prepend(dll_node_t *, int);
dll_node_t *dll_append(dll_node_t *, int);
dll_node_t *dll_delete(dll_node_t *, int);
dll_node_t *dll_search(dll_node_t *, int );
dll_node_t *dll_reverse_iter(dll_node_t *);
dll_node_t *dll_reverse_recur(dll_node_t *);
void dll_display(dll_node_t *);
void dll_free(dll_node_t *);

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
    dll_node_t *n;
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
                dll_head = dll_prepend(dll_head, val);
                break;
            case 3: /*Append*/
                scanf("%d", &val);
                dll_head = dll_append(dll_head, val);
                break;
            case 4: /*delete */
                scanf("%d", &val);
                dll_head = dll_delete(dll_head, val);
                break;
            case 5: /* search */
                scanf("%d", &val);
                n = dll_search(dll_head, val);
                if (n)
                    printf("Found \r\n");
                else
                    printf("val %d not found in linked list\r\n", val);
                break;
            case 6: /* display entire linked list */
                dll_display(dll_head);
                break;
            case 7: /* reverse a list itereatively */
                dll_head = dll_reverse_iter(dll_head);
                break;
            case 8: /* reverse a list recursively*/
                dll_head = dll_reverse_recur(dll_head);
                break;
            default: /*error */
                printf("Invalid operation\r\n");
                break;
        }
        scanf("%d", &op);
    }

    dll_display(dll_head);
    dll_free(dll_head);
    dll_head=NULL;

    return 0;
}

dll_node_t *dll_prepend(dll_node_t *head, int val)
{
    dll_node_t *n;

    n = (dll_node_t *)malloc(sizeof(struct dll_node));
    if (!n)
    {
	printf("Memory Allocation failure \r\n");
	return head;
    }
    n->val = val;
    n->next = head;
    n->prev = NULL;
    if (head)
    	head->prev = n;

    return n;
}

dll_node_t *dll_append(dll_node_t *head, int val)
{
    dll_node_t *n, *cur;

    n = (dll_node_t *)malloc(sizeof(struct dll_node));
    if (!n)
    {
	printf("Memory Allocation failure \r\n");
	return head;
    }
    n->val = val;
    n->next = n->prev = NULL;;

    if (!head)
	return n;

    cur=head;
    while (cur->next)
        cur = cur->next;
    cur->next = n;
    n->prev = cur;

    return head;
}

dll_node_t *dll_delete(dll_node_t *head, int val)
{
    dll_node_t *cur, *prev;

    if (!head)
	return NULL;

    prev=NULL;
    cur=head;
    while (cur)
    {
	if (cur->val == val)
	{
	    if (cur->next)
		cur->next->prev = prev;
	    if (prev)
		prev->next = cur->next;
	    else
		head=head->next;
	    free(cur);
	    return head;
	}
	prev=cur;
	cur=cur->next;
    }
    return head;
}

dll_node_t *dll_search(dll_node_t *head, int val)
{
    dll_node_t *n;

    if (!head)
        return NULL;

    n=head;
    while (n)
    {
	if (n->val == val)
	    return n;
	n=n->next;
    }
    return NULL;
}

void dll_display(dll_node_t *head)
{
    dll_node_t *n;

    if (!head)
        return;

    printf("List elements: ");
    n=head;
    while (n)
    {
	printf("%d ", n->val);
	n=n->next;
    }
    printf("\n");
}

dll_node_t *dll_reverse_iter(dll_node_t *head)
{
    dll_node_t *prev, *cur, *nxt;

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
}


dll_node_t *dll_reverse_recur(dll_node_t *head)
{
    dll_node_t *new_head, *nxt;

    if (!head)
	return NULL;
    if (!head->next)
	return head;
    nxt=head->next;
    new_head=dll_reverse_recur(nxt);
    nxt->next=head;
    head->prev=nxt;
    head->next=NULL;
    return new_head;
}

void dll_free(dll_node_t *head)
{
    dll_node_t *cur,*nxt;

    cur=head;
    while (cur)
    {
	nxt=cur->next;
	free(cur);
	cur=nxt;
    }
}


