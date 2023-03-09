void insertion_sort(int* array, size_t size);
void __isort(int *array, size_t begin, size_t end);

void merge_sort(int* array, size_t size);
void __split(int* array, unsigned begin, unsigned end);
void __merge(int* array, unsigned begin, unsigned end);

void quick_sort(int* array, size_t size);
void __swap(int* array, size_t index1, size_t index2);
size_t __partition(int *array, size_t left, size_t right, int pivot);
