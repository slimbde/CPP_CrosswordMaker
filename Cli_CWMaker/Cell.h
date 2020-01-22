#pragma once
using namespace System;
using namespace System::Drawing;



ref class Cell
{

public:
	~Cell() { }
	Cell(int Left, int Top, int Size, String^ Letter, String^ Number, bool Vertical)
	{
		this->Number = Number;
		this->Letter = Letter;
		this->Top = Top;
		this->Left = Left;
		this->CellSize = Size;
		this->Vertical = Vertical;
	}

	int CellSize;
	int Left;
	int Top;
	String^ Letter;
	String^ Number;
	bool Vertical;
};