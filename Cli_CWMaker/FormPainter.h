#pragma once
#include "IPainter.h"
using namespace System;
using namespace Printing;


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

	virtual void drawWords();	// рисует слова на доске
	virtual void drawBoard();	// рисует доску на холсте
	virtual void preview();		// предпросмотр печати

private:
	Board^ board;				// доска для отрисовки
	Cell^ cell;
	Graphics^ easel;			// место для отрисовки
	float scale = 20.0f;        // масштаб клетки по умолчанию
	bool cutWords;				// убрать буквы из клеток
	bool resetZeroPoint;		// рисовать не с центра а от угла

	void onPrintPage(Object^ sender, PrintPageEventArgs^ e);
	void drawCell();
};



FormPainter::FormPainter(Board^ board, Graphics^% easel)
{
	this->board = board;
	this->easel = easel;
}

void FormPainter::drawBoard()
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

		// порядковые номера слов
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

				// отрисовка ячейки
				drawCell();
			}
		}
	}
	else
		easel->DrawString(L"Составленный кроссворд не вмещается в рабочую область.\r\nВоспользуйтесь предпросмотром.",
						  gcnew Drawing::Font("Calibri", scale / 1.5f, FontStyle::Regular), Brushes::Black, 10, 10);
}
void FormPainter::drawWords()
{
	auto hWords = board->hWords;
	auto vWords = board->vWords;

	float top = scale;
	float left = board->Width * scale + scale * 2;

	easel->DrawString("ПО ГОРИЗОНТАЛИ:", gcnew Drawing::Font("Calibri", scale / 2, FontStyle::Bold), Brushes::Black, left, top);
	top += scale * 0.75f;

	for (auto i = 0; i < hWords->Count; ++i)
	{
		easel->DrawString(i + 1 + ". " + hWords[i], gcnew Drawing::Font("Calibri", scale / 2), Brushes::Black, left, top);
		top += scale * 0.6f;
	}

	top += scale * 0.75f;
	easel->DrawString("ПО ВЕРТИКАЛИ:", gcnew Drawing::Font("Calibri", scale / 2, FontStyle::Bold), Brushes::Black, left, top);
	top += scale * 0.75f;

	for (auto i = 0; i < vWords->Count; ++i)
	{
		easel->DrawString(i + 1 + ". " + vWords[i], gcnew Drawing::Font("Calibri", scale / 2), Brushes::Black, left, top);
		top += scale * 0.6f;
	}

	easel->DrawString("©slim 2020", gcnew Drawing::Font("Calibri", scale / 2), Brushes::LightGray, -scale, -scale);
}
void FormPainter::preview()
{
	auto wMargin = scale;
	auto hMargin = scale;

	auto hWords = board->hWords;
	auto vWords = board->vWords;

	// ищем длиннейшее горизонтальное слово
	int maxLength = 0;
	for each (auto item in hWords)
		maxLength = maxLength > item->Length ? maxLength : item->Length;

	auto paperWidth = int(board->Width * scale + wMargin * 2 + 1 / hWords->Count * scale * 7 + maxLength * scale);
	auto paperHeight = int(board->Height * scale + hMargin * 2 + 1 / vWords->Count * scale * 4);

	auto print = gcnew PrintDocument();

	print->DefaultPageSettings->PaperSize = gcnew Printing::PaperSize("MySize", paperWidth, paperHeight);
	print->OriginAtMargins = true;
	print->DefaultPageSettings->Margins = gcnew Printing::Margins((int)wMargin, (int)wMargin, (int)hMargin, (int)hMargin);
	print->PrintPage += gcnew PrintPageEventHandler(this, &FormPainter::onPrintPage);

	auto printDialog = gcnew PrintPreviewDialog();

	printDialog->AutoScrollMargin = System::Drawing::Size(0, 0);
	printDialog->AutoScrollMinSize = System::Drawing::Size(0, 0);
	printDialog->ClientSize = System::Drawing::Size(400, 300);
	printDialog->Document = print;
	printDialog->Enabled = true;
	printDialog->Visible = false;
	printDialog->StartPosition = FormStartPosition::CenterParent;
	printDialog->WindowState = System::Windows::Forms::FormWindowState::Maximized;
	printDialog->ShowDialog();
}


void FormPainter::onPrintPage(Object^ sender, PrintPageEventArgs^ e)
{
	easel = e->Graphics;
	resetZeroPoint = true;
	drawBoard();
	drawWords();
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