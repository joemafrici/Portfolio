//***********************************************
// Implementations of sorting algorithms
// Insertion Sort, Merge Sort, Quick Sort
// Author: Joe Mafrici
//
//***********************************************
// Includes
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include "sorts.h"

//***********************************************
// Function Definitions
//
//***********************************************
//              INSERTION SORT
//***********************************************
// Sorts an array of positive integers in ascending order
// array: pointer to array of integers
// size: size of the array
// example input: array = {5, 2, 4, 6, 1, 3}
// example output: array = {1, 2, 3, 4, 5, 6}
void insertion_sort(int *array, size_t size)
{
    __isort(array, 0, size);
}
//***********************************************
// Internal function to perform an insertion sort
// Used in insertion_sort and quick_sort
// array: pointer to array of integers
// begin: starting index of portion of array to sort
// end: ending index of portion of array to sort
void __isort(int *array, size_t begin, size_t end)
{
    for (size_t jj = begin + 1; jj < end; ++jj)
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
//              MERGE SORT
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
    __split(array, 0, size);
}
//***********************************************
// Helper function for merge_sort
// Recursively splits array
void __split(int* array, unsigned begin, unsigned end)
{
    if (end - begin < 2) return;
    unsigned middle = (end + begin) / 2;
    __split(array, begin, middle);
    __split(array, middle, end);
    __merge(array, begin, end);
}
//***********************************************
// Helper function for merge_sort
// Merges virtual subarrays
void __merge(int* array, unsigned begin, unsigned end)
{
    size_t middle = (end + begin) / 2;
    size_t i1 = begin;
    size_t i2 = middle;
    size_t temp_index = 0;
    int temp[end - begin];
    while (i1 < middle && i2 < end)
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
    while (i1 < middle)
    {
        temp[temp_index++] = array[i1++];
    }
    while (i2 < end)
    {
        temp[temp_index++] = array[i2++];
    }
    int jj = 0;
    for (int ii = begin; ii < end; ++ii)
    {
        array[ii] = temp[jj++];
    }
}
//***********************************************
//              QUICK SORT
//***********************************************
// quick sorts an array of integers
// array: pointer to an array of integers to sort
// size: size of array
void quick_sort(int* array, size_t size)
{
    // set pivot as median of three
    __qsort(array, 0, size - 1);
}
//***********************************************
// Internal recursive function for quick_sort
// array: pointer to an array of integers to sort
// left, right: left and right bounds of array
void __qsort(int* array, size_t left, size_t right)
{
    if (right - left < 2) return;
    size_t pivot = __partition(array, left, right);
    __qsort(array, left, pivot - 1);
    __qsort(array, pivot + 1, right);
}
//***********************************************
// Internal function to partition array
// Uses Median of Three to determine pivot
// Used in quick_sort
// array: pointer to an array of integers to partition
// left, right: left and right bounds of array
size_t __partition(int *array, size_t left, size_t right)
{
    size_t mid_index = (left + right) / 2;
    size_t left_index = left;
    size_t right_index = right;

    if (array[left_index] > array[mid_index])
        __swap(array, left_index, mid_index);
    if (array[mid_index] > array[right_index])
        __swap(array, mid_index, right_index);
    if (array[left] > array[mid_index])
        __swap(array, left, mid_index);

    size_t pivot = array[mid_inded];

    while (true)
    {
        // find first value to swap
        while (left_index < right && array[left_index] < pivot)
        {
            ++left_index;
        }
        // find second value to swap
        while (right_index > left && array[right_index] > pivot)
        {
            --right_index;
        }
        // partition is done when indices cross
        if (left_index >= right_index) break;
        else __swap(array, left_index, right_index);
    }
    __swap(array, left_index, right);
    return left_index;
}
//***********************************************
// Internal function to swap two integers in an array
// Used by quick_sort
// array: integer array
// index1: index of first element to swap
// index2: index of second element to swap
void __swap(int* array, size_t index1, size_t index2)
{
    int temp = array[index1];
    array[index1] = array[index2];
    array[index2] = temp;
}
