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

// this is the actual subtraction function
void add_pos_neg(Money *m1, Money *m2)
{
    if (m1->cents >= m2->cents)
    {
        m1->cents -= m2->cents;
    }
    else
    {
        if (m1->dollars == 0)
        {
            m1->cents = m2->cents - m1->cents;
            m1->is_positive = false;
        }
        else
        {
            m1->cents = 100 - (m2->cents - m1->cents);
            m1->dollars--;
        }
    }

    if (m1->is_positive)
    {
        if (m1->dollars >= m2->dollars)
        {
            m1->dollars -= m2->dollars;
        } 
        else
        {
            m1->dollars = m2->dollars - m1->dollars - 1;
            m1->cents = 100 - m1->cents;
            m1->is_positive = false;
        }
    }
    else
    {
        m1->dollars += m2->dollars;
    }
    
}

void add_neg_pos(Money *m1, Money *m2)
{
    Money *temp = make_money(m1->dollars, m1->cents, true);
    
    m1->dollars = m2->dollars;
    m1->cents = m2->cents;
    m1->is_positive = m2->is_positive;
    
    add_pos_neg(m1, temp);
    temp->free_me(temp);
}

void add_neg_neg(Money *m1, Money *m2)
{
    add_pos_pos(m1, m2);
}

void add_money(Money *m1, Money *m2)
{
    if (m1->is_positive && m2->is_positive)
    {
        add_pos_pos(m1, m2);
    }
    else if (m1->is_positive && !m2->is_positive)
    {
        add_pos_neg(m1, m2);
    }
    else if (!m1->is_positive && m2->is_positive)
    {
        add_neg_pos(m1, m2);
    }
    else
    {
        add_neg_neg(m1, m2);
    }
}

void subtract_money(Money *m1, Money *m2)
{
    // to subtract, just flip the sign of the second value
    m2->is_positive = !m2->is_positive;
    add_money(m1, m2);
    m2->is_positive = !m2->is_positive;
}
