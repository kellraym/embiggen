#ifndef MONEY_H
#define MONEY_H

#include "money.c"

typedef struct Money Money;

void free_money(Money *m);
Money *make_money(long dollars, uint8_t cents);
void print_money(Money *m);
void add_money(Money *m1, Money *m2);
void subtract_money(Money *m1, Money *m2);

#endif
