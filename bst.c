#include <stdio.h>
#include <stdlib.h>

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

