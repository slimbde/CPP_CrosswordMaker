#pragma once
using namespace System;
using namespace System::Collections::Generic;

enum Layout
{
	Vertical,
	Horizontal
};



ref class Word
{
public:
	String^ word;
	Layout layout;
	int top;
	int left;
	int length;

	// ����������� ����� (intersects - ������� �����������)
	Word(String^ word, Layout layout, int top, int left)
	{
		this->word = word;
		this->layout = layout;
		this->top = top;
		this->left = left;
		length = word->Length;
	}
	String^ operator[](int index)
	{
		if(index < 0 || index >= length)
			throw gcnew IndexOutOfRangeException();

		return word[index].ToString();
	}
	Word(Word^ other)
	{
		this->word = other->word;
		this->layout = other->layout;
		this->top = other->top;
		this->left = other->left;
		this->length = this->word->Length;
	}
};