#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SZ 1000
#define NO_MORE -1
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

typedef struct bst_node {
    struct bst_node *left;
    struct bst_node *right;
    int val; // int declared here, but change date type as necessary
} bst_node_t;

bst_node_t *bst_root;

bst_node_t *bst_insert(bst_node_t *, int);
bst_node_t *bst_delete(bst_node_t *, int);
bst_node_t *bst_search(bst_node_t *, int);
bst_node_t *find_min(bst_node_t *);
bst_node_t *find_max(bst_node_t *); 
int bst_height(bst_node_t *);
void inorder(bst_node_t *);
void preorder(bst_node_t *);
void postorder(bst_node_t *);
void bst_free(bst_node_t *);
void TBLR_1(bst_node_t *);
void print_level(bst_node_t *, int );
void TBLR_2(bst_node_t *);
void TBRL(bst_node_t *);

bst_node_t **Q_create();
void Q_enqueue(bst_node_t **, bst_node_t *, int *, int *);
bst_node_t *Q_dequeue(bst_node_t **, int *, int *);
void Q_free(bst_node_t **);

char help_str[] = "Allowed Operations: \n"
    "   -1 - Exit\r\n"
    "    1 - print help(this list)\r\n"
    "    2 <ele> - Insert ele\r\n"
    "    3 <ele> - Delete ele\r\n"
    "    4 <ele> - Find ele\r\n"
    "    5 - Find min ele\r\n"
    "    6 - Find max ele\r\n"
    "    7 - Display tree height\r\n"
    "    8 - Display Tree via depth first traversals(inorder, preorder, postorder) \r\n"
    "    9 - Display Tree via breadth first traversal(Top to bottom left to right, top to bottom right to left) \r\n"
    ;

int main()
{
    bst_node_t *n;
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
            case 2: /*Insert*/
                scanf("%d", &val);
                bst_root = bst_insert(bst_root, val);
                break;
            case 3: /*Delete*/
                scanf("%d", &val);
                bst_root = bst_delete(bst_root, val);
                break;
            case 4: /*Search*/
                scanf("%d", &val);
                if (bst_search(bst_root, val))
		    printf("Found \r\n");
		else
		    printf("Not found\r\n");
                break;
            case 5: /* Find Min*/
                n = find_min(bst_root);
                if (n)
                    printf("max value in the tree: %d \r\n", n->val);
                break;
            case 6: /* Find Max*/
                n = find_max(bst_root);
                if (n)
                    printf("max value in the tree: %d \r\n", n->val);
                break;
            case 7: /* Find tree height*/
                printf("Tree Height: %d \r\n", bst_height(bst_root));
                break;
            case 8: /* display entire tree via depth first traversals*/
    		printf("	Inorder: ");
		inorder(bst_root);
    		printf("\n	Preorder: ");
		preorder(bst_root);
    		printf("\n	Postorder: ");
		postorder(bst_root);
		printf("\n");
                break;
            case 9: /* display entire tree via breadth first traversals*/
    		printf("	TBLR_1: ");
		TBLR_1(bst_root);
    		printf("	TBLR_2: ");
		TBLR_2(bst_root);
    		printf("	TBRL: ");
		TBRL(bst_root);
                break;
            default: /*error */
                printf("Invalid operation\r\n");
                break;
        }
        scanf("%d", &op);
    }

    printf("	Inorder: ");
    inorder(bst_root);
    printf("\r\n");
    printf("	Preorder: ");
    preorder(bst_root);
    printf("\r\n");
    printf("	Post-order: ");
    postorder(bst_root);
    printf("\r\n");
    bst_free(bst_root);
    bst_root=NULL;

    return 0;
}

bst_node_t *bst_insert(bst_node_t *root, int val)
{
    if(!root)
    {
        root = (bst_node_t *)malloc(sizeof(struct bst_node));
        if (!root)
        {
            printf("Memory Allocation failure \r\n");
            return root;
        }
        root->val = val;
	root->left = root->right = NULL;
	return root;
    }

    if (val < root->val)
    {
	root->left = bst_insert(root->left, val);
	return root;
    } else if (val > root->val) {
	root->right = bst_insert(root->right, val);
	return root;
    } 
    return root; // this "val" already exists
}

bst_node_t *bst_delete(bst_node_t *root, int val)
{
    if (!root)
    {
	printf("Val %d not found in the tree \r\n", val);
	return root;
    }

    if (val < root->val)
    {
	root->left = bst_delete(root->left, val);
	return root;
    } else if (val > root->val) {
	root->right = bst_delete(root->right, val);
	return root;
    } 
    if (root->left && root->right)
    {
        root->val = find_min(root)->val;
	root->right - bst_delete(root->right, root->val);
    }
    if (!root->right)
    	return root->left;
    else
    	return root->right;

    free(root);
    return NULL;
}

bst_node_t *bst_search(bst_node_t *root, int val)
{
    if (!root)
        return NULL;

    if (val < root->val)
	return(bst_search(root->left, val));
    else if (val > root->val) 
	return(bst_search(root->right, val));

    return root;
}

bst_node_t *find_min(bst_node_t *root)
{
    if (!root)
        return NULL;
    if (root->left)
	return(find_min(root->left));
    return root;
}

bst_node_t *find_max(bst_node_t *root)
{
    if (!root)
        return NULL;
    if (root->right)
	return(find_max(root->right));
    return root;
}

int bst_height(bst_node_t *root)
{
    if (!root)
        return 0;
    return(MAX(bst_height(root->left), bst_height(root->right))+1);
}

/*
Ref: http://www.geeksforgeeks.org/bfs-vs-dfs-binary-tree/

BFS vs DFS for Binary Tree
===============================-
What are BFS and DFS for Binary Tree?

A Tree is typically traversed in two ways:

	Breadth First Traversal (Or Level Order Traversal)
	Depth First Traversals
	    Inorder Traversal (Left-Root-Right)
	    Preorder Traversal (Root-Left-Right)
	    Postorder Traversal (Left-Right-Root)

Why do we care?
---------------
There are many tree questions that can be solved using any of the above four 
traversals. Examples of such questions are size, maximum, minimum, print left 
view, etc.

Is there any difference in terms of Time Complexity?
----------------------------------------------------
All four traversals require O(n) time as they visit every node exactly once.

Is there any difference in terms of Extra Space?
There is difference in terms of extra space required.

	1) Extra Space required for Level Order Traversal is O(w) where w is 
	   maximum width of Binary Tree. In level order traversal, queue one 
	   by one stores nodes of different level.
	2) Extra Space required for Depth First Traversals is O(h) where h is 
	   maximum height of Binary Tree. In Depth First Traversals, stack (or 
	   function call stack) stores all ancestors of a node.

Maximum Width of a Binary Tree at depth (or height) h can be 2h where h starts 
from 0. So the maximum number of nodes can be at the last level. And worst 
case occurs when Binary Tree is a perfect Binary Tree with numbers of nodes 
like 1, 3, 7, 15, …etc. In worst case, value of 2h is Ceil(n/2).

Height for a Balanced Binary Tree is O(Log n). Worst case occurs for skewed 
tree and worst case height becomes O(n).

So in worst case extra space required is O(n) for both. But worst cases occur 
for different types of trees.

It is evident from above points that extra space required for Level order 
traversal is likely to be more when tree is more balanced and extra space for 
Depth First Traversal is likely to be more when tree is less balanced.

How to Pick One?
-----------------

	1) Extra Space can be one factor (Explained above)
	2) Depth First Traversals are typically recursive and recursive code 
	   requires function call overheads.
	3) The most important points is, BFS starts visiting nodes from root 
	   while DFS starts visiting nodes from leaves. So if our problem is 
	   to search something that is more likely to closer to root, we would 
	   prefer BFS. And if the target node is close to a leaf, we would 
	   prefer DFS.  
*/

void inorder(bst_node_t *root)
{
    if (!root)
        return;
    inorder(root->left);
    printf("%d ", root->val);
    inorder(root->right);
}

void preorder(bst_node_t *root)
{
    if (!root)
        return;
    printf("%d ", root->val);
    preorder(root->left);
    preorder(root->right);
}

void postorder(bst_node_t *root)
{
    if (!root)
        return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->val);
}

void bst_free(bst_node_t *root)
{
    // Using postorder method to free the nodes
    if (!root)
        return;
    bst_free(root->left);
    bst_free(root->right);
    root->left=root->right = NULL;
    free(root);
}

// http://www.geeksforgeeks.org/level-order-tree-traversal/
// http://algorithms.tutorialhorizon.com/level-order-traversal-print-each-level-in-separate-line/

void TBLR_1(bst_node_t *root)
{
    int i, h;

    h= bst_height(root);
    printf("Eelements in BST in TBLR order: \r\n");
    for (i=1; i<= h; i++)
    {
	print_level(root, i);
	printf("\r\n");
    }
}

void print_level(bst_node_t *root, int level)
{
    if (!root)
	return;
    if (level == 1)
    {
	printf("%d ", root->val);
	return;
    }
    print_level(root->left, level-1);
    print_level(root->right, level-1);
}


void TBLR_2(bst_node_t *root)
{
    bst_node_t **Q=NULL, *cur;
    int start=0, end=0;

    if (!root)
	return;
    if ((Q = Q_create()) == NULL)
	return;
    Q_enqueue(Q, root, &start, &end);
    printf("Eelements in BST in TBLR order: \r\n");
    while (cur=Q_dequeue(Q, &start, &end))
    {
        printf("%d ", cur->val);
	if (cur->left)
            Q_enqueue(Q, cur->left, &start, &end);
	if (cur->right)
            Q_enqueue(Q, cur->right, &start, &end);
    }
    Q_free(Q);
    printf("\r\n");
}

void TBRL(bst_node_t *root)
{
    bst_node_t **Q=NULL, *cur;
    int start=0, end=0;

    if (!root)
	return;
    if ((Q = Q_create()) == NULL)
	return;
    Q_enqueue(Q, root, &start, &end);
    printf("Eelements in BST in TBLR order: \r\n");
    while (cur=Q_dequeue(Q, &start, &end))
    {
        printf("%d ", cur->val);
	if (cur->right)
            Q_enqueue(Q, cur->right, &start, &end);
	if (cur->left)
            Q_enqueue(Q, cur->left, &start, &end);
    }
    Q_free(Q);
    printf("\r\n");
}

bst_node_t **Q_create()
{
    bst_node_t **Q;

    Q = (bst_node_t **)calloc(MAX_QUEUE_SZ, sizeof(bst_node_t *));
    if (!Q)
    {
	printf("Allocation failure \r\n");
	return NULL;
    }
    return Q;
}

void Q_enqueue(bst_node_t **Q, bst_node_t *node, int *start, int *end)
{
    if (abs(*end - *start) == (MAX_QUEUE_SZ -1))
    {
	printf("Queue full \r\n");
	return;
    }

    Q[*end] = node;
    if (++(*end) == MAX_QUEUE_SZ)
	*end =0;
    return;
}


bst_node_t *Q_dequeue(bst_node_t **Q, int *start, int *end)
{
    bst_node_t *n;

    if (abs(*end - *start) == 0)
	return NULL;

    n = Q[*start];
    if (++(*start) == MAX_QUEUE_SZ)
	*start=0;
    return n;
}

void Q_free(bst_node_t **Q)
{
    free(Q);
}
