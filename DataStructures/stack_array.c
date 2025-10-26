#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define STACK_CAPACITY  10  // You can change this size

typedef struct {
    int data[STACK_CAPACITY];
    int top;   // index of the top element (-1 when empty)
} Stack;

/* Initialize the stack */
void stack_init(Stack *s)
{
    s->top = -1;
}

/* Check if stack is empty */
bool stack_is_empty(const Stack *s)
{
    return s->top == -1;
}

/* Check if stack is full */
bool stack_is_full(const Stack *s)
{
    return s->top == STACK_CAPACITY - 1;
}

/* Push value onto stack */
bool stack_push(Stack *s, int value)
{
    if (stack_is_full(s))
    {
        printf("Stack overflow!\n");
        return false;
    }

    s->data[++s->top] = value;
    return true;
}

/* Pop value from stack */
bool stack_pop(Stack *s, int *out_value)
{
    if (stack_is_empty(s))
    {
        printf("Stack underflow!\n");
        return false;
    }

    *out_value = s->data[s->top--];
    return true;
}

/* Peek at the top value without popping */
bool stack_peek(const Stack *s, int *out_value)
{
    if (stack_is_empty(s))
    {
        return false;
    }

    *out_value = s->data[s->top];
    return true;
}

/* Print the stack contents */
void stack_print(const Stack *s)
{
    printf("Stack (size=%d): ", s->top + 1);
    for (int i = 0; i <= s->top; ++i)
        printf("%d ", s->data[i]);
    printf("\n");
}

/* Example usage */
int main(void)
{
    Stack s;
    stack_init(&s);

    stack_push(&s, 10);
    stack_push(&s, 20);
    stack_push(&s, 30);

    stack_print(&s);

    int val;
    stack_pop(&s, &val);
    printf("Popped: %d\n", val);

    stack_peek(&s, &val);
    printf("Top element: %d\n", val);

    stack_print(&s);

    return 0;
}
