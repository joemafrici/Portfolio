// Author: Joe Mafrici
// Purpose: Test sorting algorithms
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "sorts.h"

static int g_size;
static char *helpstring = "test_runner\n"
                                "-h print help string\n"
                                "-s <size> size of array to sort";
void process_args(int argc, char **argv);
//***********************************************
int main(int argc, char **argv)
{
    g_size = 200;
    process_args(argc, argv);
    srand((unsigned int)time(NULL));
    int data[g_size];
    for (int ii = 0; ii < g_size; ++ii)
    {
        data[ii] = rand() % 1000;
    }
    insertion_sort(data, g_size);
}
//***********************************************
// Process command line arguments
void process_args(int argc, char **argv)
{
    int c;
    while ((c = getopt(argc, argv, "hs:")) != -1)
    {
        switch(c)
        {
            case 'h':
                printf("%s\n", helpstring);
                break;
            case 's':
                g_size = atoi(optarg);
                break;
            default:
                printf("%s\n", helpstring);
                break;
        }
    }
}
