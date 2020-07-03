#pragma once
using namespace System;


ref class Cell
{

public:
	int CellSize;
	Point Location;
	String^ Letter;
	String^ Number;
	bool Vertical;

	Cell(Point location, int size, String^ letter, String^ number, bool vertical)
	{
		Number = number;
		Letter = letter;
		Location = location;
		CellSize = size;
		Vertical = vertical;
	}

};