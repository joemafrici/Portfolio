// Author: Joe Mafrici
// Purpose: Test sorting algorithms
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h> // size_t
#include <getopt.h>
#include <stdio.h>
#include <stdbool.h>
#include "sorts.h"

static int g_size;
static bool g_should_print;
static char *helpstring = "tester\n"
                                "-h print help string\n"
                                "-s <size> size of array to sort\n"
                                "-v verbose mode: print array contents\n";
void process_args(int argc, char **argv);
int validate_sort(int *data, int size);
//***********************************************
int main(int argc, char **argv)
{
    g_size = 200;
    g_should_print = false;
    process_args(argc, argv);
    srand((unsigned int)time(NULL));
    int data[g_size];

    printf("filling array with %d positive integers\n", g_size);

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

    insertion_sort(data, g_size);

    printf("verifying sort...\n");

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
        printf("%s\n", helpstring);
    }
    while ((c = getopt(argc, argv, "hs:v")) != -1)
    {
        switch(c)
        {
            case 'h':
                printf("%s\n", helpstring);
                exit(0);
                break;
            case 's':
                g_size = atoi(optarg);
                break;
            case 'v':
                g_should_print = true;
                break;
            case '?':
                printf("%s\n", helpstring);
                exit(0);
                break;
        }
    }
}
