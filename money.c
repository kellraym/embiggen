#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "utils.h"

// works better than floats

typedef struct Money
{
    int64_t dollars;
    uint8_t cents;
    bool_R is_positive;
    void (*free_me)(struct Money *m);
} Money;

void free_money(Money *m)
{
    free(m);
}

Money *make_money(uint64_t dollars, uint8_t cents, bool_R is_positive)
{
    Money *m = malloc(sizeof(Money));
    m->dollars = dollars;
    m->cents = cents;
    m->is_positive = is_positive;
    m->free_me = free_money;
    return m;
}

void print_money(Money *m)
{
    if (!m->is_positive)
    {
        printf("-");
    }
    printf("$%ld.%u", m->dollars, m->cents);
}

void subtract_money(Money *m1, Money *m2)
{
    // TODO: implement this
    if (m1->dollars >= m2->dollars) // TODO: double check this i.e. 0.5 - 0.6
    {
        if (m1->cents < m2->cents)
        {
            m1->dollars -= 1;
            if (m1->dollars < 0)
            {
                m1->cents = m2->cents - m1->cents;
            }
            else
            {
                uint8_t remainder = m2->cents - m1->cents;
                m1->cents = 100 - remainder;
            }
        }
        else
        {
            m1->cents -= m2->cents;
        }
    }
    else
    {
        m1->dollars = (m2->dollars - m1->dollars) * -1;
        if (m1->cents < m2->cents)
        {
            uint8_t remainder = m2->cents - m1->cents;
            m1->cents = 100 - remainder;
        }
        else
        {
            m1->cents += m2->cents;
        }
    }
}

void add_pos_pos(Money *m1, Money *m2)
{
    m1->dollars += m2->dollars;
    m1->cents += m2->cents;
    if (m1->cents >= 100)
    {
        m1->dollars += 1;
        m1->cents -= 100;
    }
}


void add_money(Money *m1, Money *m2)
{
    if (m1->is_positive && m2->is_positive)
    {
        add_pos_pos(m1, m2);
    }
    else if (m1->is_positive && !m2->is_positive)
    {
        // TODO: make this work
    }
}

