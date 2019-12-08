#pragma once
#include "Board.h"
#include "CompareByLength.h"
using namespace System;
using namespace System::Collections;



ref class Maker
{
    Generic::Stack<Board^ >^ states;		// стек состояний
    Generic::Stack<String^ >^ wrds;			// стек для вставляемых слов
    Generic::Stack<String^ >^ failedWords;	// стек для не вставленных слов
    int wordsCount;

public:
    virtual ~Maker();
    Maker();

    bool			Handle(List<String^ >^ words);
    void			ShowWordsList();
    void			ShowBoard();
    void			ShowFramework();
    List<Board^>^ gimmeStates();
    List<String^>^ gimmeFails();
};



inline Maker::~Maker()
{ }
inline Maker::Maker()
{
    states = gcnew Generic::Stack<Board^ >();
    failedWords = gcnew Generic::Stack<String^ >();
}

inline bool Maker::Handle(List<String^ >^ words)
{
    Console::WriteLine("\nStarted handling words at " + DateTime::Now);

    // сортируем по длине слова
    words->Sort(gcnew CompareByLength());
    // перегоним слова в стек
    wrds = gcnew Generic::Stack<String^>(words);
    wordsCount = wrds->Count;

    // создаем резервный стек для предыдущего состояния в случае неудачи
    Generic::Stack<Board^ >^ reserve;

    // создаем поле высотой в самое длинное слово
    states->Push(gcnew Board(wrds->Peek()->Length, 1));

    // пока в стеке слов есть слова
    while(wrds->Count)
    {
        // крутимся пока есть состояния в стеке
        do
        {
            // достаем из стека последнее состояние
            Board^ lastState = states->Pop();

            // временный стек для хранения результатов добавления одного слова
            Generic::Stack<Board^ >^ results = gcnew Generic::Stack<Board^ >();

            // получим стек результатов добавления слова к этому состоянию
            // взглянем на верхнее слово в стеке пока его не снимая
            results = lastState->Alter(wrds->Peek());

            // если получилось и результат не пустой
            if(results->Count != 0)
            {
                // снимем слово со стека слов
                wrds->Pop();
                // а если в стеке не вставленных слов что-то есть, достаем
                // чтобы попробовать еще раз вставить
                if(failedWords->Count)
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
        while(states->Count);

        // если не осталось состояний
        if(!states->Count)
        {
            // но стек слов еще не пуст
            if(wrds->Count)
            {
                // присваиваем прошлые состояния из резервного стека
                states = gcnew Generic::Stack<Board^ >(reserve);
                // сохраняем текущее слово чтобы попробовать вставить другие
                failedWords->Push(wrds->Pop());
            }
            else
                return false;
        }
    }

    return true;
}
inline void Maker::ShowWordsList()
{
    if(!states->Count)
    {
        Console::WriteLine("There is nothing to give back. Gimme some words first.");
        return;
    }

    Console::WriteLine("Words to guess:");

    Generic::Stack<Word^ >^ tmp = gcnew Generic::Stack<Word^ >(states->Peek()->GetWords());
    Generic::Stack<Word^ >^ wrds = gcnew Generic::Stack<Word^ >();
    while(tmp->Count)
        wrds->Push(tmp->Pop());

    int number = 1;
    while(wrds->Count)
        Console::WriteLine("{0}. {1}", (number++).ToString(), wrds->Pop()->word);
    Console::WriteLine();
}
inline void Maker::ShowBoard()
{
    Console::WriteLine("Handled {0} words\nFound {1} solutions:", wordsCount, states->Count);
    Generic::Stack<Board^ >^ temp = gcnew Generic::Stack<Board^ >(states);

    while(temp->Count)
        temp->Pop()->Show();
    String^ answer = failedWords->Count > 1 ? "There are " : "There is ";
    Console::WriteLine(answer + "{0} words left:", failedWords->Count);

    if(failedWords->Count)
        while(failedWords->Count)
            Console::WriteLine(failedWords->Pop());

    Console::WriteLine();
}
inline void Maker::ShowFramework()
{
    states->Peek()->ShowFramework();
}
inline List<Board^>^ Maker::gimmeStates()
{
    return gcnew List<Board^>(states);
}
inline List<String^>^ Maker::gimmeFails()
{
    return gcnew List<String^>(failedWords);
}