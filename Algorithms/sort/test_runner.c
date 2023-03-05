//***********************************************
// Author: Joe Mafrici
// Purpose: Test sorting algorithms
//
//***********************************************
// Includes
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h> // size_t
#include <getopt.h>
#include <stdio.h>
#include <stdbool.h>
#include "sorts.h"

//***********************************************
// Global Variables
static size_t g_size;
static unsigned g_alg;
static bool g_should_print;
static char *g_helpstring = "tester\n"
                                "-h print help string\n"
                                "-a <num> sorting algorithm\n"
                                    "\t1 - insertion sort\n"
                                    "\t2 - merge sort\n"
                                    "\t3 - quick sort\n"
                                "-s <size> size of array to sort\n"
                                "-v verbose mode: print array contents\n";
//***********************************************
// Function Declarations
void process_args(int argc, char **argv);
int validate_sort(int *data, int size);

//***********************************************
int main(int argc, char **argv)
{
    g_size = 200;
    g_alg = 1;
    g_should_print = false;
    process_args(argc, argv);
    srand((unsigned int)time(NULL));
    int data[g_size];

    printf("filling array with %zu positive integers\n", g_size);

    for (size_t ii = 0; ii < g_size; ++ii)
    {
        data[ii] = rand() % 1000;
    }

    if (g_should_print)
    {
        printf("writing array contents to beforesort.txt...\n");
        FILE *file = fopen("beforesort.txt", "w+");
        for (size_t ii = 0; ii < g_size; ++ii)
        {
            fprintf(file, "%d\n", data[ii]);
        }
        if (fclose(file) != 0) printf("error closing file\n");
    }

    printf("sorting...\n");
    switch(g_alg)
    {
        case 1:
            insertion_sort(data, g_size);
            break;
        case 2:
            merge_sort(data, g_size);
            break;
        default:
            printf("error: select valid sorting algorithm\n");
            printf("%s\n", g_helpstring);
            break;
    }

    printf("verifying sort...\n");
    printf("printing array after sort\n");
    for (int ii = 0; ii < g_size; ++ii)
    {
        printf("%d\n", data[ii]);
    }
    int sort_valid = validate_sort(data, g_size);

    if (sort_valid) printf("test successful... sort is valid!\n");
    else printf("test failed...\n");

    if (g_should_print)
    {
        printf("array contents written to aftersort.txt\n");
        FILE *file = fopen("aftersort.txt", "w+");
        for (size_t ii = 0; ii < g_size; ++ii)
        {
            fprintf(file, "%d\n", data[ii]);
        }
        if (fclose(file) != 0) printf("error closing file\n");
    }

    return EXIT_SUCCESS;

}

//***********************************************
// Verify if array is sorted in ascending order
// data: array to verify
// size: size of array
// return: 1 if array is sorted, 0 if not sorted
int validate_sort(int *data, int size)
{
    int prev = 0;
    for (size_t ii = 0; ii < g_size; ++ii)
    {
        if (prev > data[ii])
        {
           return 0;
        }
        prev = data[ii];
    }
    return 1;
}
//***********************************************
// Process command line arguments
void process_args(int argc, char **argv)
{
    int c;
    if (argc == 1)
    {
        printf("%s\n", g_helpstring);
        exit(EXIT_SUCCESS);
    }
    while ((c = getopt(argc, argv, "ha:s:v")) != -1)
    {
        switch(c)
        {
            case 'h':
                printf("%s\n", g_helpstring);
                exit(EXIT_SUCCESS);
                break;
            case 'a':
                g_alg = atoi(optarg);
                break;
            case 's':
                g_size = atoi(optarg);
                break;
            case 'v':
                g_should_print = true;
                break;
            case '?':
                printf("%s\n", g_helpstring);
                exit(EXIT_FAILURE);
                break;
        }
    }
}
