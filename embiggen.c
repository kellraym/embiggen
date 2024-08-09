#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.h"

#define NUM_OPTIONS 3

typedef struct Money
{
    int dollars;
    int8_t cents;
    void (*free_me)(struct Money *m);
} Money;

void free_money(Money *m)
{
    free(m);
}
Money *make_money(int dollars, int8_t cents)
{
    Money *m = malloc(sizeof(Money));
    m->dollars = dollars;
    m->cents = cents;
    m->free_me = free_money;
    return m;
}

char *options[] = 
{
    "0. Quit",
    "1. Save ten cents", // refactor to make this, look for change. finds a random amount of money between 0.00 and 1.00
    "2. Buy lemonade stand",
};

void clrscr()
{
    system("clear");
}

void clear_stdin()
{
    while (getchar() != 'n');
}

bool_R is_numeric(char c)
{
    // TODO: alter to only account for available options
    bool_R res = (c >= '0' && c <= '9');
    return res;
}

void print_options(float *total)
{
    clrscr();
    printf("Welcome to Embiggen\n");
    printf("You have $%.02f\n", *total);
    for (int i = 0; i < NUM_OPTIONS; i++)
    {
        printf("%s\n", options[i]);
    }
}

bool_R execute_option(int option, float *total, float *income)
{
    // add options to buy/upgrade stuff
    switch(option)
    {
        case 0:
            return false; 
        case 1:
            *total += .1;
            break;
        case 2:
            if (*total > 4.99)
            {
                *total -= 5.0;
                *income += 1.0;
                // TODO: how do I get message to persist?
                printf("Congratulations on your purchase!\npress enter to continue");
                printf("Your income is now $%.02f\n", *income);
                sleep(1);
            }
            else
            {
                printf("Not enough money, you only have $%.02f\n", *total);
                sleep(1);
            }
            break;
        default: 
            break;
    }
    printf("Adding %.02f", *income);
    *total += *income;
    return true;
}

int get_option(float *total, float *income)
{
    // take arguments specifying available options
    // TODO: incorporate q/Q as quit option
    int8_t option;

    print_options(total);
    // option = getch();
    option = getchar() - '0';
    return execute_option(option, total, income);
    // TODO: notify user that they should enter a number between x, x
}

int run_embiggen()
{
    // TODO: change total convention, don't use float, use a int_8 for cents and int_64 for 
    float total = 0.0;
    float income = 0.0;
    while (get_option(&total, &income));
    return 1;
}
