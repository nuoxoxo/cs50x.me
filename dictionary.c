// Implements a dictionary's functionality
#include <stdbool.h>
#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// a counter for the size func
int count;

//// free_family

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int x = hash(word);
    node *trav = table[x];

    //// while (trav->next != NULL)
    while (trav != NULL)
    {
        if (strcasecmp(trav->word, word) == 0)
        {
            return true;
        }
        trav = trav->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    int x = tolower(word[0]) - 97;
    return x;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dict = fopen(dictionary, "r");

    if (dict == NULL)
    {
        printf("Could not open dictioanry.\n");
        return false;
    }

    char buffer[LENGTH + 1];
    count = 0;

    while (fscanf(dict, "%s", buffer) != EOF) // fscanf(*src,format,*des)
    {
        node *new_word = malloc(sizeof(node));

        if (new_word == NULL)
        {
            printf("Not enough memory.");
            fclose(dict);
            return false;
        }

        strcpy(new_word->word, buffer); // strcpy(*des, *src)

        int bkt = hash(buffer);

        // always add to head ie unshift
        //// new_word->next = table[bkt]->next;
        new_word->next = table[bkt];
        table[bkt] = new_word;

        count++;
    }

    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    int x = count;
    return x;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

    //// node * cursor; // for keeping track
    //// node * tmp; // for free()ing

    for (int i = 0; i < N; i++)
    {
        node *trav = table[i];
        while (trav != NULL)
        {
            node *tmp = trav;
            trav = trav->next;
            free(tmp);
        }

        if (i == N - 1 && trav == NULL)
        {
            return true;
        }
    }
    //// free(cursor);
    //// free(tmp);
    return false;
}