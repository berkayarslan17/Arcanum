#ifndef CUSTOMER_H
#define CUSTOMER_H

typedef struct customer_t customer_t; // Opaque type

customer_t *customer_create(const char *p_name, const address_t *p_address);

void customer_destroy(customer_t *p_customer);

void customer_init(customer_t *p_customer, const char *p_name, const address_t*p_address);

void customer_place_order(customer_t *p_customer, const order_t *p_order);

order_t *customer_pop_last_order(customer_t *p_customer);

/* A lot of other related functions...*/

#endif // CUSTOMER_H