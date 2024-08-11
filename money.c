#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Money
{
    long dollars;
    uint8_t cents;
    void (*free_me)(struct Money *m);
} Money;

void free_money(Money *m)
{
    free(m);
}

Money *make_money(long dollars, uint8_t cents)
{
    Money *m = malloc(sizeof(Money));
    m->dollars = dollars;
    m->cents = cents;
    m->free_me = free_money;
    return m;
}

void print_money(Money *m)
{
    printf("$%ld.%u", m->dollars, m->cents);
}

void add_money(Money *m1, Money *m2)
{
    // TODO: implement this
    m1->dollars += m2->dollars;
    m1->cents += m2->cents;
    if (m1->cents >= 100)
    {
        m1->dollars += 1;
        m1->cents -= 100;
    }
}

void subtract_money(Money *m1, Money *m2)
{
    // TODO: implement this
}
