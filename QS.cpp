#include "QS.h"

QS::QS()
{
}

QS::~QS()
{
	clear();
}

bool QS::createArray(int capacity)
{
	if (capacity < 0)
	{
		return false;
	}
	if (a != NULL)
	{
		clear();
	}

	a = new int[capacity];
	addIndex = 0;
	arrayMaxSize = capacity;
	return true;
}

bool QS::addToArray(int value)
{
	if (addIndex < arrayMaxSize)
	{
		a[addIndex] = value;
		++addIndex;
		return true;
	}
	return false;
}

int QS::getSize() const
{
	//return the current size of the array
	if (a == NULL)
	{
		return 0;
	}
	else
	{
		return addIndex;
	}
}

string QS::getArray() const
{
	if (a == NULL)
	{
		return("");
	}
	else
	{
		if (addIndex == 0)
		{
			return("");
		}
		else
		{
			ostringstream ss;
			ss << a[0];
			for (int i = 1; i < addIndex; i++)
			{
				ss << "," << a[i];
			}
			return ss.str();
		}
	}
}

void QS::clear()
{
	delete[] a;
	a = NULL;
}

int QS::medianOfThree(int left, int right)
{
	int middleIndex = (left + right) / 2;
	
	if (a == NULL || addIndex < 0 || a == 0)
	{
		return -1;
	}

	if (left < 0 || right < 0 || right > addIndex - 1)
	{
		return -1;
	}

	if (left >= right)
	{
		return -1;
	}

	if (a[left] > a[middleIndex])
	{
		swap(a[left], a[middleIndex]);
	}
	if (a[middleIndex] > a[right])
	{
		swap(a[middleIndex], a[right]);
		if (a[left] > a[middleIndex])
		{
			swap(a[left], a[middleIndex]);
		}
	}
	
	return middleIndex;
}

int QS::partition(int left, int right, int pivotIndex)
{
	if (a == NULL || addIndex < 0 || a == 0)
	{
		return -1;
	}
	if (left >= right || left < 0 || right < 0 || right > addIndex - 1)
	{
		return -1;
	}
	if (pivotIndex < left || pivotIndex > right || pivotIndex < 0)
	{
		return -1;
	}

	int leftMark = left + 1;
	int rightMark = right;

	swap(a[left], a[pivotIndex]);
	
	//temporarily a[left] is the pivot
	do
	{
		while (a[leftMark] <= a[left] && leftMark < right)
		{
			++leftMark;
		}

		while (a[rightMark] > a[left] && left < rightMark)
		{
			if (rightMark == left)
			{
				break;
			}
			--rightMark;
		}

		if (leftMark < rightMark)
		{
			swap(a[leftMark], a[rightMark]);
		}

	} while (leftMark < rightMark);

	swap(a[left], a[rightMark]);
	
	return rightMark;
}

void QS::sortAll()
{
	if (a != NULL)
	{		
		sort(0, addIndex - 1);
	}
	else
	{
		return;
	}
}

void QS::sort(int left, int right)
{
	//left and right are Index
	
	if ((right - left) < 1)
	{
		return;
	}
	
	
	int partitionIndex = partition(left, right, medianOfThree(left, right));

	sort(left, partitionIndex - 1);
	sort(partitionIndex + 1, right);
	
}