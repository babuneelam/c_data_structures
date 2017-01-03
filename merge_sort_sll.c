#include <stdio.h>
#include <stdlib.h>

typedef struct sll_node {
    struct sll_node *next;
    int val; // int declared here, but change date type as necessary
} sll_node_t;

sll_node_t *sll_head;
int list_sz;

sll_node_t *merge_sort(sll_node_t *);
sll_node_t *merge(sll_node_t *, sll_node_t *);
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
    sll_head = merge_sort(sll_head); // Sort in ascending order
				     // nodes are re-arranged. Data is NOT moved from one node to another
    printf("Elements after merge sorting: ");
    sll_display(sll_head);
    printf("\r\n");

    sll_free(sll_head);
    sll_head=NULL;

    return 0;
}

// Avg, Worst: O(nlogn) algo
sll_node_t *merge_sort(sll_node_t *head)
{
    sll_node_t *second_partition, *one_jmp, *two_jmp;

    if ((!head) || (!head->next))
	return head;

    // Divide into two lists
    one_jmp = two_jmp = head;
    while(two_jmp)
    {
	if ((!two_jmp->next) || (!two_jmp->next->next))
	   break;
	one_jmp = one_jmp->next;
	two_jmp = two_jmp->next->next;
    }

    second_partition = one_jmp->next;
    one_jmp->next = NULL; // break the list

    // sort each list separately
    head = merge_sort(head);
    second_partition = merge_sort(second_partition);

    // merge the two lists to one lists
    return (merge(head, second_partition));
}

sll_node_t *merge(sll_node_t *list1, sll_node_t *list2)
{
    sll_node_t *cur, *new_head;

    cur = new_head = NULL;
    while (list1 && list2)
    {
	if (list1->val < list2->val)
	{
            if (cur)
	    {
		cur->next = list1;
		cur = list1;
	    } else
		cur = new_head =list1;
	    list1 = list1->next;
	} else {
            if (cur)
	    {
		cur->next = list2;
		cur = list2;
	    } else
		cur = new_head =list2;
	    list2 = list2->next;
	}
    }

    if (list1)
    {
        if (cur)
	    cur->next = list1;
	else
	    new_head = list1;
    }

    if (list2)
    {
        if (cur)
	    cur->next = list2;
	else
	    new_head = list2;
    }

    return new_head;
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

