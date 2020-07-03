#pragma once
#include "Word.h"
#include "Cell.h"


using namespace System;
using namespace System::Drawing;
using namespace System::Drawing::Printing;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;



ref class Board
{
	Point size;						// размеры
	List<Word^ >^ words;			// список слов
	array<String^, 2>^ board;		// доска со словами

	float scale = 20.0f;			// масштаб клетки по умолчанию
	bool cutWords;					// убрать буквы из клеток
	bool resetZeroPoint;			// рисовать не с центра а от угла


public:
	property Point Size { Point get() { return size; } };
	property List<Word^>^ vWords {
		List<Word^>^ get()
		{
			auto result = gcnew List<Word^>();

			for each (auto % item in words)
			{
				if (item->Direction == Directions::Vertical)
					result->Add(item);
			}

			return result;
		}
	}
	property List<Word^>^ hWords {
		List<Word^>^ get()
		{
			auto result = gcnew List<Word^>();

			for each (auto % item in words)
			{
				if (item->Direction == Directions::Horizontal)
					result->Add(item);
			}

			return result;
		}
	}
	property List<Word^>^ Words {
		List<Word^>^ get() { return words; }
	}
	property bool CutWords { bool get() { return cutWords; } void set(bool value) { cutWords = value; } }
	property bool ResetZeroPoint { bool get() { return resetZeroPoint; } void set(bool value) { resetZeroPoint = value; } }

	Board(Point size);

	Generic::Stack<Board^ >^ Append(String^ word);
	array<String^, 2>^ GetRawBoard() { return board; }
	void GetDrawn(Graphics^% easel);
	void Preview();


private:
	bool IsEmpty();
	String^ GetChar(Point pt);
	void CollectWord(Word^ wrd);
	Board^ IncreaseLeft(Board^ brd, int offset);
	Board^ IncreaseRight(Board^ brd, int offset);
	Board^ IncreaseTop(Board^ brd, int offset);
	Board^ IncreaseBottom(Board^ brd, int offset);
	bool CheckVerticalNeighbors(Point crossPoint, Point beforePoint, Point nextToPoint);
	bool CheckHorizontalNeighbors(Point crossPoint, Point beforePoint, Point nextToPoint);
	Generic::Stack<Board^ >^ InsertHorizontally(String^ word);
	Generic::Stack<Board^ >^ InsertVertically(String^ word);
	void drawCell(Cell^ cell, Graphics^% easel);
	void onPrintPage(Object^ sender, PrintPageEventArgs^ e);
};




inline Board::Board(Point size)
{
	this->size = size;
	board = gcnew array<String^, 2>(size.X, size.Y);
}

inline Generic::Stack<Board^ >^ Board::Append(String^ wrd)
{
	// если доска пуста, добавим первое слово
	if (IsEmpty())
	{
		// пишем номер слово в нулевой столбец
		for (int i = 0; i < size.Y; ++i)
			board[0, i] = wrd[i].ToString();

		// добавляем слово в список слов
		CollectWord(gcnew Word(wrd, Directions::Vertical, Point(0, 0)));

		// создаем временный стек для результата
		auto result = gcnew Generic::Stack<Board^ >();
		result->Push(this);

		return result;
	}
	else // если доска не пуста
	{
		// пробуем вписать слово горизонтально и вертикально
		auto result = InsertHorizontally(wrd);
		auto extraResult = InsertVertically(wrd);

		// дополняем стек результатов вставки вертикально
		while (extraResult->Count)
			result->Push(extraResult->Pop());

		return result;
	}
}


inline bool Board::IsEmpty()
{
	for each (String ^ item in board)
		if (!String::IsNullOrEmpty(item))
			return false;
	return true;
}
inline String^ Board::GetChar(Point pt)
{
	try
	{
		return board[pt.X, pt.Y];
	}
	catch (Exception^)
	{
		return nullptr;
	}
}
inline void Board::CollectWord(Word^ wrd)
{
	if (words == nullptr)
		words = gcnew List<Word^>();

	words->Add(wrd);
}
inline Board^ Board::IncreaseLeft(Board^ brd, int offset)
{
	// новая ширина шире на offset
	int newWidth = brd->Size.X + offset;
	Board^ temp = gcnew Board(Point(newWidth, brd->Size.Y));

	// перепишем все буквы на доске на новые (со смещением) позиции
	for (int i = 0; i < brd->Size.X; ++i)
		for (int j = 0; j < brd->Size.Y; ++j)
			temp->board[i + offset, j] = gcnew String(brd->board[i, j]);

	// скопируем массив слов изменяя их координаты left
	temp->words = gcnew List<Word^>();
	for each (Word ^ word in brd->words)
		temp->words->Add(gcnew Word(word));


	for each (Word ^ item in temp->words)
		item->Location.X += offset;

	return temp;
}
inline Board^ Board::IncreaseRight(Board^ brd, int offset)
{
	// новая ширина шире на offset
	int newWidth = brd->Size.X + offset;
	Board^ temp = gcnew Board(Point(newWidth, brd->Size.Y));

	// перепишем все буквы на доске на прежние (без смещения) позиции
	for (int i = 0; i < brd->Size.X; ++i)
		for (int j = 0; j < brd->Size.Y; ++j)
			temp->board[i, j] = gcnew String(brd->board[i, j]);

	// скопируем массив слов без изменения их координаты left
	temp->words = gcnew List<Word^>();
	for each (Word ^ word in brd->words)
		temp->words->Add(gcnew Word(word));

	return temp;
}
inline Board^ Board::IncreaseTop(Board^ brd, int offset)
{
	// новая высота больше на offset
	int newHeight = brd->Size.Y + offset;
	Board^ temp = gcnew Board(Point(brd->Size.X, newHeight));

	// перепишем все буквы на доске на новые (со смещением) позиции
	for (int i = 0; i < brd->Size.X; ++i)
		for (int j = 0; j < brd->Size.Y; ++j)
			temp->board[i, j + offset] = gcnew String(brd->board[i, j]);

	// скопируем массив слов изменяя их координаты top
	temp->words = gcnew List<Word^ >();
	for each (Word ^ word in brd->words)
		temp->words->Add(gcnew Word(word));

	for each (Word ^ item in temp->words)
		item->Location.Y += offset;

	return temp;
}
inline Board^ Board::IncreaseBottom(Board^ brd, int offset)
{
	// новая высота больше на offset
	int newHeight = brd->Size.Y + offset;
	Board^ temp = gcnew Board(Point(brd->Size.X, newHeight));

	// перепишем все буквы на доске на прежние (без смещения) позиции
	for (int i = 0; i < brd->Size.X; ++i)
		for (int j = 0; j < brd->Size.Y; ++j)
			temp->board[i, j] = gcnew String(brd->board[i, j]);

	// скопируем массив слов без изменения их координаты top
	temp->words = gcnew List<Word^ >();
	for each (Word ^ word in brd->words)
		temp->words->Add(gcnew Word(word));

	return temp;
}
inline bool Board::CheckVerticalNeighbors(Point crossPoint, Point beforePoint, Point nextToPoint)
{
		// * * * * * * * * * * * * *
		// *|#|#|#|#|#|#|#|#|#|#|#|*
		// * * * * * * * * * * * * *

	// проверяем по три точки от координат начала слова до координат конца
	for (int x = beforePoint.X; x <= nextToPoint.X; ++x)
	{
		// проверим по 3 вертикальных точки по всей длине слова кроме пересечения
		for (int y = beforePoint.Y - 1; y <= beforePoint.Y + 1; ++y)
		{
			if (x == crossPoint.X)
				break;

			if (GetChar(Point(x, y)) != nullptr)
				return false;
		}
	}

	return true;
}
inline bool Board::CheckHorizontalNeighbors(Point crossPoint, Point beforePoint, Point nextToPoint)
{
	// проверяем по три точки от координат начала слова до координат конца
	for (int y = beforePoint.Y; y <= nextToPoint.Y; ++y)
	{
		// проверим по 3 горизонтальных точки по всей длине слова кроме пересечения
		for (int x = beforePoint.X - 1; x <= beforePoint.X + 1; ++x)
		{
			if (y == crossPoint.Y)
				break;

			if (GetChar(Point(x, y)) != nullptr)
				return false;
		}
	}

	return true;
}
inline Generic::Stack<Board^ >^ Board::InsertHorizontally(String^ wrd)
{
	// создаем временный стек для результата
	Generic::Stack<Board^ >^ result = gcnew Generic::Stack<Board^ >();

	// идем по всем вертикальным словам
	for each (Word ^ currentWord in words)
	{
		if (currentWord->Direction == Directions::Vertical)
		{
			// резервируем сдвиг слова влево относительно места скрещивания
			int offset;

			// пытаемся проверить впишется ли слово к текущему
			// цикл по высоте, i - итератор по координатам слова
			for (int i = currentWord->Location.Y; i < currentWord->Location.Y + currentWord->Text->Length; ++i)
			{
				bool InsertPossible = true;

				// пытаемся найти общую букву пересечения
				String^ mutualLetter = GetChar(Point(currentWord->Location.X, i));

				// получаем смещение этого слова относительно буквы
				offset = wrd->IndexOf(mutualLetter);

				if (offset != -1)
				{
					// 
					Point beforeBegin = Point(currentWord->Location.X - offset - 1, i);
					Point nextToEnd = Point(currentWord->Location.X - offset + wrd->Length, i);
					Point crossPoint = Point(currentWord->Location.X, i);

					// проверяем соседей текущей буквы
					if (!CheckVerticalNeighbors(crossPoint, beforeBegin, nextToEnd))
						InsertPossible = false;
				}
				else
					InsertPossible = false;

				// если InsertPossible все еще true вписываем слово
				if (InsertPossible)
				{
					// чтобы не запортить экземпляр для следующих итераций, скопируем его
					Board^ temp = gcnew Board(size);

					for (int i = 0; i < size.X; ++i)
						for (int j = 0; j < size.Y; ++j)
							temp->board[i, j] = board[i, j];

					temp->words = gcnew List<Word^ >();
					for each (Word ^ word in words)
						temp->words->Add(gcnew Word(word));

					// абсолютная координата начала нового слова
					int absLeft = currentWord->Location.X - offset;
					// если она отрицательна
					if (absLeft < 0)
					{
						// добавляем столбцы слева
						temp = IncreaseLeft(temp, Math::Abs(absLeft));
						absLeft = 0;
					}

					// абсолютная координата конца нового слова
					int rightDeviation = absLeft + wrd->Length;

					// если она за правой границей поля
					if (rightDeviation > size.X)
						temp = IncreaseRight(temp, rightDeviation - size.X);

					// запишем новое слово начиная с этой координаты на доску
					for (int k = absLeft, j = 0; k < absLeft + wrd->Length; ++k)
						temp->board[k, i] = wrd[j++].ToString();

					// добавим это слово к словам
					Word^ newWord = gcnew Word(wrd, Directions::Horizontal, Point(absLeft, i));
					temp->CollectWord(newWord);

					// сохраняем эту доску в стек
					result->Push(temp);
				}
			}
		}
	}

	return result;
}
inline Generic::Stack<Board^ >^ Board::InsertVertically(String^ wrd)
{
	// создаем временный стек для результата
	Generic::Stack<Board^ >^ result = gcnew Generic::Stack<Board^ >();

	// идем по всем четным словам (горизонтальным) словам
	for each (Word ^ currentWord in words)
	{
		if (currentWord->Direction == Directions::Horizontal)
		{
			// пытаемся проверить впишется ли слово к текущему
			// цикл по ширине, i - итератор по координатам слова
			for (int i = currentWord->Location.X; i < currentWord->Location.X + currentWord->Text->Length; ++i)
			{
				bool InsertPossible = true;

				if (wrd == "Крыльце")
					i = i;

				// резервируем сдвиг слова вверх относительно места скрещивания
				int offset;

				// пытаемся найти общую букву пересечения
				String^ mutualLetter = GetChar(Point(i, currentWord->Location.Y));

				// получаем смещение этого слова относительно буквы
				offset = wrd->IndexOf(mutualLetter);

				if (offset != -1)
				{
					Point beforeBegin = Point(i, currentWord->Location.Y - offset - 1);
					Point nextToEnd = Point(i, currentWord->Location.Y - offset + wrd->Length);
					Point crossPoint = Point(i, currentWord->Location.Y);

					// проверяем соседей текущей буквы
					if (!CheckHorizontalNeighbors(crossPoint, beforeBegin, nextToEnd))
						InsertPossible = false;
				}
				else
					InsertPossible = false;

				// если InsertPossible все еще true вписываем слово
				if (InsertPossible)
				{
					// чтобы не запортить экземпляр для следующих итераций, скопируем его
					Board^ temp = gcnew Board(size);

					for (int i = 0; i < size.X; ++i)
						for (int j = 0; j < size.Y; ++j)
							temp->board[i, j] = board[i, j];

					temp->words = gcnew List<Word^ >();
					for each (Word ^ word in words)
						temp->words->Add(word);

					// абсолютная координата начала нового слова
					int absTop = currentWord->Location.Y - offset;
					// если она отрицательна
					if (absTop < 0)
					{
						// добавляем столбцы сверху
						temp = IncreaseTop(temp, Math::Abs(absTop));
						absTop = 0;
					}

					// абсолютная координата конца нового слова
					int bottomDeviation = absTop + wrd->Length;

					// если она за нижней границей поля
					if (bottomDeviation > size.Y)
						temp = IncreaseBottom(temp, bottomDeviation - size.Y);

					// запишем новое слово начиная с этой координаты на доску
					for (int k = absTop, j = 0; k < absTop + wrd->Length; ++k)
						temp->board[i, k] = wrd[j++].ToString();

					// добавим это слово к словам
					Word^ newWord = gcnew Word(wrd, Directions::Vertical, Point(i, absTop));
					temp->CollectWord(newWord);

					// сохраняем эту доску в стек
					result->Push(temp);
				}
			}
		}
	}

	return result;
}

inline void Board::GetDrawn(Graphics^% easel)
{
	Cell^ cell;

	easel->Clear(SystemColors::Info);

	if (size.Y * scale < easel->VisibleClipBounds.Height && size.X * scale < easel->VisibleClipBounds.Width)
	{
		auto easelHeight = easel->VisibleClipBounds.Height;
		auto easelWidth = easel->VisibleClipBounds.Width;

		auto zeroTop = (easelHeight - size.Y * scale) / 2.5f;
		auto zeroLeft = (easelWidth - size.X * scale) / 2;

		if (resetZeroPoint)
		{
			zeroTop = 0.0f;
			zeroLeft = 0.0f;
		}

		// порядковые номера слов
		int nVertical = 1;
		int nHorizontal = 1;

		for each (auto word in words)
		{
			List<String^>^ letters = gcnew List<String^>();
			for each (auto letter in word->Text)
				letters->Add(letter.ToString());

			for (int i = 0; i < letters->Count; ++i)
			{
				float currentVerticalLeft = zeroLeft + word->Location.X * scale;
				float currentVertiaclTop = zeroTop + word->Location.Y * scale + i * scale;
				float currentHorizontalLeft = zeroLeft + word->Location.X * scale + i * scale;
				float currentHorizontalTop = zeroTop + word->Location.Y * scale;

				if (word->Direction == Directions::Horizontal)
					cell = gcnew Cell(Point((int)currentHorizontalLeft, (int)currentHorizontalTop),
									  (int)scale,
									  cutWords ? " " : letters[i]->ToUpper(),
									  i == 0 ? (nHorizontal++).ToString() : "",
									  false);
				else
					cell = gcnew Cell(Point((int)currentVerticalLeft, (int)currentVertiaclTop),
									  (int)scale,
									  cutWords ?
									  " " : letters[i]->ToUpper(),
									  i == 0 ? (nVertical++).ToString() : "",
									  true);

				// отрисовка ячейки
				drawCell(cell, easel);
			}
		}
	}
	else
		easel->DrawString(L"Составленный кроссворд не вмещается в рабочую область.\r\nВоспользуйтесь предпросмотром.",
						  gcnew Drawing::Font("Calibri", scale / 1.5f, FontStyle::Regular), Brushes::Black, 10, 10);
}
inline void Board::Preview()
{
	auto wMargin = scale;
	auto hMargin = scale;

	// ищем длиннейшее горизонтальное слово
	int maxLength = 0;
	for each (auto item in hWords)
		maxLength = maxLength > item->Text->Length ? maxLength : item->Text->Length;

	auto paperWidth = int(size.X * scale + wMargin * 2 + 1 / hWords->Count * scale * 7 + maxLength * scale);
	auto paperHeight = int(size.Y * scale + hMargin * 2 + 1 / vWords->Count * scale * 4);

	auto print = gcnew PrintDocument();

	print->DefaultPageSettings->PaperSize = gcnew Printing::PaperSize("MySize", paperWidth, paperHeight);
	print->OriginAtMargins = true;
	print->DefaultPageSettings->Margins = gcnew Printing::Margins((int)wMargin, (int)wMargin, (int)hMargin, (int)hMargin);
	print->PrintPage += gcnew PrintPageEventHandler(this, &Board::onPrintPage);

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
inline void Board::drawCell(Cell^ cell, Graphics^% easel)
{
	auto rect = Rectangle(cell->Location.X, cell->Location.Y, cell->CellSize, cell->CellSize);
	easel->DrawRectangle(Pens::Black, rect);
	easel->DrawString(cell->Letter, gcnew Font("Calibri", 10.0f), Brushes::Black, float(cell->Location.X + cell->CellSize / 5), float(cell->Location.Y + cell->CellSize / 8));

	if (cell->Vertical)
		easel->DrawString(cell->Number, gcnew Font("Calibri", 6.0f), Brushes::Maroon, float(cell->Location.X + cell->CellSize) - 7, float(cell->Location.Y) - 1);
	else
		easel->DrawString(cell->Number, gcnew Font("Calibri", 6.0f), Brushes::Maroon, float(cell->Location.X) - 1, float(cell->Location.Y) - 1);
}
inline void Board::onPrintPage(Object^ sender, PrintPageEventArgs^ e)
{
	auto easel = e->Graphics;
	resetZeroPoint = true;
	GetDrawn(easel);

	float top = scale;
	float left = size.X * scale + scale * 2;

	easel->DrawString(L"ПО ГОРИЗОНТАЛИ:", gcnew Drawing::Font("Calibri", scale / 2, FontStyle::Bold), Brushes::Black, left, top);
	top += scale * 0.75f;

	for (auto i = 0; i < hWords->Count; ++i)
	{
		easel->DrawString(i + 1 + ". " + hWords[i]->Text, gcnew Drawing::Font("Calibri", scale / 2), Brushes::Black, left, top);
		top += scale * 0.6f;
	}

	top += scale * 0.75f;
	easel->DrawString(L"ПО ВЕРТИКАЛИ:", gcnew Drawing::Font("Calibri", scale / 2, FontStyle::Bold), Brushes::Black, left, top);
	top += scale * 0.75f;

	for (auto i = 0; i < vWords->Count; ++i)
	{
		easel->DrawString(i + 1 + ". " + vWords[i]->Text, gcnew Drawing::Font("Calibri", scale / 2), Brushes::Black, left, top);
		top += scale * 0.6f;
	}

	easel->DrawString(L"©slim 2020", gcnew Drawing::Font("Calibri", scale / 2), Brushes::LightGray, -scale, -scale);
}
