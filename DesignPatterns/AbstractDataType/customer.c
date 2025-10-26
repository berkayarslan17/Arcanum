
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "customer.h"

#define MAX_NO_OF_ORDERS 50

typedef struct {
    const char *name;
    address_t address;
    size_t no_of_orders;
    order_t orders[MAX_NO_OF_ORDERS];
} customer_t;

customer_t *customer_create(const char *p_name, const address_t *p_address)
{
    assert(p_name);
    assert(p_address);

    customer_t *p_customer = malloc(sizeof(customer_t));

    if(p_customer)
    {
        p_customer->name = p_name;
        memcpy(&p_customer->address, p_address, sizeof(address_t));
        p_customer->no_of_orders = 0;
    }

    return p_customer;
}

void customer_init(customer_t *p_customer, const char *p_name, const address_t*p_address)
{
    assert(p_customer);
    assert(p_name);
    assert(p_address);

    p_customer->p_name = p_name;
    p_customer->no_of_orders = 0;
    memcpy(&p_customer->p_address, p_address, sizeof(address_t));
    memset(orders, 0, sizeof(order_t) * MAX_NO_OF_ORDERS);

}

void customer_destroy(customer_t *p_customer)
{
    if(!p_customer)
    {
        return;
    }

    free(p_customer->p_name);
    free(p_customer);
}

bool customer_place_order(customer_t *p_customer, const order_t *p_order)
{
    assert(p_customer);
    assert(p_order);

    bool is_success = true;

    // Check if order array is full or not
    if(p_customer->no_of_orders == MAX_NO_OF_ORDERS)
    {
        is_success = false;
    }

    if(is_success)
    {
        // Place the order
        memcpy(&p_customer->orders[p_customer->no_of_orders], p_order, sizeof(order_t));

        // Increase the no of orders
        p_customer->no_of_orders++;
    }

    return is_success;
}

order_t *customer_pop_last_order(customer_t *p_customer)
{
    assert(p_customer);

    order_t *p_order = NULL;

    if(p_customer->no_of_orders)
    {
        p_customer->no_of_orders--;
        p_order = &p_customer->orders[p_customer->no_of_orders];
    }

    return p_order;
}