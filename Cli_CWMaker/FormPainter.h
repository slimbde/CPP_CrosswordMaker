#pragma once
#include "IPainter.h"
using namespace System;



ref class FormPainter : IPainter
{

public:
	property float Scale {
		virtual float get() { return scale; }
	}
	property bool CutWords {
		virtual bool get() { return cutWords; }
		virtual void set(bool value) { cutWords = value; }
	}
	property bool ResetZeroPoint {
		virtual bool get() { return resetZeroPoint; }
		virtual void set(bool value) { resetZeroPoint = value; }
	}

	FormPainter(Board^ board, Graphics^% easel);

	virtual void drawWords() { }	// ������ ����� �� �����
	virtual void drawBoard() { }	// ������ ����� �� ������
	virtual void preview();			// ������������ ������

private:
	Board^ board;				// ����� ��� ���������
	Cell^ cell;
	Graphics^ easel;			// ����� ��� ���������
	float scale = 20.0f;        // ������� ������ �� ���������
	bool cutWords;				// ������ ����� �� ������
	bool resetZeroPoint;		// �������� �� � ������ � �� ����

	void drawCell();
};



FormPainter::FormPainter(Board^ board, Graphics^% easel)
{
	this->board = board;
	this->easel = easel;
}
void FormPainter::preview()
{
	easel->Clear(SystemColors::Info);

	if (board->Height * Scale < easel->VisibleClipBounds.Height && board->Width * Scale < easel->VisibleClipBounds.Width)
	{
		auto easelHeight = easel->VisibleClipBounds.Height;
		auto easelWidth = easel->VisibleClipBounds.Width;

		auto zeroTop = (easelHeight - board->Height * scale) / 2.5f;
		auto zeroLeft = (easelWidth - board->Width * scale) / 2;

		if (resetZeroPoint)
		{
			zeroTop = 0.0f;
			zeroLeft = 0.0f;
		}

		// ���������� ������ ����
		int nVertical = 1;
		int nHorizontal = 1;

		for each (auto item in board->Words)
		{
			for (int i = 0; i < item->length; ++i)
			{
				float currentVerticalLeft = zeroLeft + item->left * scale;
				float currentVertiaclTop = zeroTop + item->top * scale + i * scale;
				float currentHorizontalLeft = zeroLeft + item->left * scale + i * scale;
				float currentHorizontalTop = zeroTop + item->top * scale;

				if (item->lyt == "Horizontal")
					cell = gcnew Cell((int)currentHorizontalLeft,
					(int)currentHorizontalTop,
									  (int)scale,
									  cutWords ? " " : item[i]->ToUpper(),
									  i == 0 ? (nHorizontal++).ToString() : "",
									  false);
				else
					cell = gcnew Cell((int)currentVerticalLeft,
					(int)currentVertiaclTop,
									  (int)scale,
									  cutWords ?
									  " " : item[i]->ToUpper(),
									  i == 0 ? (nVertical++).ToString() : "",
									  true);

				// ��������� ������
				drawCell();
			}
		}
	}
	else
		easel->DrawString(L"������������ ��������� �� ��������� � ������� �������.\r\n�������������� ��������������.",
						  gcnew Drawing::Font("Calibri", scale / 1.5f, FontStyle::Regular), Brushes::Black, 10, 10);
}

void FormPainter::drawCell()
{
	auto rect = Rectangle(cell->Left, cell->Top, cell->CellSize, cell->CellSize);
	easel->DrawRectangle(Pens::Black, rect);
	easel->DrawString(cell->Letter, gcnew Font("Calibri", 10.0f), Brushes::Black, float(cell->Left + cell->CellSize / 5), float(cell->Top + cell->CellSize / 8));

	if (cell->Vertical)
		easel->DrawString(cell->Number, gcnew Font("Calibri", 6.0f), Brushes::Maroon, float(cell->Left + cell->CellSize) - 7, float(cell->Top) - 1);
	else
		easel->DrawString(cell->Number, gcnew Font("Calibri", 6.0f), Brushes::Maroon, float(cell->Left) - 1, float(cell->Top) - 1);
}