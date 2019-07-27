#pragma once
using namespace System::Collections::Generic;

// предикат для сравнения значений больше-меньше
ref class CompareByIntValue : public IComparer<int>
{
public:
	// Унаследовано через IComparer
	virtual int Compare(int x, int y)
	{
		if(x > y)
			return -1;
		if(x < y)
			return 1;
		return 0;
	}
};