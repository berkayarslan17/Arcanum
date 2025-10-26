/**
 * @file doubly_linked_list.c
 * @brief Doubly Linked List Implementation in C
 *
 * This file provides an implementation of a generic doubly linked list
 * supporting insertion and removal of elements from both the head and tail.
 * Each node stores an integer value and maintains pointers to its neighbors,
 * enabling efficient bidirectional traversal.
 *
 * The API offers a minimal set of operations for creating, modifying, and
 * destroying lists:
 *   - Initialize and deinitialize list structures
 *   - Push elements to the head or tail
 *   - Pop elements from the head or tail
 *   - Print contents for debugging
 *
 * Example usage:
 * @code
 * LinkedList list;
 * list_init(&list);
 *
 * list_push_tail(&list, 10);
 * list_push_tail(&list, 20);
 * list_push_head(&list, 5);
 *
 * list_print(&list);
 *
 * int val;
 * list_pop_head(&list, &val);
 * printf("Popped: %d\n", val);
 *
 * list_deinit(&list);
 * @endcode
 *
 * @note This implementation uses dynamic memory allocation (`malloc`/`free`).
 *       Always deinitialize the list with @ref list_deinit to prevent leaks.
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
}Node;

typedef struct {
    Node *head;
    Node *tail;
    size_t size;
} LinkedList;

void list_init(LinkedList *list)
{
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void list_push_head(LinkedList *list, int value)
{
    Node *new_node = malloc(sizeof(Node));
    
    if(!new_node)
    {
        return;
    }
    
    new_node->data = value;
    new_node->prev = NULL;
    new_node->next = list->head;
    
    if(list->head)
    {
        list->head->prev = new_node;
    }
    else
    {
        list->tail = new_node;
    }
    
    list->head = new_node;
    list->size++;
}

void list_push_tail(LinkedList *list, int value)
{
    Node *new_node = malloc(sizeof(Node));
    
    if(!new_node)
    {
        return;
    }
    
    new_node->data = value;
    new_node->prev = list->tail;
    new_node->next = NULL;
    
    if(list->tail)
    {
        list->tail->next = new_node;
    }
    else
    {
        list->head = new_node;
    }
    
    list->tail = new_node;
    list->size++;
}

bool list_pop_head(LinkedList *list, int *out_value)
{
    if(!list->head)
    {
        return false;
    }
    
    *out_value = list->head->data;
    Node *temp_node = list->head;
    
    list->head = list->head->next;
    if(list->head)
    {
        list->head->prev = NULL;
    }
    else
    {
        list->tail = NULL;
    }
    
    
    free(temp_node);
    list->size--;
    
    return true;
}

bool list_pop_tail(LinkedList *list, int *out_value)
{
    if(!list->tail)
    {
        return false;
    }
    
    Node *temp = list->tail;
    *out_value = temp->data;
    
    
    list->tail = temp->prev;
    if(list->tail)
    {
        list->tail->next = NULL;
    }
    else
    {
        list->head = NULL;
    }
    
    free(temp);
    list->size--;
    
    return true;
}

/* Print list from head to tail */
void list_print(const LinkedList *list)
{
    const Node *cur = list->head;
    printf("List (%zu): ", list->size);
    while (cur) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

/* Free all nodes */
void list_deinit(LinkedList *list)
{
    Node *cur = list->head;
    while (cur) {
        Node *next = cur->next;
        free(cur);
        cur = next;
    }
    list->head = list->tail = NULL;
    list->size = 0;
}

/* Example usage */
int main(void)
{
    LinkedList list;
    list_init(&list);

    list_push_tail(&list, 10);
    list_push_tail(&list, 20);
    list_push_head(&list, 5);
    list_push_tail(&list, 30);
    list_print(&list);

    int val;
    list_pop_head(&list, &val);
    printf("Popped from head: %d\n", val);
    list_pop_tail(&list, &val);
    printf("Popped from tail: %d\n", val);
    list_print(&list);

    list_deinit(&list);
    return 0;
}