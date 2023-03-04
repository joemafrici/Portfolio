//***********************************************
// Search algorithm implementations
// Author: Joe Mafrici
//
#include <stdbool.h>
#include <stdio.h>
#include "search.h"
//***********************************************
// Performs a binary search on an array of integers
bool binary_search(int* array, size_t size, int key)
{
    int middle = size / 2;
    if (size == 1)
    {
        if (array[0] == key) return true;
        else return false;
    }
    else if (size == 0) return false;
    else
    {
        if (array[middle] > key)
        {
            bsearch(array, 0, middle, key);
        }
        else
        {
            bsearch(array, middle, size - 1, key);
        }
    }
}
//***********************************************
// Internal recursive helper function for binary_search
bool bsearch(int* array, unsigned left, unsigned right, int key)
{
    if (right - left == 1)
    {
        if (array[left] == key) return true;
        else if (array[right] == key) return true;
        else return false;
    }
    else
    {
        unsigned middle = (right - left) / 2;
        if (array[middle] > key)
        {
            return bsearch(array, left, middle, key);
        }
        else
        {
            return bsearch(array, middle, right, key);
        }
    }
}
