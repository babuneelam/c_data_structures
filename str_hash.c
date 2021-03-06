#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NO_MORE -1
#define MAX_HASH 16384
#define MAX_STR_LEN 50

typedef struct hash_node {	
    struct hash_node *next;
    int hash_idx;
    int val; // int declared here, but change date type as necessary
	       // use this if we need to map keys --> values (as in c++ hash map)

    char *key; 
} hash_node_t;

typedef struct hash_table {
    hash_node_t *tbl[MAX_HASH];
    int chain_len[MAX_HASH];
    int cur_size;
} hash_table_t;

hash_table_t *hash_tbl;

/*TBD: Locking */

/*Funtion prototypes*/
int ht_create(void);
void ht_free(void);
hash_node_t *ht_search(char *);
hash_node_t *ht_search_idx(char *, int);
hash_node_t *ht_insert(char *, int);
int ht_delete(char *);
void ht_display(void);
void ht_display_idx(int);
static __always_inline unsigned int hash_fn(char *);
int valid_key(char *);

char help_str[] = "Allowed Operations: \n"
    "   -1 - Exit\r\n"
    "    1 - print help(this list)\r\n"
    "    2 <str key> <enter> <val>- Insert str\r\n"
    "    3 <str key> - Delete str\r\n"
    "    4 <str key> - search str\r\n"
    "    5 <hash_ind> - disply str at <hash_ind>\r\n"
    "    6 - display list\r\n"
    ;

int main()
{
    hash_node_t *h;
    int op, val, idx, ret;
    char key[MAX_STR_LEN];
   
    if (ht_create() == 0)
        return 0;

    printf("%s", help_str);
    scanf("%d", &op);
    while(op != NO_MORE)
    {
	switch(op)
	{
	    case 1:
		printf("%s", help_str);
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
		scanf("%d", &val);
		h = ht_insert(key, val);
		break;
	    case 3: /*delete */
		getchar();
		memset(key,'\n',MAX_STR_LEN);
		fgets(key, MAX_STR_LEN, stdin);
		if(key[MAX_STR_LEN-1] != '\n')
		{
		    printf("Input string is more than allowed limit \r\n");
		    while ( getchar() != '\n' ); // flush any additional chars from stdin
		    break;
		}
		key[strlen(key)-1] = '\0'; // remove '\n' at the end
		ret = ht_delete(key);
		if (!ret)
		    printf("key %s not found in hash table\r\n", key);
		break;
	    case 4: /* search */
		getchar();
		memset(key,'\n',MAX_STR_LEN);
		fgets(key, MAX_STR_LEN, stdin);
		if(key[MAX_STR_LEN-1] != '\n')
		{
		    printf("Input string is more than allowed limit \r\n");
		    while ( getchar() != '\n' ); // flush any additional chars from stdin
		    break;
		}
		key[strlen(key)-1] = '\0'; // remove '\n' at the end
		h = ht_search(key);
		if (h)
		    printf("Found at Hash Index %d Val = %d\r\n", h->hash_idx, h->val);
		else
		    printf("key %s not found in hash table\r\n", key);
		break;
	    case 5: /*display hash nodes at an index */
		scanf("%d", &idx);
		ht_display_idx(idx);
		break;
	    case 6: /* display entire hash table */
		ht_display();
		break;
	    default: /*error */
   		printf("Invalid operation\r\n");
		break;
	}
        scanf("%d", &op);
    }

    ht_display();
    ht_free();

    return 0;
}

hash_node_t *ht_insert(char *key, int val)
{
    int hash_val;
    hash_node_t *h, *cur;

    if (!valid_key(key))
    {
        printf("Invalid key\r\n");
        return NULL;
    }
    hash_val=hash_fn(key);
    /* check if it exists */
    h=ht_search_idx(key, hash_val);
    if (h)
	return h;
    h = (hash_node_t *)malloc(sizeof(struct hash_node));
    if (!h)
	return NULL;
    h->key = (char *)malloc(strlen(key));
    if (!h->key)
    {
	free(h);
	return NULL;
    }
    strcpy(h->key, key);
    h->val = val;
    h->hash_idx = hash_val;
    h->next=NULL;

    /* increment counters*/
    hash_tbl->cur_size++;
    hash_tbl->chain_len[hash_val]++;

    /* Insert at the tail */
    cur=hash_tbl->tbl[hash_val];
    if (!cur)
    {
        hash_tbl->tbl[hash_val] = h;
        return h;
    }
    while(cur->next)
        cur=cur->next;
    cur->next=h;
    return h;
}

int ht_delete(char *key)
{
    int hash_val;
    hash_node_t *h, *cur;

    if (!valid_key(key))
    {
        printf("Invalid key\r\n");
        return -1;
    }
    hash_val=hash_fn(key);
    cur=hash_tbl->tbl[hash_val];
    if (!cur) // Key not found
        return -1;
    if (!strcmp(cur->key, key))
    {
        hash_tbl->tbl[hash_val] = cur->next;
        hash_tbl->cur_size--;
        hash_tbl->chain_len[hash_val]--;
	free(cur->key);
	free(cur);
	return 1;
    }
        
    while ((cur->next) && (strcmp(cur->next->key, key)))
        cur=cur->next;
    if (!cur->next) // Key not found
        return -1;
    h = cur->next;
    cur->next = cur->next->next;
    hash_tbl->cur_size--;
    hash_tbl->chain_len[hash_val]--;
    free(h->key);
    free(h);
    return 1;
}

hash_node_t *ht_search(char *key)
{
    int hash_val;
    hash_node_t *h;

    if (!valid_key(key))
    {
        printf("Invalid key\r\n");
        return NULL;
    }
    hash_val=hash_fn(key);
    h=hash_tbl->tbl[hash_val];
    while ((h) && (strcmp(h->key, key)))
	h=h->next;
    return h;
}

hash_node_t *ht_search_idx(char *key, int idx)
{
    hash_node_t *h;

    if (!valid_key(key))
    {
        printf("Invalid key\r\n");
        return NULL;
    }
    if(idx >= MAX_HASH)
	return NULL;

    h=hash_tbl->tbl[idx];
    while ((h) && (strcmp(h->key, key)))
	h = h->next;
    return h;
}


static __always_inline unsigned int hash_fn(char *key)
{
    int i;
    unsigned long hsh=123487837; // starting with some random number
				 // so that input alone doesn't determine
				 // the hash output

    for (i=0; i<strlen(key); i++)
        hsh ^= (hsh<<5) + (unsigned long)key[i] +(hsh >>2);
    return(hsh % MAX_HASH); 
}

int valid_key(char *key)
{
    int i;

    // Possible Validation1: Allow only alphabets
    // Possible Validation2: Allow any charater

    // Allow only ASCII characters
    for (i=0; i<strlen(key); i++)
        if ((key[i] <0) || (key[i] >127))
            return 0;

    return 1;
}

int ht_create()
{
    int i;

    hash_tbl = (hash_table_t *)calloc(1, sizeof(struct hash_table));
    if (!hash_tbl) {
	printf("%s: Failed to allocate MLT table\n", __FUNCTION__);
	return 0;
    }

    return 1;
}

void ht_free()
{
    hash_node_t *h, *cur;
    int i;

    for(i=0; i< MAX_HASH; i++)
    {
	h = hash_tbl->tbl[i];
        if (!hash_tbl->chain_len[i])
            continue;
	while(h)
	{
	    cur=h;
	    h=h->next;
	    free(cur->key);
	    free(cur);
	}
	hash_tbl->tbl[i]=NULL;
    }

    free(hash_tbl);
    hash_tbl=NULL;
    return;
}


void ht_display()
{
    hash_node_t *h;
    int i;

    for(i=0; i< MAX_HASH; i++)
    {
	h = hash_tbl->tbl[i];
        if (!hash_tbl->chain_len[i])
            continue;
	printf("Hash Index %d: ", i);
	while(h)
	{
	    printf("key %s val %d, ", h->key, h->val);
	    h=h->next;
	}
	printf("\r\n");
    }
    printf("\r\n");
    return;
}


void ht_display_idx(int idx)
{
    hash_node_t *h;

    if(idx > MAX_HASH)
        return;

    h = hash_tbl->tbl[idx];
    if (!h)
        return;
    printf("Hash Index %d: ", idx);
    while(h)
    {
	printf("key %s val %d, ", h->key, h->val);
	h=h->next;
    }
    printf("\r\n");

    return;
}


