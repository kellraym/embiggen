#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "money.h"
#include "utils.h"

#define NUM_OPTIONS 3

void clrscr()
{
    system("clear");
}
void clear_stdin()
{
    while (getchar() != '\n');
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
    printf("You have ");
    print_money(total);
    printf("\n");
    for (int i = 0; i < NUM_OPTIONS; i++)
    {
        printf("%s\n", options[i]);
    }
}

bool_R execute_option(int8_t option, Money *total, Money *income)
{
    // TODO: raise the prices of purchased stuff
    // TODO: add options to buy/upgrade stuff
    // TODO: pass in a string pointer to display a message in print options
    switch(option)
    {
        case 0:
            return false; 
        case 1:
            add_money_val(total, 0, 10, true);
            break;
        case 2:
            if (compare_money_val(total, 4, 99, true) != -1)
            {
                add_money_val(total, 5, 0, false);
                add_money_val(income, 1, 0, true);
                printf("Congratulations on your purchase!");
                printf("Your income is now ");
                print_money(income);
                putchar('\n');
                sleep(1);
            }
            else
            {
                printf("Not enough money, you only have ");
                print_money(total);
                putchar('\n');
                sleep(1);
            }
            break;
        default: 
            break;
    }
    add_money(total, income);
    clear_stdin();
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
    // TODO: write stats to a file to continue, use three save files to select from or overwrite
    Money *total = make_money(0, 0, true);
    Money *income = make_money(0, 0, true);
    while (get_option(total, income));
    return 0;
}
