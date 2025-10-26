#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Define a node structure */
typedef struct Node {
    int data;
    struct Node *next;
} Node;

/* Define the stack structure */
typedef struct {
    Node *top;
    size_t size;
} Stack;

/* Initialize stack */
void stack_init(Stack *stack)
{
    stack->top = NULL;
    stack->size = 0;
}

/* Check if stack is empty */
bool stack_is_empty(const Stack *stack)
{
    return (stack->top == NULL);
}

/* Push value onto stack */
bool stack_push(Stack *stack, int value)
{
    Node *new_node = malloc(sizeof(Node));
    if (!new_node)
        return false;  // allocation failed

    new_node->data = value;
    new_node->next = stack->top;
    stack->top = new_node;
    stack->size++;
    return true;
}

/* Pop value from stack */
bool stack_pop(Stack *stack, int *out_value)
{
    if (stack_is_empty(stack))
        return false;

    Node *temp = stack->top;
    *out_value = temp->data;

    stack->top = temp->next;
    free(temp);
    stack->size--;
    return true;
}

/* Peek at top element without popping */
bool stack_peek(const Stack *stack, int *out_value)
{
    if (stack_is_empty(stack))
        return false;

    *out_value = stack->top->data;
    return true;
}

/* Free all stack nodes */
void stack_free(Stack *stack)
{
    Node *curr = stack->top;
    while (curr)
    {
        Node *next = curr->next;
        free(curr);
        curr = next;
    }
    stack->top = NULL;
    stack->size = 0;
}

/* Print stack contents (top to bottom) */
void stack_print(const Stack *stack)
{
    Node *curr = stack->top;
    printf("Stack (size=%zu): ", stack->size);
    while (curr)
    {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

/* Example usage */
int main(void)
{
    Stack stack;
    stack_init(&stack);

    stack_push(&stack, 10);
    stack_push(&stack, 20);
    stack_push(&stack, 30);
    stack_print(&stack); // Stack: 30 20 10

    int val;
    stack_pop(&stack, &val);
    printf("Popped: %d\n", val);

    stack_peek(&stack, &val);
    printf("Top: %d\n", val);

    stack_print(&stack); // Stack: 20 10

    stack_free(&stack);
    return 0;
}
