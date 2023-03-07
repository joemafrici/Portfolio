//***********************************************
// Author: Joe Mafrici
// Computes a factorial iteratively and recursively
//
#include <stdio.h>
#include <stdlib.h>
unsigned iterative_factorial(unsigned n);
unsigned recursive_factorial(unsigned n);
//***********************************************
int main(int argc, char **argv)
{
    unsigned result;
    result = recursive_factorial(5);
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

//***********************************************
//
unsigned recursive_factorial(unsigned n)
{
    if (n == 0) return 1;
    return n * recursive_factorial(n - 1);
}
