#pragma once
using namespace System::Collections;

// предикат для сравнения строк по длине
ref class CompareByLength : public Generic::IComparer<String^>
{
public:
    // Унаследовано через IComparer
    virtual int Compare(System::String^ x, System::String^ y)
    {
        if(x->Length > y->Length)
            return 1;

        if(x->Length < y->Length)
            return -1;

        return 0;
    }
};