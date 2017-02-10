#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 26 
#define NO_MORE -1
#define MAX_STR_LEN 50

typedef struct trie_node {
    struct trie_node *children[MAX_SIZE];
    char key[MAX_SIZE]; // Not required, just keeping for display purposes
    bool isLeaf;
} trie_node_t;

trie_node_t *trie_root;

trie_node_t *trie_insert(trie_node_t *, char *);
trie_node_t *trie_delete(trie_node_t *, char *);
bool trie_search(trie_node_t *, char *);
void trie_free(trie_node_t *);
void trie_preorder(trie_node_t *);

char help_str[] = "Allowed Operations: \n"
    "   -1 - Exit\r\n"
    "    1 - print help(this list)\r\n"
    "    2 <ele> - Insert ele\r\n"
    "    3 <ele> - Delete ele\r\n"
    "    4 <ele> - Find ele\r\n"
    "    5 - Display Tree via depth first traversal(pre-order) \r\n"
    ;

int main()
{
    trie_node_t *n;
    int op;
    char key[MAX_STR_LEN];

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
		getchar();
		memset(key,'\n',MAX_STR_LEN);
// why not scanf %s? because fgets offers protection against buffer overflows
// http://stackoverflow.com/questions/26955466/difference-between-gets-vs-scanf-vs-fgets-in-c-programming
		fgets(key, MAX_STR_LEN, stdin); 
		if(key[MAX_STR_LEN-1] != '\n')
		{
		    printf("Input string is more than allowed limit \r\n");
		    while ( getchar() != '\n' ); // flush any additional chars from stdin
		    break;
		}
		key[strlen(key)-1] = '\0'; // remove '\n' at the end

                trie_root = trie_insert(trie_root, key);
                break;
            case 3: /*Delete*/
		getchar();
		memset(key,'\n',MAX_STR_LEN);
// why not scanf %s? because fgets offers protection against buffer overflows
// http://stackoverflow.com/questions/26955466/difference-between-gets-vs-scanf-vs-fgets-in-c-programming
		fgets(key, MAX_STR_LEN, stdin); 
		if(key[MAX_STR_LEN-1] != '\n')
		{
		    printf("Input string is more than allowed limit \r\n");
		    while ( getchar() != '\n' ); // flush any additional chars from stdin
		    break;
		}
		key[strlen(key)-1] = '\0'; // remove '\n' at the end

                trie_root = trie_delete(trie_root, key);
                break;
            case 4: /*Search*/
		getchar();
		memset(key,'\n',MAX_STR_LEN);
// why not scanf %s? because fgets offers protection against buffer overflows
// http://stackoverflow.com/questions/26955466/difference-between-gets-vs-scanf-vs-fgets-in-c-programming
		fgets(key, MAX_STR_LEN, stdin); 
		if(key[MAX_STR_LEN-1] != '\n')
		{
		    printf("Input string is more than allowed limit \r\n");
		    while ( getchar() != '\n' ); // flush any additional chars from stdin
		    break;
		}
		key[strlen(key)-1] = '\0'; // remove '\n' at the end

                if (trie_search(trie_root, key))
		    printf("Found \r\n");
		else
		    printf("Not found\r\n");
                break;
            case 5: /* display entire tree via breadth first traversals*/
    		printf("	pre-order: \r\n");
		trie_preorder(trie_root);
   		printf("\r\n");
                break;
            default: /*error */
                printf("Invalid operation\r\n");
                break;
        }
        scanf("%d", &op);
    }

    printf("	pre-order: \r\n");
    trie_preorder(trie_root);
    printf("\r\n");
    trie_free(trie_root);
    trie_root=NULL;

    return 0;
}

trie_node_t *trie_insert(trie_node_t *root, char *key)
{
    int i, ind;
    trie_node_t *cur;

// TBD: string validation to ensure all characters are only lower-case alphabets
    if(!root)
    {
        root = (trie_node_t *)calloc(1, sizeof(struct trie_node));
        if (!root)
        {
            printf("Memory Allocation failure \r\n");
            return root;
        }
    }

    cur = root;
    for (i=0; i<strlen(key); i++)
    {
	ind = key[i] - 'a';
        if (!cur->children[ind])
        {
            cur->children[ind] = (trie_node_t *)calloc(1, sizeof(struct trie_node));
            if (!cur->children[ind])
	    {
                printf("Memory Allocation failure \r\n");
                return root;
            }
	}
        cur = cur->children[ind];
    }
    cur->isLeaf = 1;
    strcpy(cur->key, key);

    return root; 
}

trie_node_t *trie_delete(trie_node_t *root, char *key)
{
    int i, ind;
    trie_node_t *cur;

    if (!root)
    {
	printf("Key %s not found in the tree \r\n", key);
	return root;
    }

    cur = root;
    for (i=0; i<strlen(key); i++)
    {
	ind = key[i] - 'a';
        if (!cur->children[ind])
        {
	    printf("Key %s not found in the tree \r\n", key);
	    return root;
	}
        cur = cur->children[ind];
    }
    if (cur->isLeaf)
	cur->isLeaf = 0; // Not freeing unused nodes !!
    else {
	printf("Key %s not found in the tree \r\n", key);
	return root;
    }

    return root;
}

bool trie_search(trie_node_t *root, char *key)
{
    trie_node_t *cur;
    int i, ind;

    if (!root)
	return 0;

    cur = root;
    for (i=0; i<strlen(key); i++)
    {
	ind = key[i] - 'a';
        if (!cur->children[ind])
	    return 0;
        cur = cur->children[ind];
    }
    if (cur->isLeaf)
	return 1;
    return 0;
}

void trie_free(trie_node_t *root)
{
    int i;

    // Using preorder method to free the nodes
    if (!root)
        return;
    for (i=0; i<MAX_SIZE; i++)
    {
	trie_free(root->children[i]);
	root->children[i] = NULL;
    }
    free(root);
}

void trie_preorder(trie_node_t *root)
{
    int i;
    //trie_node_t *cur;

    if (!root)
        return;
    if (root->isLeaf)
        printf("%s\r\n", root->key);
    for (i=0; i<MAX_SIZE; i++)
	trie_preorder(root->children[i]);
}

