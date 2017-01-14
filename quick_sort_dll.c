#include <stdio.h>
#include <stdlib.h>

typedef struct dll_node {
    struct dll_node *next;
    struct dll_node *prev;
    int val; // int declared here, but change date type as necessary
} dll_node_t;

dll_node_t *dll_head;
int list_sz;

dll_node_t *quick_sort(dll_node_t *);
void qs_partition(dll_node_t **, dll_node_t *, dll_node_t **);
dll_node_t *dll_prepend(dll_node_t *, int); // int type input, but change data type as necessary
dll_node_t *dll_get_tail(dll_node_t *);
void dll_display(dll_node_t *);
void dll_free(dll_node_t *);


int main()
{
    int i, val;

    printf("Enter the number of elements :");
    scanf("%d", &list_sz);
    if (list_sz <0)
    {
	printf("Invalid list size \r\n");
	return 0;
    }

    for (i=0; i<list_sz; i++)
    {
	scanf("%d", &val); // INput verification not done
        dll_head = dll_prepend(dll_head, val);
    }
    dll_display(dll_head);
    dll_head = quick_sort(dll_head); // Sort in ascending order
				     // nodes are re-arranged. Data is NOT moved from one node to another
    dll_display(dll_head);

    dll_free(dll_head);
    dll_head=NULL;


    return 0;
}

// Avg, Worst: O(nlogn) algo, but no extra array required as in merge sort
dll_node_t *quick_sort(dll_node_t *head)
{
    dll_node_t *pivot, *tail, *second_partition=NULL, *cur;

    if ((!head) || (!head->next)) // empty or single element list
        return head;

    pivot = dll_get_tail(head); // picking last element of the list as pivot
		    // Other ways: choose a random index, 
		    // choose 3 random indices & take median of the three numbers at these indices.
    // remove pivot from the list
    pivot->prev->next=NULL;

    // make two lists
    qs_partition(&head, pivot, &second_partition);
    head = quick_sort(head); 
    tail=dll_get_tail(head);
    if (tail) {
        tail->next= pivot;
	pivot->prev = tail;
    } else {
	head=pivot;
	pivot->prev = NULL;
    }
    second_partition = quick_sort(second_partition);
    if (second_partition)
    {
        pivot->next = second_partition;
        second_partition->prev = pivot;
    } else
        pivot->next = NULL;

    return head;
}

void qs_partition(dll_node_t **head, dll_node_t *pivot, dll_node_t **second_partition)
{
    dll_node_t *second_part_cur=NULL, *cur;

    *second_partition=NULL;
    cur = *head;
    while(cur)
    {
	if (cur->val > pivot->val)
	{
	    // remove cur from this list
	    if(cur->prev) {
		cur->prev->next=cur->next;
	    } else 
		*head = cur->next;
	    if(cur->next)
		cur->next->prev = cur->prev;
	    // add cur to second_partition list
	    if (*second_partition) {
		second_part_cur->next = cur;
		cur->prev = second_part_cur;
		second_part_cur = cur;
	    } else {
		*second_partition= cur;
		cur->prev = NULL;
		second_part_cur = cur;
	    } 
	} 
	cur=cur->next;
    }
    if (second_part_cur)
        second_part_cur->next = NULL;
}

dll_node_t *dll_get_tail(dll_node_t *node)
{
    while (node && (node->next))
	node=node->next;
    return node;
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

void dll_display(dll_node_t *node)
{
    if (!node)
	return;

    printf("List elements:\r\n");
    while (node)
    {
        printf("%d ", node->val);
        node=node->next;
    }
    printf("\r\n");
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

