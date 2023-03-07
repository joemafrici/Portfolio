//***********************************************
// Implementations of sorting algorithms
// Insertion Sort, Merge Sort
// Author: Joe Mafrici
//
#include <stddef.h>
#include <stdio.h>
#include "sorts.h"

//***********************************************
// Sorts an array of positive integers in ascending order
// array: pointer to array of integers
// size: size of the array
// example input: array = {5, 2, 4, 6, 1, 3}
// example output: array = {1, 2, 3, 4, 5, 6}
void insertion_sort(int *array, size_t size)
{
    for (size_t jj = 1; jj < size; ++jj)
    {
        int key = array[jj];
        // insert key into sorted sequence
        int ii = jj - 1;
        while (ii >= 0 && array[ii] > key)
        {
            array[ii + 1] = array[ii];
            ii = ii - 1;
        }
        array[ii + 1] = key;
    }
}

//***********************************************
// Sorts an array of doubles in ascending order
// array: pointer to an array of doubles
// size: size of the array
// example input: array = {5.8, 2.1, 5.5, 3.2, 1.0, 3.1}
// example output: array = {1.0, 2.1, 3.1, 3.2, 5.5, 5.8}
void merge_sort(int* array, size_t size)
{
    // recursively split the array into subarrays until the
    // subarray size is 1
    split(array, 0, size);
}
//***********************************************
// Helper function for merge_sort
// Recursively splits array
void split(int* array, unsigned begin, unsigned end)
{
    if (end - begin == 1) return;
    unsigned middle = (end + begin) / 2;
    split(array, begin, middle);
    split(array, middle, end);
    merge(array, begin, end);
}
//***********************************************
// Helper function for merge_sort
// Merges virtual subarrays
void merge(int* array, unsigned begin, unsigned end)
{
    size_t middle = (end + begin) / 2;
    size_t i1 = begin;
    size_t i2 = middle;
    size_t temp_index = 0;
    int temp[end - begin];
    while (i1 <= middle && i2 <= end)
    {
        if (array[i1] < array[i2])
        {
            temp[temp_index++] = array[i1++];
        }
        else
        {
            temp[temp_index++] = array[i2++];
        }
    }

    for (int ii = begin; ii < end; ++ii)
    {
        array[ii] = temp[ii];
    }
}

