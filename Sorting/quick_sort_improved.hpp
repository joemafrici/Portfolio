#ifndef QUICK_SORT_IMPROVED_HPP
#define SELECTION_SORT_HPP

#include <Windows.h>
#include "ISort.hpp"

template<class C>
class QuickSortImproved final : public ISort<C>
{
public:
	~QuickSortImproved() = default;
	size_t Sort(C container, const size_t& size) override;
	virtual const char* SortName() const;
private:
	void RecursiveQuickSort(C& container, const int& left, const int& right);
	int MedianOf3(C& container, const int& left, const int& right);
	int Partition(C& container, const int& left, const int& right, const int& pivot);
	void Insertion(C& container, const int& left, const int& right);
	void Swap(C& container, const int& index1, const int& index2);
};

template<class C>
size_t QuickSortImproved<C>::Sort(C container, const size_t& size)
{
	const auto start_time = GetTickCount();

	RecursiveQuickSort(container, 0, size - 1);
	Insertion(container, 0, size - 1);

	return GetTickCount() - start_time;
}

template<class C>
const char* QuickSortImproved<C>::SortName() const
{
	return "Quick Sort Improved";
}

template<class C>
void QuickSortImproved<C>::RecursiveQuickSort(C& container, const int& left, const int& right)
{
	int size{ right - left + 1 };

	if (size < 10)
		Insertion(container, left, right);
	else
	{
		int median = MedianOf3(container, left, right);
		int partition = Partition(container, left, right, median); // returns pivot point
		RecursiveQuickSort(container, left, partition - 1); // search to the left of the pivot
		RecursiveQuickSort(container, partition + 1, right); // search to the right of the pivot point
	}
	
}

template<class C>
int QuickSortImproved<C>::MedianOf3(C& container, const int& left, const int& right)
{
	int center{ (left + right) / 2 };

	if (container[left] > container[center])
		Swap(container, left, center);
	if (container[left] > container[right])
		Swap(container, left, right);
	if (container[center] > container[right])
		Swap(container, center, right);

	Swap(container, center, right - 1); // put pivot on right
	return container[right - 1]; // return median value
}

template<class C>
int QuickSortImproved<C>::Partition(C& container, const int& left, const int& right, const int& pivot)
{
	int leftIndex{ left };
	int rightIndex{ right - 1 }; // the position to the left of pivot. pivot is right
	bool done{ false };

	while (!done)
	{
		// start at the leftmost position and iterate right until we find
		// an item that is greater than pivot and thus needs to be swapped.
		// all items less than pivot should be on the left so if one is larger
		// we need to swap it to the right. the loop breaks when we find an
		// item larger than pivot and when that happens leftIndex represents
		// the index of the item that needs to be swapped to the right
		while (container[++leftIndex] < pivot)
		{
			// do nothing
		}

		// start at the rightmost position and iterate left until we find
		// an item that is less than pivot and thus needs to be swapped.
		// all items greater than pivot should be on the right so if one is less
		// we need to swap it to the left. the loop breaks when we find an
		// item less than pivot and when that happens rightIndex represents
		// the index of the item that needs to be swapped to the left
		while (container[--rightIndex] > pivot)
		{
			// do nothing
		}

		// if leftIndex crosses over rightIndex we are done partitioning
		if (leftIndex >= rightIndex)
			done = true;
		else
			Swap(container, leftIndex, rightIndex);
	}

	// the pivot is swapped into the place following all the elements less than it
	Swap(container, leftIndex, right - 1);

	// return the position of pivot
	return leftIndex;
}

template<class C>
void QuickSortImproved<C>::Insertion(C& container, const int& left, const int& right)
{
	int in{}, out{};

	for (out = left + 1; out <= right; ++out)
	{
		int temp{ container[out] }; // remove marked item
		in = out; // start shifts at out
		// until one is smaller
		while (in > left && container[in - 1] >= temp)
		{
			container[in] = container[in - 1]; // shift item to right
			--in; // go left one position
		}
		container[in] = temp; // insert marked item
	}
}

template<class C>
void QuickSortImproved<C>::Swap(C& container, const int& index1, const int& index2)
{
	int temp{ container[index1] };
	container[index1] = container[index2];
	container[index2] = temp;
}
#endif