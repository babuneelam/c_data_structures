#include <stdlib.h>
#include <stdio.h>

#define NO_MORE -1
#define MAX_HASH 16384 // 16K

typedef struct hash_node {	
    int key;
    int val; // int declared here, but change date type as necessary
	     // use this if we need to map keys --> values (as in c++ hash map)

    int hash_idx;
    struct hash_node *next;
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
hash_node_t *ht_search(int);
hash_node_t *ht_search_idx(int, int);
hash_node_t *ht_insert(int, int);
int ht_delete(int);
void ht_display(void);
void ht_display_idx(int);
static __always_inline unsigned int hash_fn(int);

char help_str[] = "Allowed Operations: \n"
    "   -1 - Exit\r\n"
    "    1 - print help(this list)\r\n"
    "    2 <int key> <val>- Insert ele\r\n"
    "    3 <int key> - Delete ele\r\n"
    "    4 <int key> - search ele\r\n"
    "    5 <hash_ind> - display ele at <hash_ind>\r\n"
    "    6 - display list\r\n"
    ;

int main()
{
    hash_node_t *h;
    int op, key, val, idx, ret;
   
    if (ht_create() == 0)
        return 0;

    printf("%s", help_str);
    scanf("%d", &op);
    while(op != NO_MORE)
    {
	switch(op)
	{
            case 1:
                printf("%s",help_str);
                break;
	    case 2: /*Insert*/
		scanf("%d%d", &key, &val);
		h = ht_insert(key, val);
		break;
	    case 3: /*delete */
		scanf("%d", &key);
		ret = ht_delete(key);
		if (!ret)
		    printf("key %d not found in hash table\r\n", key);
		break;
	    case 4: /* search */
		scanf("%d", &key);
		h = ht_search(key);
		if (h)
		    printf("Found at Hash Index %d Val = %d\r\n", h->hash_idx, h->val);
		else
		    printf("key %d not found in hash table\r\n", key);
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

hash_node_t *ht_insert(int key, int val)
{
    int hash_val;
    hash_node_t *h, *cur;

    hash_val=hash_fn(key);
    /* check if it exists */
    h=ht_search_idx(key, hash_val);
    if (h)
	return h;
    h = (hash_node_t *)malloc(sizeof(struct hash_node));
    if (!h)
        return NULL;
    h->key = key;
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

int ht_delete(int key)
{
    int hash_val;
    hash_node_t *h, *cur;

    hash_val=hash_fn(key);
    cur=hash_tbl->tbl[hash_val];
    if (!cur) // Key not found
        return -1;
    if (cur->key == key)
    {
        hash_tbl->tbl[hash_val] = cur->next;
        hash_tbl->cur_size--;
        hash_tbl->chain_len[hash_val]--;
        free(cur);
	return 1;
    }
        
    while ((cur->next) && (cur->next->key != key))
        cur=cur->next;
    if (!cur->next) // Key not found
        return -1;
    h = cur->next;
    cur->next = cur->next->next;
    hash_tbl->cur_size--;
    hash_tbl->chain_len[hash_val]--;
    free(h);
    return 1;
}

hash_node_t *ht_search(int key)
{
    int hash_val;
    hash_node_t *h;

    hash_val=hash_fn(key);
    h=hash_tbl->tbl[hash_val];
    while ((h) && (h->key != key))
	h=h->next;
    return h;
}

hash_node_t *ht_search_idx(int key, int idx)
{
    hash_node_t *h;

    if(idx >= MAX_HASH)
	return NULL;

    h=hash_tbl->tbl[idx];
    while ((h) && (h->key != key))
	h = h->next;
    return h;
}


static __always_inline unsigned int hash_fn(int key)
{
    return(key % MAX_HASH); //TBD: improvise
	//*stk_fn_hash = bob_jenkins_hash(*stk_fn_hash);
        // a = (a + 0x7ed55d16) + (a << 12);
        // a = (a ^ 0xc761c23c) ^ (a >> 19);
        // a = (a + 0x165667b1) + (a << 5);
        // a = (a + 0xd3a2646c) ^ (a << 9);
        // a = (a + 0xfd7046c5) + (a << 3);
        // a = (a ^ 0xb55a4f09) ^ (a >> 16);
	//return (*stk_fn_hash & (MLT_MAX_HASH - 1));

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
	    printf("key %d val %d, ", h->key, h->val);
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
	printf("key %d val %d, ", h->key, h->val);
	h=h->next;
    }
    printf("\r\n");

    return;
}


