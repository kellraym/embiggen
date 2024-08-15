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
comparer_R compare_money(Money *m1, Money *m2);
// returns -1 if m1 < m2, 0 if m1 == m2, 1 if m1 > m2
comparer_R compare_money_val(Money *m, uint64_t dollars, uint8_t cents, bool_R is_positive);
// compares money struct to constant value, uses dollars, cents, is_positive to build internal struct
void add_money(Money *m1, Money *m2);
// adds m2 to m1, modifies m1
void subtract_money(Money *m1, Money *m2);
// subtracts m2 from m1, modifies m1
void add_money_val(Money *m, uint64_t dollars, uint8_t cents, bool_R is_positive);
// adds a constant value to money, uses dollars, cents, is_positive to build internal money struct

#endif
