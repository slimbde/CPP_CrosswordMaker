#pragma once
#include "Word.h"
#include "Point.h"
using namespace System;
using namespace System::Collections::Generic;



ref class Board
{
	int width;						// ������ �����
	int height;						// ������ �����
	array<Word^ >^ words;			// ������ ����
	array<String^, 2>^ board;		// ����� �� �������

	void Draw(array<char, 2>^ brd)
	{
		int hgt = brd->GetLength(0);
		int wdt = brd->GetLength(1);

		String^ head = gcnew String('-', wdt > 2 ? wdt * 2 - 1 : 0);
		head = "+" + head;
		head += "+";
		Console::WriteLine(head);

		for(int i = 0; i < hgt; ++i)
		{
			Console::Write("|");
			for(int j = 0; j < wdt; ++j)
			{
				Console::Write(brd[i, j] == '\0' ? " " : gcnew String(brd[i, j], 1));
				Console::Write("|");
			}
			Console::WriteLine();
		}

		Console::WriteLine(head);
	}

	bool IsEmpty()
	{
		for each(String^ item in board)
			if(!String::IsNullOrEmpty(item))
				return false;
		return true;
	}
	String^ GetChar(Point^ pt)
	{
		try
		{
			return board[pt->top, pt->left];
		}
		catch(Exception^)
		{
			return nullptr;
		}
	}
	void CollectWord(Word^ wrd)
	{
		if(words == nullptr)
			words = gcnew array<Word^>(1) { wrd };
		else
		{
			array<Word^ >^ result = gcnew array<Word^ >(words->Length + 1);
			words->CopyTo(result, 0);
			result[words->Length] = wrd;
			words = result;
		}
	}
	void IncreaseLeft(Board^% brd, int offset)
	{
		// ����� ������ ���� �� offset
		int newWidth = brd->width + offset;
		Board^ temp = gcnew Board(brd->height, newWidth);

		// ��������� ��� ����� �� ����� �� ����� (�� ���������) �������
		for(int i = 0; i < brd->height; ++i)
			for(int j = 0; j < brd->width; ++j)
				temp->board[i, j + offset] = brd->board[i, j];

		// ��������� ������ ���� ������� �� ���������� left
		temp->words = gcnew array<Word^ >(brd->words->Length);
		brd->words->CopyTo(temp->words, 0);
		for each(Word^ item in temp->words)
			item->left += offset;

		brd = temp;
	}
	void IncreaseRight(Board^% brd, int offset)
	{
		// ����� ������ ���� �� offset
		int newWidth = brd->width + offset;
		Board^ temp = gcnew Board(brd->height, newWidth);

		// ��������� ��� ����� �� ����� �� ������� (��� ��������) �������
		for(int i = 0; i < brd->height; ++i)
			for(int j = 0; j < brd->width; ++j)
				temp->board[i, j] = brd->board[i, j];

		// ��������� ������ ���� ��� ��������� �� ���������� left
		temp->words = gcnew array<Word^ >(brd->words->Length);
		brd->words->CopyTo(temp->words, 0);

		brd = temp;
	}
	void IncreaseTop(Board^% brd, int offset)
	{
		// ����� ������ ������ �� offset
		int newHeight = brd->height + offset;
		Board^ temp = gcnew Board(newHeight, brd->width);

		// ��������� ��� ����� �� ����� �� ����� (�� ���������) �������
		for(int i = 0; i < brd->height; ++i)
			for(int j = 0; j < brd->width; ++j)
				temp->board[i + offset, j] = brd->board[i, j];

		// ��������� ������ ���� ������� �� ���������� top
		temp->words = gcnew array<Word^ >(brd->words->Length);
		brd->words->CopyTo(temp->words, 0);
		for each(Word^ item in temp->words)
			item->top += offset;

		brd = temp;
	}
	void IncreaseBottom(Board^% brd, int offset)
	{
		// ����� ������ ������ �� offset
		int newHeight = brd->height + offset;
		Board^ temp = gcnew Board(newHeight, brd->width);

		// ��������� ��� ����� �� ����� �� ������� (��� ��������) �������
		for(int i = 0; i < brd->height; ++i)
			for(int j = 0; j < brd->width; ++j)
				temp->board[i, j] = brd->board[i, j];

		// ��������� ������ ���� ��� ��������� �� ���������� top
		temp->words = gcnew array<Word^ >(brd->words->Length);
		brd->words->CopyTo(temp->words, 0);

		brd = temp;
	}
	bool CheckVerticalNeighbors(Point^ crossPoint, Point^ beforePoint, Point^ nextToPoint)
	{
		// * * * * * * * * * * * * *
		// *|#|#|#|#|#|#|#|#|#|#|#|*
		// * * * * * * * * * * * * *

		// ��������� �� ��� ����� �� ��������� ������ ����� �� ��������� �����
		for(int left = beforePoint->left; left <= nextToPoint->left; ++left)
		{
			// �������� �� 3 ������������ ����� �� ���� ����� ����� ����� �����������
			for(int top = beforePoint->top - 1; top <= beforePoint->top + 1; ++top)
			{
				if(left == crossPoint->left)
					continue;

				if(GetChar(gcnew Point(top, left)) != nullptr)
					return false;
			}
		}

		return true;
	}
	bool CheckHorizontalNeighbors(Point^ crossPoint, Point^ beforePoint, Point^ nextToPoint)
	{
		// ��������� �� ��� ����� �� ��������� ������ ����� �� ��������� �����
		for(int top = beforePoint->top; top <= nextToPoint->top; ++top)
		{
			// �������� �� 3 �������������� ����� �� ���� ����� ����� ����� �����������
			for(int left = beforePoint->left - 1; left <= beforePoint->left + 1; ++left)
			{
				if(top == crossPoint->top)
					continue;

				if(GetChar(gcnew Point(top, left)) != nullptr)
					return false;
			}
		}

		return true;
	}
	Stack<Board^ >^ InsertHorizontally(String^ wrd)
	{
		// ������� ��������� ���� ��� ����������
		Stack<Board^ >^ result = gcnew Stack<Board^ >();

		// ���� �� ���� ������ ������ (��������������) ������
		for each(Word^ currentWord in words)
		{
			if(currentWord->layout == Layout::Vertical)
			{
				// ����������� ����� ����� ����� ������������ ����� �����������
				int offset;

				// �������� ��������� �������� �� ����� � ��������
				// ���� �� ������, i - �������� �� ����������� �����
				for(int i = currentWord->top; i < currentWord->top + currentWord->length; ++i)
				{
					bool InsertPossible = true;

					// �������� ����� ����� ����� �����������
					String^ mutualLetter = GetChar(gcnew Point(i, currentWord->left));

					// �������� �������� ����� ����� ������������ �����
					offset = wrd->IndexOf(mutualLetter);

					if(offset != -1)
					{
						Point^ beforeBegin = gcnew Point(i, currentWord->left - offset - 1);
						Point^ nextToEnd = gcnew Point(i, currentWord->left - offset + wrd->Length + 1);
						Point^ crossPoint = gcnew Point(i, currentWord->left);

						// ��������� ������� ������� �����
						if(CheckVerticalNeighbors(crossPoint, beforeBegin, nextToEnd))
						{
								// ���������� ���������� ������ ������ �����
							int wrdLeft = currentWord->left - offset;
							// ���������� ���������� ������ ����� �� ������
							int wrdTop = i;

							// ��������� ������ ����� ������������ ����� �� ����������
							// � ������� (��� ���������) �� �����
							for(int j = wrdLeft, k = 0; j < wrdLeft + wrd->Length; ++j)
							{
								// ����� ������� ������ ����������� �����
								String^ currentBoardLetter = GetChar(gcnew Point(wrdTop, j));
								// ���� ��� �� ����������� ����� ��� �� �������
								if(currentBoardLetter != wrd[k++].ToString() && currentBoardLetter != nullptr)
								{
									InsertPossible = false;
									break;
								}
							}
							// ���� ��� ���������� �� ���������� �������� - ������������� ������
							if(!InsertPossible)
								break;
						}
						else
							InsertPossible = false;
					}
					else
						InsertPossible = false;

					// ���� InsertPossible ��� ��� true ��������� �����
					if(InsertPossible)
					{
						// ����� �� ��������� ��������� ��� ��������� ��������, ��������� ���
						Board^ temp = gcnew Board(height, width);

						for(int i = 0; i < height; ++i)
							for(int j = 0; j < width; ++j)
								temp->board[i, j] = board[i, j];

						temp->words = gcnew array<Word^ >(words->Length);
						for(int i = 0; i < words->Length; ++i)
							temp->words[i] = gcnew Word(words[i]);

						// ���������� ���������� ������ ������ �����
						int absLeft = currentWord->left - offset;
						// ���� ��� ������������
						if(absLeft < 0)
						{
							// ��������� ������� �����
							IncreaseLeft(temp, Math::Abs(absLeft));
							// ������ ��� ���������� ���������� � ������ �����
							absLeft = 0;
						}

						// ���������� ���������� ����� ������ �����
						int rightDeviation = absLeft + wrd->Length;
						// ���� ��� �� ������ �������� ����
						if(rightDeviation > width)
							// ������� ����� ����� (���������� ���������� �� ���������)
							IncreaseRight(temp, rightDeviation - width);

						// ������� ����� ����� ������� � ���� ���������� �� �����
						for(int k = absLeft, j = 0; k < absLeft + wrd->Length; ++k)
							temp->board[i, k] = wrd[j++].ToString();

						// ������� ��� ����� � ������
						Word^ newWord = gcnew Word(wrd, Layout::Horizontal, i, absLeft);
						temp->CollectWord(newWord);

						// ��������� ��� ����� � ����
						result->Push(temp);
					}
				}
			}
		}

		return result;
	}
	Stack<Board^ >^ InsertVertically(String^ wrd)
	{
		// ������� ��������� ���� ��� ����������
		Stack<Board^ >^ result = gcnew Stack<Board^ >();

		// ���� �� ���� ������ ������ (��������������) ������
		for each(Word^ currentWord in words)
		{
			if(currentWord->layout == Layout::Horizontal)
			{
				// �������� ��������� �������� �� ����� � ��������
				// ���� �� ������, i - �������� �� ����������� �����
				for(int i = currentWord->left; i < currentWord->left + currentWord->length; ++i)
				{
					bool InsertPossible = true;

					// ����������� ����� ����� ����� ������������ ����� �����������
					int offset;

					// �������� ����� ����� ����� �����������
					String^ mutualLetter = GetChar(gcnew Point(currentWord->top, i));

					// �������� �������� ����� ����� ������������ �����
					offset = wrd->IndexOf(mutualLetter);

					if(offset != -1)
					{
						Point^ beforeBegin = gcnew Point(currentWord->top - offset - 1, i);
						Point^ nextToEnd = gcnew Point(currentWord->top - offset + wrd->Length + 1, i);
						Point^ crossPoint = gcnew Point(currentWord->top, i);

						// ��������� ������� ������� �����
						if(CheckHorizontalNeighbors(crossPoint, beforeBegin, nextToEnd))
						{
							// ���������� ���������� ������ ������ �����
							int wrdTop = currentWord->top - offset;
							// ���������� ���������� ������ ����� �� ������
							int wrdLeft = i;

							// ��������� ������ ����� ������������ ����� �� ����������
							// � ������� (��� ���������) �� �����
							for(int j = wrdTop, k = 0; j < wrdTop + wrd->Length; ++j)
							{
								// ����� ������� ������ ����������� �����
								String^ currentBoardLetter = GetChar(gcnew Point(j, wrdLeft));
								// ���� ��� �� ����������� ����� ��� �� �������
								if(currentBoardLetter != wrd[k++].ToString() && currentBoardLetter != nullptr)
								{
									InsertPossible = false;
									break;
								}
							}
							// ���� ��� ���������� �� ���������� �������� - ������������� ������
							if(!InsertPossible)
								break;
						}
						else
							InsertPossible = false;
					}
					else
						InsertPossible = false;

					// ���� InsertPossible ��� ��� true ��������� �����
					if(InsertPossible)
					{
						// ����� �� ��������� ��������� ��� ��������� ��������, ��������� ���
						Board^ temp = gcnew Board(height, width);

						for(int i = 0; i < height; ++i)
							for(int j = 0; j < width; ++j)
								temp->board[i, j] = board[i, j];

						temp->words = gcnew array<Word^ >(words->Length);
						for(int i = 0; i < words->Length; ++i)
							temp->words[i] = gcnew Word(words[i]);

						// ���������� ���������� ������ ������ �����
						int absTop = currentWord->top - offset;
						// ���� ��� ������������
						if(absTop < 0)
						{
							// ��������� ������� ������
							IncreaseTop(temp, Math::Abs(absTop));
							// ������ ��� ���������� ���������� � ������ �����
							absTop = 0;
						}

						// ���������� ���������� ����� ������ �����
						int bottomDeviation = absTop + wrd->Length;
						// ���� ��� �� ������ �������� ����
						if(bottomDeviation > temp->height)
							// ������� ����� ����� (���������� ���������� �� ���������)
							IncreaseBottom(temp, bottomDeviation - temp->height);

						// ������� ����� ����� ������� � ���� ���������� �� �����
						for(int k = absTop, j = 0; k < absTop + wrd->Length; ++k)
							temp->board[k, i] = wrd[j++].ToString();

						// ������� ��� ����� � ������
						Word^ newWord = gcnew Word(wrd, Layout::Vertical, absTop, i);
						temp->CollectWord(newWord);

						// ��������� ��� ����� � ����
						result->Push(temp);
					}
				}
			}
		}

		return result;
	}

public:
	virtual ~Board();
	Board(int height, int width);

	void Show();
	Stack<Board^ >^ Alter(String^ wrd);
};




inline Board::~Board()
{
}
inline Board::Board(int height, int width)
{
	this->width = width;
	this->height = height;
	board = gcnew array<String^, 2>(height, width);
}


inline void Board::Show()
{
	String^ head = gcnew String('-', width > 2 ? width * 2 - 1 : 0);
	head = "+" + head;
	head += "+";
	Console::WriteLine(head);

	for(int i = 0; i < height; ++i)
	{
		Console::Write("|");
		for(int j = 0; j < width; ++j)
		{
			Console::Write(String::IsNullOrEmpty(board[i, j]) ? " " : board[i, j]);
			Console::Write("|");
		}
		Console::WriteLine();
	}

	Console::WriteLine(head);
}
inline Stack<Board^ >^ Board::Alter(String^ wrd)
{
	// ���� ����� �����, ������� ������ �����
	if(IsEmpty())
	{
		// ����� ����� ����� � ������� �������
		for(int i = 0; i < height; ++i)
			board[i, 0] = wrd[i].ToString();

		// ��������� ����� � ������ ����
		CollectWord(gcnew Word(wrd, Layout::Vertical, 0, 0));

		// ������� ��������� ���� ��� ����������
		Stack<Board^ >^ result = gcnew Stack<Board^ >();
		result->Push(this);

		return result;
	}
	else // ���� ����� �� �����
	{
		// ������� ������� ����� �������������
		Stack<Board^ >^ result = InsertHorizontally(wrd);
		// ������� ������� ����� �����������
		Stack<Board^ >^ extraResult = InsertVertically(wrd);

		// ��������� ���� ����������� ������� �����������
		while(extraResult->Count)
			result->Push(extraResult->Pop());

		//Draw(board);
		return result;
	}
}