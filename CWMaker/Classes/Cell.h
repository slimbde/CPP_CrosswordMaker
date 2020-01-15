#pragma once
using namespace System;
using namespace System::Drawing;



ref class Cell
{
    Drawing::Rectangle rect;
    Drawing::Pen^ pen;
    String^ number;
    String^ letter;
    float top;
    float left;
    float size;
    bool vertical;

public:
    ~Cell() { }
    Cell(float left, float top, float size, String^ letter, String^ number, bool vertical);

    void draw(Drawing::Graphics^ place);
};



inline Cell::Cell(float left, float top, float size, String^ letter, String^ number, bool vertical)
{
    this->number = number;
    this->letter = letter;
    this->top = (float)top;
    this->left = (float)left;
    this->size = (float)size;
    this->vertical = vertical;
    pen = gcnew Pen(Color::Black);
    rect = Rectangle((int)left, (int)top, (int)size, (int)size);
}

inline void Cell::draw(Drawing::Graphics^ place)
{
    place->DrawRectangle(pen, rect);
    place->DrawString(letter, gcnew Font("Calibri", 10.0f), Brushes::Black, left + size / 5, top + size / 8);
    place->DrawString(number, gcnew Font("Calibri", 6.0f), Brushes::Maroon, vertical ? left + size - 10 : left - 1, top - 1);
}