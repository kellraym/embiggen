#ifndef MONEY_H
#define MONEY_H

#include "money.c"
#include "utils.h"

typedef struct Money Money;

Money *make_money(uint64_t dollars, uint8_t cents, bool_R is_negative);
// returns an initialized Money struct
// adds free_money as m->free_me
void print_money(Money *m);
// prints value of m as "$<dollars>.<cents>"
void add_money(Money *m1, Money *m2);
// adds m2 to m1, modifies m1
void subtract_money(Money *m1, Money *m2);
// subtracts m2 from m1, modifies m1

#endif
