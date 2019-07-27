#pragma once
#include "Board.h"
#include "CompareByLength.h"
using namespace System;
using namespace System::Collections::Generic;



ref class Maker
{
	Stack<Board^ >^ states;
	Stack<String^ >^ wrds;

public:
	virtual ~Maker();
	Maker();

	bool Handle(IEnumerable<String^ >^ words);
	void ShowBoard();
};



inline Maker::~Maker()
{
}
inline Maker::Maker()
{
	states = gcnew Stack<Board^ >();
}

inline bool Maker::Handle(IEnumerable<String^ >^ words)
{
	Console::WriteLine("\nStarted handling words");

	// сортируем по длине слова
	((List<String^>^)words)->Sort(gcnew CompareByLength());
	// перегоним слова в стек
	wrds = gcnew Stack<String^>(words);

	// создаем резервный стек для предыдущего состояния в случае неудачи
	Stack<Board^ >^ reserve;

	// создаем поле высотой в самое длинное слово и шириной равной второму по длине
	states->Push(gcnew Board(wrds->Peek()->Length, 1));

	// разместим слова на доске
	while(wrds->Count)
	{
		// флаг успешного получения результатов
		bool success;

		do
		{
			// установим флаг success в true
			success = true;

			// если стек состояний не пуст
			while(states->Count)
			{
				// достаем из стека последнее состояние
				Board^ lastBoard = states->Pop();

				// временный стек для хранения результатов добавления одного слова
				Stack<Board^ >^ results = gcnew Stack<Board^ >();

				// получим стек результатов добавления слова к этому состоянию
				// взглянем на верхнее слово в стеке пока его не снимая
				results = lastBoard->Alter(wrds->Peek());

				// если получилось и результат не пустой
				if(results->Count != 0)
				{
					// если у нас получилось вставить слово - снимем его со стека слов
					wrds->Pop();

					// очищаем стек состояний
					states->Clear();
					// пакуем результаты в стек состояний
					states = gcnew Stack<Board^ >(results);

					// пакуем результаты в резервный массив
					reserve = gcnew Stack<Board^ >(states);

					// и т.к. success по прежнему в true - выходим из цикла
					break;
				}
				else
				{
					// если не получилось вставить слово, то вернемся и достанем
					// следующее состояние и попробуем туда вставить это слово
					success = false;
					break;
				}
			}

			// если мы не можем упаковать слово никаким способом, то вернем предыдущие
			if(!states->Count)
			{
				states = gcnew Stack<Board^ >(reserve);
				Console::WriteLine("Cannot handle all of words, but");
				return false;
			}
		}
		while(!success);
	}

	return true;
}
inline void Maker::ShowBoard()
{
	Console::WriteLine("Found {0} solutions:", states->Count);
	while(states->Count)
		states->Pop()->Show();
	Console::WriteLine("There are {0} words left: ", wrds->Count);
	while(wrds->Count)
		Console::WriteLine(wrds->Pop());
	Console::WriteLine();
}