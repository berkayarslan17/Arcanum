typedef struct node{
    int val;
    struct node *p_next;
}node_t;

typedef struct {
    node_t *p_head;
    node_t *p_tail;
}sll_t;

node_t *allocate_node(int val)
{
    node_t *p_new_node = malloc(sizeof(node_t));
    p_new_node->val = val;
    p_new_node->next = NULL;

    return p_new_node;
}

void free_node(node_t *p_node)
{
    p_node->val = 0;
    p_node->next = NULL;
    free(p_node);
}

void list_init(sll_t *p_list, int val)
{
    node_t *p_new_node = allocate_node(val);
    p_list->p_head = p_new_node;
    p_list->p_tail = p_new_node;
}

void list_append_to_head(sll_t *p_list, int val)
{
    assert(p_list);

    node_t *p_new_node = allocate_node(val);

    if(p_list->p_head)
    {
        p_new_node->p_next = p_list->p_head;
    }
    else
    {
        p_list->p_tail = p_new_node;
    }

    p_list->p_head = p_new_node;
    
}

void list_append_to_tail(sll_t *p_list, int val)
{
    assert(p_list);

    node_t *p_new_node = allocate_node(val);

    if(p_list->p_tail)
    {
        p_list->p_tail->p_next = p_new_node;
    }
    else
    {
        p_list->p_head = p_new_node;
    }

    p_list->p_tail = p_new_node;
}

int list_pop_from_head(sll_t *p_list)
{
    assert(p_list);

    res = INT_MIN;

    if(p_list->p_head)
    {
        res = p_list->p_head->val;

        node_t *p_temp = p_list->p_head->p_next;
        free_node(p_list->p_head);
        p_list->p_head = p_temp;

        if(!p_temp)
        {
            p_list->tail = NULL;
        }
    }

    return res;
}

int list_pop_from_tail(sll_t *p_list)
{
    assert(p_list);

    res = INT_MIN;

    if(p_list->p_tail)
    {
        res = p_list->p_tail->val;
    
        node_t *p_prev = NULL;
        node_t *p_cur = p_list->p_head;

        while(p_cur->p_next != NULL)
        {
            p_prev = p_cur;
            p_cur = p_cur->p_next;
        }

        free_node(p_list->p_tail);
        p_list->p_tail = p_prev;

        if(!p_prev)
        {
            p_list->p_head = NULL;
        }
        else
        {
            p_prev->p_next = NULL;
        }
    }

    return res;
}

void print_list(const sll_t *p_list)
{
    printf("List: ");
    node_t *p_cur = p_list->p_head;
    while (p_cur)
    {
        printf("%d -> ", p_cur->val);
        p_cur = p_cur->p_next;
    }
    printf("NULL\n");
}


// SLL API Usage
int main(void)
{
    sll_t list = {0};

    printf("Initializing list with value 10\n");
    list_init(&list, 10);
    print_list(&list);

    printf("\nAppending 20 to head\n");
    list_append_to_head(&list, 20);
    print_list(&list);

    printf("\nAppending 30 to tail\n");
    list_append_to_tail(&list, 30);
    print_list(&list);

    printf("\nAppending 40 to tail\n");
    list_append_to_tail(&list, 40);
    print_list(&list);

    printf("\nPopping from head: ");
    int val = list_pop_from_head(&list);
    printf("%d\n", val);
    print_list(&list);

    printf("\nPopping from tail: ");
    val = list_pop_from_tail(&list);
    printf("%d\n", val);
    print_list(&list);

    printf("\nPopping from tail again: ");
    val = list_pop_from_tail(&list);
    printf("%d\n", val);
    print_list(&list);

    printf("\nPopping from head: ");
    val = list_pop_from_head(&list);
    printf("%d\n", val);
    print_list(&list);

    printf("\nPopping from empty list (should return INT_MIN): ");
    val = list_pop_from_tail(&list);
    printf("%d\n", val);
    print_list(&list);

    return 0;
}
