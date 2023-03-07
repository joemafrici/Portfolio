//***********************************************
// Declarations for search.c
// Author: Joe Mafrici
//

#include <stdbool.h>
bool binary_search(int* array, size_t size, int key);
bool __recurse(int* array, unsigned left, unsigned right, int key);
