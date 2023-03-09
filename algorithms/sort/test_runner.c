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
void setup(int* array);
bool verify_result(int *data, int size);

//***********************************************
int main(int argc, char **argv)
{
    srand((unsigned)time(NULL));
    g_size = 200;
    g_alg = 1;
    g_should_print = false;
    process_args(argc, argv);
    int data[g_size];
    setup(data);

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
    if (false)
    {
        printf("---------- array before sort -------------\n");
        for (size_t ii = 0; ii < g_size; ++ii)
        {
            printf("%d\t", data[ii]);
        }
        printf("\n");
    }
    switch(g_alg)
    {
        case 1:
            insertion_sort(data, g_size);
            break;
        case 2:
            merge_sort(data, g_size);
            break;
        case 3:
            quick_sort(data, g_size);
            break;
        default:
            printf("error: select valid sorting algorithm\n");
            printf("%s\n", g_helpstring);
            exit(EXIT_FAILURE);
            break;
    }

    if (false)
    {
        printf("---------- array after sort -------------\n");
        for (size_t ii = 0; ii < g_size; ++ii)
        {
            printf("%d\t", data[ii]);
        }
    }
    else
    {
        bool sort_valid = verify_result(data, g_size);

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
    }

    return EXIT_SUCCESS;
}

//***********************************************
// Verify if array is sorted in ascending order
// data: array to verify
// size: size of array
// return: true if array is sorted, false if not
bool verify_result(int *data, int size)
{
    int prev = 0;
    for (size_t ii = 0; ii < g_size; ++ii)
    {
        if (prev > data[ii])
        {
           return false;
        }
        prev = data[ii];
    }
    return true;
}
//***********************************************
// Set initial array state
void setup(int * array)
{
    for (size_t ii = 0; ii < g_size; ++ii)
    {
        array[ii] = rand() % g_size;
    }
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
