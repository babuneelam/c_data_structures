#include <stdio.h>
#include <stdlib.h>

#define NO_MORE -1

typedef struct sll_node {
    struct sll_node *next;
    int val;
} sll_node_t;

sll_node_t *sll_head;

sll_node_t *sll_prepend(sll_node_t *, int);
sll_node_t *sll_append(sll_node_t *, int);
sll_node_t *sll_delete(sll_node_t *, int);
sll_node_t *sll_search(sll_node_t *, int );
sll_node_t *sll_reverse_iter(sll_node_t *);
sll_node_t *sll_reverse_recur(sll_node_t *);
void sll_display(sll_node_t *);
void sll_free(sll_node_t *);

char help_str[] = "Allowed Operations: \n"
    "   -1 - Exit\r\n"
    "    1 - print help(this list)\r\n"
    "    2 <ele> - Prepend ele\r\n"
    "    3 <ele> - Append ele\r\n"
    "    4 <ele> - Delete ele\r\n"
    "    5 <ele> - search ele\r\n"
    "    6 - display list\r\n"
    "    7 - reverse list iteratively\r\n"
    "    8 - reverse list recursively\r\n"
    ;

int main()
{
    sll_node_t *n;
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
                sll_head = sll_prepend(sll_head, val);
                break;
            case 3: /*Append*/
                scanf("%d", &val);
                sll_head = sll_append(sll_head, val);
                break;
            case 4: /*delete */
                scanf("%d", &val);
                sll_head = sll_delete(sll_head, val);
                break;
            case 5: /* search */
                scanf("%d", &val);
                n = sll_search(sll_head, val);
                if (n)
                    printf("Found \r\n");
                else
                    printf("val %d not found in linked list\r\n", val);
                break;
            case 6: /* display entire linked list */
                sll_display(sll_head);
                break;
            case 7: /* reverse a list itereatively */
                sll_head = sll_reverse_iter(sll_head);
                break;
            case 8: /* reverse a list recursively*/
                sll_head = sll_reverse_recur(sll_head);
                break;
            default: /*error */
                printf("Invalid operation\r\n");
                break;
        }
        scanf("%d", &op);
    }

    sll_display(sll_head);
    sll_free(sll_head);
    sll_head=NULL;

    return 0;
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

sll_node_t *sll_append(sll_node_t *head, int val)
{
    sll_node_t *n, *cur;

    n = (sll_node_t *)malloc(sizeof(struct sll_node));
    if (!n)
    {
        printf("Memory Allocation failure \r\n");
        return head;
    }
    n->val = val;
    n->next = NULL;;

    if (!head)
        return n;

    cur=head;
    while (cur->next)
        cur = cur->next;
    cur->next = n;

    return head;
}

sll_node_t *sll_delete(sll_node_t *head, int val)
{
    sll_node_t *cur, *prev;

    if (!head)
        return NULL;

    prev=NULL;
    cur=head;
    while (cur)
    {
        if (cur->val == val)
        {
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

sll_node_t *sll_search(sll_node_t *head, int val)
{
    sll_node_t *n;
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

void sll_display(sll_node_t *head)
{
    sll_node_t *n;

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

sll_node_t *sll_reverse_iter(sll_node_t *head)
{
    sll_node_t *prev, *cur, *nxt;

    prev=NULL;
    cur=head;
    while(cur)
    {
        nxt=cur->next;
        cur->next=prev;
        prev=cur;
        cur=nxt;
    }
    return prev;
}


sll_node_t *sll_reverse_recur(sll_node_t *head)
{
    sll_node_t *new_head, *nxt;

    if (!head)
        return NULL;
    if (!head->next)
        return head;
    nxt=head->next;
    new_head=sll_reverse_recur(nxt);
    nxt->next=head;
    head->next=NULL;
    return new_head;
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

