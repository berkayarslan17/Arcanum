/*

Design a data structure for storing a very large (potentially unbounded) set of customers in memory. 

Each customer has: 

customer_id (unique identifier) 

customer_name 

Possibility others attributes 


The solution must support: 

Efficient insertion of new customers. 

if a customer with the same customer_id already exists, return the existing customer object instead of creating a new one. 

The insertion API has the following signature: 

customer_t *insert(unsigned customer_id, const char *customer_name) 
{
}

*/

// Declare the customer structure

/*
Implement insert function
- O(1) lookup, use hash table for this
- Implement a hash function that returns the index of the hash table
- If there is a collision, use chaining with linked list.
- If Dynamic allocation fails, return NULL.

*/

typedef struct customer{
  unsigned customer_id;
  char *p_customer_name;
  struct customer *next;
} customer_t;

customer_t *customers[HASH_TABLE_SIZE];

unsigned int hash(unsigned customer_id)
{
  return (customer_id % HASH_TABLE_SIZE);
}

customer_t *insert(unsigned customer_id, const char *p_customer_name)
{
  // Get index with hash
  unsigned idx = hash(customer_id);
  customer_t *p_customer = customers[idx];

  // Search the bucket first
    while(p_customer)
    {
      if(p_customer->customer_id == customer_id)
      {
        return p_customer;
      }

      p_customer = p_customer->next;
    }

    // If it reaches here, that means couldn't find in the chain
    customer_t *p_new_customer = malloc(sizeof(customer_t));

    if(!p_new_customer)
    {
      return NULL;
    }

    p_new_customer->customer_id = customer_id;
    p_new_customer->p_customer_name = p_customer_name;
    p_new_customer->next = customers[idx];
    customers[idx] = p_new_customer;

    return p_new_customer;
  }