#include "factorial.h"

int
factorial(int x)
{
    int i, result = 1;

    for (i = 1; i <= x; i++)
        result *= i;

    return result;
}
