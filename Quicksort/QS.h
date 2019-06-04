#pragma once
#include "QSInterface.h"
#include <sstream>

class QS : public QSInterface
{
public:
	QS();
	~QS();

	bool createArray(int capacity);
	bool addToArray(int value);
	int getSize() const;
	string getArray() const;
	void clear();
	int medianOfThree(int left, int right);
	int partition(int left, int right, int pivotIndex);
	void sortAll();
	void sort(int left, int right);
protected:
	int* a = NULL;
	int addIndex;
	int arrayMaxSize;
};

