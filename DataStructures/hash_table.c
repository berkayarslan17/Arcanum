#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define NAME_SIZE 20
#define TABLE_SIZE 20

typedef struct {
    char name[NAME_SIZE];
    unsigned int age;
    unsigned int height;
} person_t;

person_t *hash_table[TABLE_SIZE];

static unsigned int hash(const char *p_name)
{
    unsigned int len = strnlen(p_name, NAME_SIZE);
    unsigned int hash = 0;

    for(int i = 0; i < len; i++)
    {
        hash += p_name[i];
        hash = (hash * p_name[i]) % TABLE_SIZE;
    }

    return hash;
}

void hash_table_init(void)
{
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        hash_table[i] = NULL;
    }
}

bool hash_table_insert_person(const person_t *p_person)
{
    bool is_success = true;
    unsigned int idx = hash(p_person->name);

    if(hash_table[idx] == NULL)
    {
        hash_table[idx] = p_person;
    }
    else
    {
        is_success = false;
    }

    return is_success;
}

bool hash_table_delete_person(const person_t *p_person)
{
    bool is_success = true;
    unsigned int idx = hash(p_person->name);

    if(hash_table[idx] != NULL && !memcmp(hash_table[idx]->name, p_person->name, NAME_SIZE))
    {
        hash_table[idx] = NULL;
    }
    else
    {
        is_success = false;
    }

    return is_success;
}

person_t *hash_table_lookup(const char *p_name)
{
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        if(hash_table[i] && strncmp(p_name, hash_table[i]->name, NAME_SIZE) == 0)
        {
            return hash_table[i];
        }
    }

    return NULL;
}

int hash_table_find(const char *p_name)
{    
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        if(hash_table[i] && strncmp(p_name, hash_table[i]->name, NAME_SIZE) == 0)
        {
            return i;
        }
    }

    return -1;
}

void hash_table_print(void)
{
    printf("HASH TABLE\n");

    for(int i = 0; i < TABLE_SIZE; i++)
    {
        printf("Idx: %d\t\t\tAddress:%p\t\n", i, hash_table[i]);
    }
}

int main()
{
    person_t person1 = {
        .name = "Berkay",
        .age = 26,
        .height = 191
    };

    person_t person2 = {
        .name = "Fatih",
        .age = 26,
        .height = 181
    };

    hash_table_init();

    hash_table_insert_person(&person1);
    hash_table_print();
    hash_table_insert_person(&person2);
    hash_table_print();
    person_t *tmp = hash_table_lookup("Berkay");
    int idx = hash_table_find("Berkay");
    printf("lookup person: %p, idx: %d\n", tmp, idx);
}