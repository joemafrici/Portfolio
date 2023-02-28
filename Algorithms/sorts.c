// Author: Joe Mafrici
// Purpose: Implementation of the Insertion Sort algorithm

//***********************************************
// Sorts an array of positive integers in ascending order
// array: pointer to array of integers
// size: size of the array
// example input: array = {5, 2, 4, 6, 1, 3}
// example output: array = {1, 2, 3, 4, 5, 6}
void insertion_sort(int *array, int size)
{
    for (int jj = 1; jj < size; ++jj)
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
