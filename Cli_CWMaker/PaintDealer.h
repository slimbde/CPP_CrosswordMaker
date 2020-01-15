#pragma once
#include "BoardDealer.h"
using namespace Printing;


ref class PaintDealer
{

public:
	property float Scale { float get() { return scale; } }

	PaintDealer(BoardDealer^ bDealer);

	void drawWords(Graphics^% easel);                                       // рисует слова на доске
	void drawBoard(Graphics^% easel, bool resetZeroPoint, bool cutWords);   // рисует доску на холсте
	void preview(bool checked);

private:
	BoardDealer^ bDealer;		// текущая мат модель
	float scale = 20.0f;        // масштаб клетки по умолчанию
	bool cutWords;

	void onPrintPage(Object^ sender, PrintPageEventArgs^ e);
};



PaintDealer::PaintDealer(BoardDealer^ bDealer)
{
	this->bDealer = bDealer;
}

void PaintDealer::drawBoard(Graphics^% easel, bool resetZeroPoint, bool cutWords)
{
	auto currentBoard = bDealer->gimmeBoard();
	currentBoard->Draw(easel, resetZeroPoint, cutWords, scale); // TODO:
}
void PaintDealer::drawWords(Graphics^% easel)
{
	auto hWords = bDealer->gimmeHWords();
	auto vWords = bDealer->gimmeVWords();

	float top = scale;
	float left = bDealer->CurrentWidth * scale + scale * 2;

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

	easel->DrawString("©slimHouse 2019", gcnew Drawing::Font("Calibri", scale / 2), Brushes::LightGray, -scale, -scale);
}
void PaintDealer::preview(bool checked)
{
	cutWords = checked;

	auto wMargin = scale;
	auto hMargin = scale;

	auto hWords = bDealer->gimmeHWords();
	auto vWords = bDealer->gimmeVWords();

	// ищем длиннейшее горизонтальное слово
	int maxLength = 0;
	for each (auto item in hWords)
		maxLength = maxLength > item->Length ? maxLength : item->Length;

	auto paperWidth = int(bDealer->CurrentWidth * scale + wMargin * 2 + 1 / hWords->Count * scale * 7 + maxLength * scale);
	auto paperHeight = int(bDealer->CurrentHeight * scale + hMargin * 2 + 1 / vWords->Count * scale * 4);

	auto print = gcnew PrintDocument();

	print->DefaultPageSettings->PaperSize = gcnew Printing::PaperSize("MySize", paperWidth, paperHeight);
	print->OriginAtMargins = true;
	print->DefaultPageSettings->Margins = gcnew Printing::Margins((int)wMargin, (int)wMargin, (int)hMargin, (int)hMargin);
	print->PrintPage += gcnew PrintPageEventHandler(this, &PaintDealer::onPrintPage);

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


void PaintDealer::onPrintPage(Object^ sender, PrintPageEventArgs^ e)
{
	auto easel = e->Graphics;

	drawBoard(easel, true, cutWords);
	drawWords(easel);
}