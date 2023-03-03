//***********************************************
// Author: Joe Mafrici
// Computes a factorial iteratively and recursively
//
#include <stdio.h>
#include <stdlib.h>
unsigned iterative_factorial(unsigned n);
//***********************************************
int main(int argc, char **argv)
{
    unsigned result;
    result = iterative_factorial(0);
    printf("result is %u\n", result);
    return EXIT_SUCCESS;
}
//***********************************************
//
unsigned iterative_factorial(unsigned n)
{
    unsigned result = 1;
    for (unsigned ii = n; ii > 1; --ii)
    {
        result = result * ii;
    }
    return result;
}
