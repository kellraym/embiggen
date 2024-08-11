// #include "embiggen.h"
#include "money.h"
#include "utils.h"

int main()
{
    Money *m1 = make_money(0, 50, true);
    Money *m2 = make_money(0, 80, true);
    print_money(m1);
    printf("\n");
    // subtract_money(m1, m2);
    add_money(m1, m2);
    print_money(m1);
    printf("\n"); 
    return 0; 
   // return run_embiggen();
    // extra comment
}
