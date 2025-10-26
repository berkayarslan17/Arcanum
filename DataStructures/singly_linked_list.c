/**
 * @file singly_linked_list.c
 * @brief Singly Linked List Implementation in C
 *
 * This file provides a minimal implementation of a singly linked list
 * supporting insertion and removal of elements from both the head and tail.
 * Each node stores an integer value and a pointer to the next node.
 *
 * The API offers basic list manipulation utilities such as:
 *   - Creating nodes dynamically
 *   - Appending elements to the head or tail
 *   - Removing elements from the head or tail
 *   - Searching for an element
 *   - Printing and freeing the list
 *
 * Example usage:
 * @code
 * Node *list = NULL;
 * int value;
 *
 * list_append_head(&list, 1);
 * list_append_tail(&list, 2);
 * list_append_tail(&list, 3);
 *
 * list_print(list);   // List: 1 -> 2 -> 3 -> NULL
 *
 * if (list_pop_head(&list, &value))
 *     printf("Popped head: %d\n", value);
 *
 * Node *found = list_find(list, 3);
 * printf("Find 3: %s\n", found ? "found" : "not found");
 *
 * list_free(&list);
 * @endcode
 *
 * @note This implementation uses dynamic memory allocation (`malloc` / `free`).
 *       Always call @ref list_free to release allocated memory before exiting.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node* node_create(int value)
{
    Node *new_node = malloc(sizeof(Node));
    if (!new_node)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void list_append_head(Node **head, int value)
{
    Node *new_node = node_create(value);
    new_node->next = *head;
    *head = new_node;
}

void list_append_tail(Node **head, int value)
{
    Node *new_node = node_create(value);

    if (*head == NULL)
    {
        *head = new_node;
        return;
    }

    Node *curr = *head;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    curr->next = new_node;
}

bool list_pop_head(Node **head, int *out_value)
{
    if (*head == NULL)
        return false;

    Node *temp = *head;
    *out_value = temp->value;
    *head = temp->next;
    free(temp);

    return true;
}

bool list_pop_tail(Node **head, int *out_value)
{
    if (*head == NULL)
        return false;

    Node *curr = *head;
    Node *prev = NULL;

    while (curr->next != NULL)
    {
        prev = curr;
        curr = curr->next;
    }

    *out_value = curr->value;

    if (prev == NULL)
    {
        *head = NULL; // only one node
    }
    else
    {
        prev->next = NULL;
    }

    free(curr);
    return true;
}

Node* list_find(Node *head, int value)
{
    for (Node *curr = head; curr != NULL; curr = curr->next)
    {
        if (curr->value == value)
            return curr;
    }
    return NULL;
}

void list_print(const Node *head)
{
    printf("List:");
    for (const Node *curr = head; curr != NULL; curr = curr->next)
    {
        printf(" %d ->", curr->value);
    }
    printf(" NULL\n");
}

void list_free(Node **head)
{
    Node *curr = *head;
    while (curr)
    {
        Node *next = curr->next;
        free(curr);
        curr = next;
    }
    *head = NULL;
}

int main(void)
{
    Node *list = NULL;
    int value = 0;

    list_append_head(&list, 2);
    list_append_head(&list, 3);
    list_append_head(&list, 4);
    list_append_tail(&list, 5);

    list_print(list);

    if (list_pop_head(&list, &value))
        printf("Popped head: %d\n", value);
    list_print(list);

    if (list_pop_tail(&list, &value))
        printf("Popped tail: %d\n", value);
    list_print(list);

    Node *found = list_find(list, 3);
    printf("Find 3: %s\n", found ? "found" : "not found");

    list_free(&list);
    list_print(list);

    return 0;
}
