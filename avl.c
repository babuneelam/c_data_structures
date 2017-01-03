#include <stdio.h>
#include <stdlib.h>

#define NO_MORE -1
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

typedef struct bst_node {
    struct bst_node *left;
    struct bst_node *right;
    int val; // int declared here, but change date type as necessary
    int height;
} bst_node_t;

bst_node_t *bst_root;

bst_node_t *avl_insert(bst_node_t *, int);
bst_node_t *s_rotate_left(bst_node_t *);
bst_node_t *d_rotate_left(bst_node_t *);
bst_node_t *s_rotate_right(bst_node_t *);
bst_node_t *d_rotate_right(bst_node_t *);
bst_node_t *avl_delete(bst_node_t *, int);
bst_node_t *bst_search(bst_node_t *, int);
bst_node_t *find_min(bst_node_t *);
bst_node_t *find_max(bst_node_t *); 
int bst_height(bst_node_t *);
void inorder(bst_node_t *);
void preorder(bst_node_t *);
void postorder(bst_node_t *);
void bst_free(bst_node_t *);

char help_str[] = "Allowed Operations: \n"
    "   -1 - Exit\r\n"
    "    1 - print help(this list)\r\n"
    "    2 <ele> - Insert ele\r\n"
    "    3 <ele> - Delete ele\r\n"
    "    4 <ele> - Find ele\r\n"
    "    5 - Find min ele\r\n"
    "    6 - Find max ele\r\n"
    "    7 - Display tree height\r\n"
    "    8 - Display Tree via traversals(inorder, preorder, postorder) \r\n"
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
                bst_root = avl_insert(bst_root, val);
                break;
            case 3: /*Delete*/
                scanf("%d", &val);
                bst_root = avl_delete(bst_root, val);
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
            case 8: /* display entire tree via traversals*/
    		printf("	Inorder: ");
		inorder(bst_root);
    		printf("\n	Preorder: ");
		preorder(bst_root);
    		printf("\n	Postorder: ");
		postorder(bst_root);
		printf("\n");
                break;
            default: /*error */
                printf("Invalid operation\r\n");
                break;
        }
        scanf("%d", &op);
    }

    inorder(bst_root);
    preorder(bst_root);
    postorder(bst_root);
    bst_free(bst_root);
    bst_root=NULL;

    return 0;
}

/*

a) Left Left Case

T1, T2, T3 and T4 are subtrees.
         z                                      y 
        / \                                   /   \
       y   T4      Right Rotate (z)          x      z
      / \          - - - - - - - - ->      /  \    /  \ 
     x   T3                               T1  T2  T3  T4
    / \
  T1   T2
b) Left Right Case

     z                               z                           x
    / \                            /   \                        /  \ 
   y   T4  Left Rotate (y)        x    T4  Right Rotate(z)    y      z
  / \      - - - - - - - - ->    /  \      - - - - - - - ->  / \    / \
T1   x                          y    T3                    T1  T2 T3  T4
    / \                        / \
  T2   T3                    T1   T2
c) Right Right Case

  z                                y
 /  \                            /   \ 
T1   y     Left Rotate(z)       z      x
    /  \   - - - - - - - ->    / \    / \
   T2   x                     T1  T2 T3  T4
       / \
     T3  T4
d) Right Left Case

   z                            z                            x
  / \                          / \                          /  \ 
T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      y
    / \  - - - - - - - - ->     /  \   - - - - - - - ->  / \    / \
   x   T4                      T2   y                  T1  T2  T3  T4
  / \                              /  \
T2   T3                           T3   T4

Source:
http://www.geeksforgeeks.org/avl-tree-set-1-insertion/

*/

bst_node_t *avl_insert(bst_node_t *root, int val)
{
    int lh, rh;

    if(!root)
    {
        root = (bst_node_t *)malloc(sizeof(struct bst_node));
        if (!root)
        {
            printf("Memory Allocation failure \r\n");
            return root;
        }
        root->val = val;
        root->height = 1;
	root->left = root->right = NULL;
	return root;
    }

    if (val < root->val)
    {
	root->left = avl_insert(root->left, val);
        lh = bst_height(root->left);
	rh = bst_height(root->right);
	if ((lh-rh) == 2)
	{
	    if(val < root->left->val)
		root = s_rotate_right(root);
	    else
		root = d_rotate_right(root);
	} else
	    root->height = MAX(lh,rh)+1;
	return root;
    } else if (val > root->val) {
	root->right = avl_insert(root->right, val);
        lh = bst_height(root->left);
	rh = bst_height(root->right);
	if ((rh-lh) == 2)
	{
	    if(val > root->right->val)
		root = s_rotate_left(root);
	    else
		root = d_rotate_left(root);
	} else
	    root->height = MAX(lh,rh)+1;
	return root;
    } 
    return root; // this "val" already exists
}

/*
a) Left Left Case

T1, T2, T3 and T4 are subtrees.
         z                                      y 
        / \                                   /   \
       y   T4      Right Rotate (z)          x      z
      / \          - - - - - - - - ->      /  \    /  \ 
     x   T3                               T1  T2  T3  T4
    / \
  T1   T2
*/
// Rotate to the tree to thr right to correct imbalance in the leftmost subtree
bst_node_t *s_rotate_right(bst_node_t *x)
{
    bst_node_t *y;

    y = x->left;
    x->left = y->right;
    y->right = x;
    x->height = MAX(bst_height(x->left), bst_height(x->right))+1;
    y->height = MAX(bst_height(y->left), bst_height(y->right))+1;
    return y;
}

/*
c) Right Right Case

  z                                y
 /  \                            /   \ 
T1   y     Left Rotate(z)       z      x
    /  \   - - - - - - - ->    / \    / \
   T2   x                     T1  T2 T3  T4
       / \
     T3  T4
*/
// Rotate to the tree to the left to correct imbalance in the rightmost subtree
bst_node_t *s_rotate_left(bst_node_t *x)
{
    bst_node_t *y;

    y = x->right;
    x->right = y->left;
    y->left = x;

    x->height = MAX(bst_height(x->left), bst_height(x->right))+1;
    y->height = MAX(bst_height(y->left), bst_height(y->right))+1;
    return y;
}

/*
b) Left Right Case

     z                               z                           x
    / \                            /   \                        /  \ 
   y   T4  Left Rotate (y)        x    T4  Right Rotate(z)    y      z
  / \      - - - - - - - - ->    /  \      - - - - - - - ->  / \    / \
T1   x                          y    T3                    T1  T2 T3  T4
    / \                        / \
  T2   T3                    T1   T2
*/
bst_node_t *d_rotate_right(bst_node_t *n)
{
    n->left = s_rotate_left(n->left);
    return(s_rotate_right(n));
}

/*
d) Right Left Case

   z                            z                            x
  / \                          / \                          /  \ 
T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      y
    / \  - - - - - - - - ->     /  \   - - - - - - - ->  / \    / \
   x   T4                      T2   y                  T1  T2  T3  T4
  / \                              /  \
T2   T3                           T3   T4
*/
bst_node_t *d_rotate_left(bst_node_t *n)
{
    n->right = s_rotate_right(n->right);
    return(s_rotate_left(n));
}

bst_node_t *avl_delete(bst_node_t *root, int val)
{
    if (!root)
    {
	printf("Val %d not found in the tree \r\n", val);
	return root;
    }

    if (val < root->val)
    {
	root->left = avl_delete(root->left, val);
	return root;
    } else if (val > root->val) {
	root->right = avl_delete(root->right, val);
	return root;
    } 
    if (root->left && root->right)
    {
        root->val = find_min(root)->val;
	root->right - avl_delete(root->right, root->val);
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
    return(root->height);
}

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

