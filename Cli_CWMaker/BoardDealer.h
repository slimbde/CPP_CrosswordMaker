#pragma once
#include "CompareByLength.h"
#include "Board.h"


ref class BoardDealer
{

public:
	property int StatesCount { int get() { return states->Count; } }
	property int FailsCount { int get() { return failedWords->Count; } }

	BoardDealer();

	void setCurrentBoard(int stateNo);
	void reset();
	int handle(Generic::List<String^>^ inputList);
	List<String^>^ gimmeVWords();
	List<String^>^ gimmeHWords();
	array<String^>^ gimmeFails();
	void DrawBoard(Graphics^% easel, bool cutWords, bool resetZeroPoint);
	void PreviewBoard(bool cutWords);


private:
	Generic::Stack<Board^ >^ states;		// стек состояний
	Generic::Stack<String^ >^ failedWords;	// стек для не вставленных слов
	Board^ currentBoard;					// текущее обрабатываемое состояние

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
	auto result = gcnew List<String^>();
	for each (auto item in currentBoard->vWords)
		result->Add(item->Text);

	return result;
}
List<String^>^ BoardDealer::gimmeHWords()
{
	auto result = gcnew List<String^>();
	for each (auto item in currentBoard->hWords)
		result->Add(item->Text);

	return result;
}
array<String^>^ BoardDealer::gimmeFails()
{
	return failedWords->ToArray();
}
void BoardDealer::DrawBoard(Graphics^% easel, bool cutWords, bool resetZeroPoint)
{
	currentBoard->CutWords = cutWords;
	currentBoard->ResetZeroPoint = resetZeroPoint;
	currentBoard->GetDrawn(easel);
}
void BoardDealer::PreviewBoard(bool cutWords)
{
	currentBoard->CutWords = cutWords;
	currentBoard->Preview();
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

	// сортируем по длине слова
	words->Sort(gcnew CompareByLength());

	auto wrds = gcnew Generic::Stack<String^>(words);

	// создаем резервный стек для предыдущего состояния в случае неудачи
	Generic::Stack<Board^ >^ reserve;

	// создаем поле высотой в самое длинное слово
	states->Push(gcnew Board(Point(1, wrds->Peek()->Length)));

	// пока в стеке вставляемых слов есть слова
	while (wrds->Count)
	{
		// крутимся пока есть состояния в стеке состояний
		do
		{
			// достаем из стека состояний последнее состояние
			Board^ lastState = states->Pop();

			// временный стек для хранения результатов добавления одного слова
			Generic::Stack<Board^ >^ results = gcnew Generic::Stack<Board^ >();

			// получим стек результатов добавления слова к этому состоянию
			// взглянем на верхнее слово в стеке слов пока его не снимая
			results = lastState->Append(wrds->Peek());

			// если получилось и результат не пустой
			if (results->Count != 0)
			{
				// снимем слово со стека слов
				wrds->Pop();
				// а если в стеке не вставленных слов что-то есть, достаем
				// чтобы попробовать еще раз вставить
				if (failedWords->Count)
					wrds->Push(failedWords->Pop());

				// очищаем стек состояний
				states->Clear();

				// пакуем результаты в стек состояний
				states = gcnew Generic::Stack<Board^ >(results);

				// пакуем результаты в резервный массив
				reserve = gcnew Generic::Stack<Board^ >(results);

				// выходим из каруселей состояний к следующему слову
				break;
			}
		}
		while (states->Count);

		// если не осталось состояний
		if (!states->Count)
		{
			// но стек слов еще не пуст
			if (wrds->Count)
			{
				// присваиваем прошлые состояния из резервного стека
				states = gcnew Generic::Stack<Board^ >(reserve);
				// сохраняем текущее слово чтобы попробовать вставить другие
				failedWords->Push(wrds->Pop());
			}
			else
				return;
		}
	}

	return;
}
