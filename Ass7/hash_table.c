/*
 * CS 11, C Track, lab 7
 *
 * FILE: hash_table.c
 *
 *       Implementation of the hash table functionality.
 *
 */

/*
 * Attempted extra credit question. Look at main.c please!
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "memcheck.h"


/*** Hash function. ***/

int hash(char *s)
{
    int val = 0;
    while (*s != '\0') {
        val += (int) *s;
        s++;
    }
    return val % 128;
}


/*** Linked list utilities. ***/

/* Create a single node. */
node *create_node(char *key, int value)
{
    node *result = (node *)malloc(sizeof(node));

    if (result == NULL)
    {
        fprintf(stderr, "Fatal error: out of memory. "
                "Terminating program.\n");
        exit(EXIT_FAILURE);
    }

    result->key = key;  
    result->next = NULL;
    result->value = value;

    return result;
}


/* Free all the nodes of a linked list. */
void free_list(node *list)
{
    node *temp;

    while (list != NULL)
    {
        temp = list;
        list = list->next;
        free(temp->key);
        free(temp);
    }
}


/*** Hash table utilities. ***/

/* Create a new hash table. */
hash_table *create_hash_table()
{
    int i;
    hash_table *ht = (hash_table *) malloc(sizeof(hash_table));
    node **result = (node **) malloc(NSLOTS * sizeof(node *)), **p;

    if (result == NULL)
    {
        fprintf(stderr, "Fatal error: out of memory. "
                "Terminating program.\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0, p = result; i < NSLOTS; i++, p++) {
        *p = NULL;
    }

    ht->slot = result;
    return ht;
}


/* Free a hash table. */
void free_hash_table(hash_table *ht)
{
    int i;
    node **arr = ht->slot, *temp;

    for (i = 0; i < NSLOTS; i++, arr++) {
        temp = *arr;
        free_list(temp);
    }   

    free(ht->slot);
    free(ht);

}


/*
 * Look for a key in the hash table.  Return 0 if not found.
 * If it is found return the associated value.
 */
int get_value(hash_table *ht, char *key)
{
    int idx = hash(key);
    node *list = *(ht->slot + idx);
    int value = 0;

    while (list != NULL) {
        if (strcmp(list->key, key) == 0) {
            value = list->value;
            break;
        }
        list = list->next;
    }

    return value;
}


/*
 * Set the value stored at a key.  If the key is not in the table,
 * create a new node and set the value to 'value'.  Note that this
 * function alters the hash table that was passed to it.
 */
void set_value(hash_table *ht, char *key, int value)
{
    int idx = hash(key);
    node *list = *(ht->slot + idx);
    int found = 0;

    while (list != NULL) {
        if (strcmp(list->key, key) == 0) {
            list->value = value;
            found = 1;
            free(key);
            break;
        }
        list = list->next;
    }

    if (!(found)) {
        list = *(ht->slot + idx);
        if (list == NULL) {
            *(ht->slot + idx) = create_node(key, value);
        }
        else {
            while (list->next != NULL) {
            list = list->next;
            }
            list->next = create_node(key, value);
        }
        
    }
}


/* Print out the contents of the hash table as key/value pairs. */
void print_hash_table(hash_table *ht)
{
    node **p, *list;
    int i;

    for (i = 0, p = ht->slot; i < 128; i++, p++) {
        if (*p != NULL) {
            list = *p;
            while (list != NULL) {
                printf("%s %d\n", list->key, list->value);
                list = list->next;
            }
        }
    }
}