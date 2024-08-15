#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "utils.h"

// works better than floats

typedef struct Money
{
    // TODO: change to allow for increments of 1000, i.e. millions, billions, trillions, etc.
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
    // TODO: find a better way to do this? don't return a string you have to free
    if (!m->is_positive)
    {
        printf("-");
    }
    printf("$%ld.", m->dollars);
    if (m->cents < 9)
    {
        printf("0%u", m->cents);
    }
    else
    {
        printf("%u", m->cents);
    }
    
}

comparer_R compare_positive(Money *m1, Money *m2)
{
    if (m1->dollars > m2->dollars)
    {
        return greater;
    }
    else if (m1->dollars == m2->dollars)
    {
        if (m1->cents > m2->cents)
        {
            return greater;
        }
        else
        {
            return less;
        }
    }
    else
    {
        return less;
    }
}

comparer_R compare_negative(Money *m1, Money *m2)
{
    return compare_positive(m1, m2) * -1;
}


comparer_R compare_same_sign(Money *m1, Money *m2)
{
    // TODO: implement this
    if (m1->is_positive)
    {
        return compare_positive(m1, m2);
    }
    else
    {
        return compare_negative(m1, m2);
    }
}

comparer_R compare_money(Money *m1, Money *m2)
{
    if (m1->is_positive && !m2->is_positive)
    {
        return greater;
    }
    else if (!m1->is_positive && m2->is_positive)
    {
        return less;
    }
    else if (m1->dollars == m2->dollars && m1->cents == m2->cents && m1->is_positive == m2->is_positive)
    {
        return equal;
    }
    else
    {
        return compare_same_sign(m1, m2);
    }
    
}

comparer_R compare_money_val(Money *m, uint64_t dollars, uint8_t cents, bool_R is_positive)
{
    Money *temp_money = make_money(dollars, cents, is_positive);
    comparer_R res = compare_money(m, temp_money);
    temp_money->free_me(temp_money);
    return res;
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
    m2->is_positive = !m2->is_positive;
    add_money(m1, m2);
    m2->is_positive = !m2->is_positive;
}

void add_money_val(Money *m, uint64_t dollars, uint8_t cents, bool_R is_positive)
{
    Money *temp_money = make_money(dollars, cents, is_positive);
    add_money(m, temp_money);
    temp_money->free_me(temp_money);
}
