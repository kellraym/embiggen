#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.h"

#define NUM_OPTIONS 3

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

void print_options(Money *total)
{
    clrscr();
    printf("Welcome to Embiggen\n");
    // TODO: make a better way to print money
    printf("You have $%d.%d\n", total->dollars, total->cents);
    for (int i = 0; i < NUM_OPTIONS; i++)
    {
        printf("%s\n", options[i]);
    }
}

bool_R execute_option(int8_t option, Money *total, Money *income)
{
    // TODO: raise the prices of purchased stuff
    // TODO: add options to buy/upgrade stuff
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
                printf("Congratulations on your purchase!");
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

int get_option(Money *total, Money *income)
{
    // TODO: take arguments specifying available options
    // TODO: incorporate q/Q as quit option
    int8_t option;

    print_options(total);
    option = getchar() - '0';
    return execute_option(option, total, income);
    // TODO: notify user that they should enter a number between x, x
}

int run_embiggen()
{
    // TODO: change total convention, don't use float, use a int_8 for cents and int_64 for 
    // float total = 0.0;
    Money *total = make_money(0, 0);
    // float income = 0.0;
    Money *income = make_money(0, 0);
    while (get_option(total, income));
    return 1;
}
