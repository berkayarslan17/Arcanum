 
typedef struct {
    int *values;
    int head;
    int tail;
    int num_entries;
    int size;
}queue_t;

void init_queue(queue_t *p_queue, int max_size)
{
    p_queue->size = max_size;
    p_queue->values = malloc(sizeof(int) * max_size);
    p_queue->num_entries = 0;
    p_queue->head = 0;
    p_queue->tail = 0;
}

bool is_queue_empty(const queue_t *p_queue)
{
    return (p_queue->num_entries == 0);
}

bool is_queue_full(const queue_t *p_queue)
{
    return (p_queue->num_entries == p_queue->size);
}

void queue_deinit(queue_t *p_queue)
{
    free(p_queue->values);
    p_queue->size = 0;
    p_queue->num_entries = 0;
    p_queue->head = 0;
    p_queue->tail = 0;
}

bool queue_enqueue(queue_t *p_queue, int value)
{
    // If it is full, return false
    if(is_queue_full(p_queue))
    {
        return false;
    }
    
    p_queue->values[p_queue->tail] = value;
    p_queue->tail = (p_queue->tail + 1) % p_queue->size;
    p_queue->num_entries++;
    
    return true;
}

bool queue_dequeue(queue_t *p_queue, int *p_val)
{
    // If it is empty, return false
    if(is_queue_empty(p_queue))
    {
        return false;
    }
    
    *p_val = p_queue->values[p_queue->head];
    p_queue->head = (p_queue->head + 1) % p_queue->size;
    p_queue->num_entries--;
    
    return true;
}

