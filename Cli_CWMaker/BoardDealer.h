#pragma once
#include "CompareByLength.h"
#include "Board.h"


ref class BoardDealer
{

public:
	property int StatesCount { int get() { return states->Count; } }
	property int FailsCount { int get() { return failedWords->Count; } }
	property int CurrentHeight { int get() { return currentBoard->Height; } }
	property int CurrentWidth { int get() { return currentBoard->Width; } }
	property array<String^, 2>^ RawBoard { array<String^, 2>^ get() { return currentBoard->Brd; } }

	BoardDealer();

	void setCurrentBoard(int stateNo);
	void reset();
	int handle(Generic::List<String^>^ inputList);
	List<String^>^ gimmeVWords();
	List<String^>^ gimmeHWords();
	array<String^>^ gimmeFails();
	Board^ gimmeBoard();


private:
	Generic::Stack<Board^ >^ states;		// ���� ���������
	Generic::Stack<String^ >^ failedWords;	// ���� ��� �� ����������� ����
	Board^ currentBoard;					// ������� �������������� ���������

	void compose(Generic::List<String^>^ words);
};



BoardDealer::BoardDealer()
{
	states = gcnew Generic::Stack<Board^>();
	failedWords = gcnew Generic::Stack<String^>();
}

void BoardDealer::setCurrentBoard(int stateNo)
{
	currentBoard = states->ToArray()[stateNo];
}
List<String^>^ BoardDealer::gimmeVWords()
{
	return currentBoard->vWords;
}
List<String^>^ BoardDealer::gimmeHWords()
{
	return currentBoard->hWords;
}
array<String^>^ BoardDealer::gimmeFails()
{
	return failedWords->ToArray();
}
Board^ BoardDealer::gimmeBoard()
{
	return currentBoard;
}

void BoardDealer::reset()
{
	states = gcnew Generic::Stack<Board^>();
	failedWords = gcnew Generic::Stack<String^>();
}
int BoardDealer::handle(Generic::List<String^>^ inputList)
{
	compose(inputList);
	return states->Count;
}


void BoardDealer::compose(List<String^>^ words)
{
	Console::WriteLine("\nStarted handling words at " + DateTime::Now);

	// ��������� �� ����� �����
	words->Sort(gcnew CompareByLength());

	auto wrds = gcnew Generic::Stack<String^>(words);

	// ������� ��������� ���� ��� ����������� ��������� � ������ �������
	Generic::Stack<Board^ >^ reserve;

	// ������� ���� ������� � ����� ������� �����
	states->Push(gcnew Board(wrds->Peek()->Length, 1));

	// ���� � ����� ����������� ���� ���� �����
	while (wrds->Count)
	{
		// �������� ���� ���� ��������� � ����� ���������
		do
		{
			// ������� �� ����� ��������� ��������� ���������
			Board^ lastState = states->Pop();

			// ��������� ���� ��� �������� ����������� ���������� ������ �����
			Generic::Stack<Board^ >^ results = gcnew Generic::Stack<Board^ >();

			// ������� ���� ����������� ���������� ����� � ����� ���������
			// �������� �� ������� ����� � ����� ���� ���� ��� �� ������
			results = lastState->Alter(wrds->Peek());

			// ���� ���������� � ��������� �� ������
			if (results->Count != 0)
			{
				// ������ ����� �� ����� ����
				wrds->Pop();
				// � ���� � ����� �� ����������� ���� ���-�� ����, �������
				// ����� ����������� ��� ��� ��������
				if (failedWords->Count)
					wrds->Push(failedWords->Pop());

				// ������� ���� ���������
				states->Clear();

				// ������ ���������� � ���� ���������
				states = gcnew Generic::Stack<Board^ >(results);

				// ������ ���������� � ��������� ������
				reserve = gcnew Generic::Stack<Board^ >(results);

				// ������� �� ��������� ��������� � ���������� �����
				break;
			}
		}
		while (states->Count);

		// ���� �� �������� ���������
		if (!states->Count)
		{
			// �� ���� ���� ��� �� ����
			if (wrds->Count)
			{
				// ����������� ������� ��������� �� ���������� �����
				states = gcnew Generic::Stack<Board^ >(reserve);
				// ��������� ������� ����� ����� ����������� �������� ������
				failedWords->Push(wrds->Pop());
			}
			else
				return;
		}
	}

	return;
}
