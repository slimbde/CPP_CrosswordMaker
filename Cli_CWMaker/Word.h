#pragma once
using namespace System;
using namespace System::Drawing;


enum Directions
{
	Vertical,
	Horizontal
};



ref class Word
{

public:
	String^ Text;
	Directions Direction;
	Point Location;

	Word(String^ text, Directions direction, Point point)
	{
		Text = text;
		Direction = direction;
		Location = point;
	}
	Word(Word^ other)
	{
		this->Text = gcnew String(other->Text);
		this->Direction = other->Direction;
		this->Location = Point(other->Location.X, other->Location.Y);
	}

};