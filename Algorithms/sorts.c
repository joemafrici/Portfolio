// Author: Joe Mafrici
// Purpose: Implementation of the Insertion Sort algorithm
//
#include <stddef.h>

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
void merge_sort(double *array, size_t size)
{
    // recursively split the array into subarrays until the
    // subarray size is 1
}
