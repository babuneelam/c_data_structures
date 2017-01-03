#include <stdio.h>
#include <stdlib.h>

typedef struct sll_node {
    struct sll_node *next;
    int val; // int declared here, but change date type as necessary
} sll_node_t;

sll_node_t *sll_head;
int list_sz;

sll_node_t *quick_sort(sll_node_t *);
void qs_partition(sll_node_t **, sll_node_t *, sll_node_t **);
sll_node_t *sll_prepend(sll_node_t *, int); // int type input, but change data type as necessary
sll_node_t *sll_get_tail(sll_node_t *);
void sll_display(sll_node_t *);
void sll_free(sll_node_t *);


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
        sll_head = sll_prepend(sll_head, val);
    }
    sll_head = quick_sort(sll_head); // Sort in ascending order
				     // nodes are re-arranged. Data is NOT moved from one node to another
    printf("Elements after quick sorting: ");
    sll_display(sll_head);
    printf("\r\n");

    sll_free(sll_head);
    sll_head=NULL;


    return 0;
}

// Avg, Worst: O(nlogn) algo, but no extra array required as in merge sort
sll_node_t *quick_sort(sll_node_t *head)
{
    sll_node_t *pivot, *tail, *second_partition=NULL, *cur, *prev;

    if ((!head) || (!head->next)) // empty or single element list
        return head;

    prev=NULL;
    cur=head;
    while(cur->next)
    {
	prev=cur;
	cur=cur->next;
    }
    // remove pivot from the list
    prev->next=NULL;
    pivot = cur; // picking last element of the list as pivot
		    // Other ways: choose a random index, 
		    // choose 3 random indices & take median of the three numbers at these indices.

    // make two lists
    qs_partition(&head, pivot, &second_partition);
    head = quick_sort(head); 
    tail=sll_get_tail(head);
    if (tail)
        tail->next= pivot;
    else
	head=pivot;
    pivot->next = quick_sort(second_partition);
    return head;
}

void qs_partition(sll_node_t **head, sll_node_t *pivot, sll_node_t **second_partition)
{
    sll_node_t *second_part_cur=NULL, *cur, *prev=NULL;

    *second_partition=NULL;
    cur = *head;
    while(cur)
    {
	if (cur->val > pivot->val)
	{
	    // remove cur from this list
	    if(prev)
		prev->next=cur->next;
	    else 
		*head = cur->next;
	    // add cur to second_partition list
	    if (*second_partition) {
		second_part_cur->next = cur;
		second_part_cur = second_part_cur->next;
	    } else {
		*second_partition= cur;
		second_part_cur = cur;
	    } 
	} else 
  	    prev=cur;
	cur=cur->next;
    }
    if (second_part_cur)
        second_part_cur->next = NULL;
}

sll_node_t *sll_get_tail(sll_node_t *node)
{
    while (node && (node->next))
	node=node->next;
    return node;
}


sll_node_t *sll_prepend(sll_node_t *head, int val)
{
    sll_node_t *n;

    n = (sll_node_t *)malloc(sizeof(struct sll_node));
    if (!n)
    {
        printf("Memory Allocation failure \r\n");
        return head;
    }
    n->val = val;
    n->next = head;

    return n;
}

void sll_display(sll_node_t *node)
{
    while (node)
    {
        printf("%d ", node->val);
        node=node->next;
    }
}

void sll_free(sll_node_t *head)
{
    sll_node_t *cur,*nxt;

    cur=head;
    while (cur)
    {
        nxt=cur->next;
        free(cur);
        cur=nxt;
    }
}

