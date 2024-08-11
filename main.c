// #include "embiggen.h"
#include "utils.h"

int main()
{
    Money *m1 = make_money(200, 50);
    Money *m2 = make_money(400, 50);
    print_money(m1);
    printf("\n");
    add_money(m1, m2);
    print_money(m1);
    printf("\n"); 
    return 0; 
   // return run_embiggen();
}
