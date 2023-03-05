//***********************************************
// Test runner for search algorithms
// Author: Joe Mafrici
//
//***********************************************
// Includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h> // size_t
#include <getopt.h>
#include "search.h"
#include "../sort/sorts.h"

//***********************************************
// Global Variables
static size_t g_size;
static int g_key;
static char *g_helpstring = "tester\n"
                                "-h print a help string then exit\n"
                                "-s <size> size of array to search\n";

//***********************************************
// Function Declarations
void process_args(int argc, char** argv);
void setup();
bool verify_result();
//***********************************************
int main(int argc, char** argv)
{
    srand((unsigned)time(NULL));
    g_size = 100;

    process_args(argc, argv);
    g_key = rand() % g_size;

    int data[g_size];
    setup(data);

    bool search_found = binary_search(data, g_size, g_key);
    bool verify_found = verify_result(data);
    if (search_found) printf("%d was found in the array\n", g_key);
    else printf("%d was not found in the array\n", g_key);
    if (search_found == verify_found) printf("result is valid\n");

    return EXIT_SUCCESS;
}
//***********************************************
// Does a linear search to verify sorting algorithm
// correctly found or correctly did not find the key
// array: array to verify
bool verify_result(int *array)
{
    for (size_t ii = 0; ii < g_size; ++ii)
    {
        if (array[ii] == g_key) return true;
    }
    return false;
}
//***********************************************
// Set up array state
void setup(int* array)
{
    for (size_t ii = 0; ii < g_size; ++ii)
    {
        array[ii] = rand() % 1000;
    }

    insertion_sort(array, g_size);
}
//***********************************************
// Process command line arguments
void process_args(int argc, char** argv)
{
    int c;
    if (argc == 1)
    {
        printf("%s\n", g_helpstring);
        exit(EXIT_SUCCESS);
    }
    while ((c = getopt(argc, argv, "hs:")) != -1)
        switch(c)
        {
            case 'h':
                printf("%s\n", g_helpstring);
                exit(EXIT_SUCCESS);
                break;
            case 's':
                g_size = atoi(optarg);
                break;
            case '?':
                printf("%s\n", g_helpstring);
                exit(EXIT_FAILURE);
        }
}
