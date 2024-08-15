typedef enum bool_R { false, true } bool_R;
typedef enum comparer_R { less = -1, equal, greater } comparer_R;

char *options[] = 
{
    "0. Quit",
    "1. Save ten cents", // refactor to make this, look for change. finds a random amount of money between 0.00 and 1.00
    "2. Buy lemonade stand",
};
