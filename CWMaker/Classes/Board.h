#pragma once
#include "Word.h"
#include "Point.h"
using namespace System;
using namespace System::Collections;
using namespace System::Text;


ref class Board
{
    int width;						// ширина доски
    int height;						// высота доски
    array<Word^ >^ words;			// список слов
    array<String^, 2>^ board;		// доска со словами

    void Draw(array<String^, 2>^ brd)
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
                Console::Write(brd[i, j] == nullptr ? " " : brd[i, j]);
                Console::Write("|");
            }
            Console::WriteLine();
        }

        Console::WriteLine(head);
    }
    int GetWordNumber(int top, int left)
    {
        for(int k = 0; k < words->Length; ++k)
        {
            if(words[k]->layout == CWM::Layout::Horizontal)
                if(words[k]->top == top)
                    for(int i = 0; i < words[k]->length; ++i)
                        if(words[k]->left + i == left)
                            return k + 1;
            if(words[k]->layout == CWM::Layout::Vertical)
                if(words[k]->left == left)
                    for(int i = 0; i < words[k]->length; ++i)
                        if(words[k]->top + i == top)
                            return k + 1;
        }
        return -1;
    }


    bool IsEmpty()
    {
        for each(String ^ item in board)
            if(!String::IsNullOrEmpty(item))
                return false;
        return true;
    }
    String^ GetChar(CWM::Point^ pt)
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
        // новая ширина шире на offset
        int newWidth = brd->width + offset;
        Board^ temp = gcnew Board(brd->height, newWidth);

        // перепишем все буквы на доске на новые (со смещением) позиции
        for(int i = 0; i < brd->height; ++i)
            for(int j = 0; j < brd->width; ++j)
                temp->board[i, j + offset] = brd->board[i, j];

        // скопируем массив слов изменяя их координаты left
        temp->words = gcnew array<Word^ >(brd->words->Length);
        brd->words->CopyTo(temp->words, 0);
        for each(Word ^ item in temp->words)
            item->left += offset;

        brd = temp;
    }
    void IncreaseRight(Board^% brd, int offset)
    {
        // новая ширина шире на offset
        int newWidth = brd->width + offset;
        Board^ temp = gcnew Board(brd->height, newWidth);

        // перепишем все буквы на доске на прежние (без смещения) позиции
        for(int i = 0; i < brd->height; ++i)
            for(int j = 0; j < brd->width; ++j)
                temp->board[i, j] = brd->board[i, j];

        // скопируем массив слов без изменения их координаты left
        temp->words = gcnew array<Word^ >(brd->words->Length);
        brd->words->CopyTo(temp->words, 0);

        brd = temp;
    }
    void IncreaseTop(Board^% brd, int offset)
    {
        // новая высота больше на offset
        int newHeight = brd->height + offset;
        Board^ temp = gcnew Board(newHeight, brd->width);

        // перепишем все буквы на доске на новые (со смещением) позиции
        for(int i = 0; i < brd->height; ++i)
            for(int j = 0; j < brd->width; ++j)
                temp->board[i + offset, j] = brd->board[i, j];

        // скопируем массив слов изменяя их координаты top
        temp->words = gcnew array<Word^ >(brd->words->Length);
        brd->words->CopyTo(temp->words, 0);
        for each(Word ^ item in temp->words)
            item->top += offset;

        brd = temp;
    }
    void IncreaseBottom(Board^% brd, int offset)
    {
        // новая высота больше на offset
        int newHeight = brd->height + offset;
        Board^ temp = gcnew Board(newHeight, brd->width);

        // перепишем все буквы на доске на прежние (без смещения) позиции
        for(int i = 0; i < brd->height; ++i)
            for(int j = 0; j < brd->width; ++j)
                temp->board[i, j] = brd->board[i, j];

        // скопируем массив слов без изменения их координаты top
        temp->words = gcnew array<Word^ >(brd->words->Length);
        brd->words->CopyTo(temp->words, 0);

        brd = temp;
    }
    bool CheckVerticalNeighbors(CWM::Point^ crossPoint, CWM::Point^ beforePoint, CWM::Point^ nextToPoint)
    {
        // * * * * * * * * * * * * *
        // *|#|#|#|#|#|#|#|#|#|#|#|*
        // * * * * * * * * * * * * *

        // проверяем по три точки от координат начала слова до координат конца
        for(int left = beforePoint->left; left <= nextToPoint->left; ++left)
        {
            // проверим по 3 вертикальных точки по всей длине слова кроме пересечения
            for(int top = beforePoint->top - 1; top <= beforePoint->top + 1; ++top)
            {
                if(left == crossPoint->left)
                    continue;

                if(GetChar(gcnew CWM::Point(top, left)) != nullptr)
                    return false;
            }
        }

        return true;
    }
    bool CheckHorizontalNeighbors(CWM::Point^ crossPoint, CWM::Point^ beforePoint, CWM::Point^ nextToPoint)
    {
        // проверяем по три точки от координат начала слова до координат конца
        for(int top = beforePoint->top; top <= nextToPoint->top; ++top)
        {
            // проверим по 3 горизонтальных точки по всей длине слова кроме пересечения
            for(int left = beforePoint->left - 1; left <= beforePoint->left + 1; ++left)
            {
                if(top == crossPoint->top)
                    continue;

                if(GetChar(gcnew CWM::Point(top, left)) != nullptr)
                    return false;
            }
        }

        return true;
    }
    Generic::Stack<Board^ >^ InsertHorizontally(String^ wrd)
    {
        // создаем временный стек для результата
        Generic::Stack<Board^ >^ result = gcnew Generic::Stack<Board^ >();

        // идем по всем вертикальным словам
        for each(Word ^ currentWord in words)
        {
            if(currentWord->layout == CWM::Layout::Vertical)
            {
                // резервируем сдвиг слова влево относительно места скрещивания
                int offset;

                // пытаемся проверить впишется ли слово к текущему
                // цикл по высоте, i - итератор по координатам слова
                for(int i = currentWord->top; i < currentWord->top + currentWord->length; ++i)
                {
                    bool InsertPossible = true;

                    // пытаемся найти общую букву пересечения
                    String^ mutualLetter = GetChar(gcnew CWM::Point(i, currentWord->left));

                    // получаем смещение этого слова относительно буквы
                    offset = wrd->IndexOf(mutualLetter);

                    if(offset != -1)
                    {
                        // 
                        CWM::Point^ beforeBegin = gcnew CWM::Point(i, currentWord->left - offset - 1);
                        CWM::Point^ nextToEnd = gcnew CWM::Point(i, currentWord->left - offset + wrd->Length + 1);
                        CWM::Point^ crossPoint = gcnew CWM::Point(i, currentWord->left);

                        // проверяем соседей текущей буквы
                        if(!CheckVerticalNeighbors(crossPoint, beforeBegin, nextToEnd))
                            InsertPossible = false;
                    }
                    else
                        InsertPossible = false;

                    // если InsertPossible все еще true вписываем слово
                    if(InsertPossible)
                    {
                        // чтобы не запортить экземпляр для следующих итераций, скопируем его
                        Board^ temp = gcnew Board(height, width);

                        for(int i = 0; i < height; ++i)
                            for(int j = 0; j < width; ++j)
                                temp->board[i, j] = board[i, j];

                        temp->words = gcnew array<Word^ >(words->Length);
                        for(int i = 0; i < words->Length; ++i)
                            temp->words[i] = gcnew Word(words[i]);

                        // абсолютная координата начала нового слова
                        int absLeft = currentWord->left - offset;
                        // если она отрицательна
                        if(absLeft < 0)
                        {
                            // добавляем столбцы слева
                            IncreaseLeft(temp, Math::Abs(absLeft));
                            // теперь эта абсолютная координата в начале доски
                            absLeft = 0;
                        }

                        // абсолютная координата конца нового слова
                        int rightDeviation = absLeft + wrd->Length;
                        // если она за правой границей поля
                        if(rightDeviation > width)
                            // двигаем доску влево (абсолютная координата не изменится)
                            IncreaseRight(temp, rightDeviation - width);

                        // запишем новое слово начиная с этой координаты на доску
                        for(int k = absLeft, j = 0; k < absLeft + wrd->Length; ++k)
                            temp->board[i, k] = wrd[j++].ToString();

                        // добавим это слово к словам
                        Word^ newWord = gcnew Word(wrd, CWM::Layout::Horizontal, i, absLeft);
                        temp->CollectWord(newWord);

                        // сохраняем эту доску в стек
                        result->Push(temp);
                    }
                }
            }
        }

        return result;
    }
    Generic::Stack<Board^ >^ InsertVertically(String^ wrd)
    {
        // создаем временный стек для результата
        Generic::Stack<Board^ >^ result = gcnew Generic::Stack<Board^ >();

        // идем по всем четным словам (горизонтальным) словам
        for each(Word ^ currentWord in words)
        {
            if(currentWord->layout == CWM::Layout::Horizontal)
            {
                // пытаемся проверить впишется ли слово к текущему
                // цикл по ширине, i - итератор по координатам слова
                for(int i = currentWord->left; i < currentWord->left + currentWord->length; ++i)
                {
                    bool InsertPossible = true;

                    // резервируем сдвиг слова вверх относительно места скрещивания
                    int offset;

                    // пытаемся найти общую букву пересечения
                    String^ mutualLetter = GetChar(gcnew CWM::Point(currentWord->top, i));

                    // получаем смещение этого слова относительно буквы
                    offset = wrd->IndexOf(mutualLetter);

                    if(offset != -1)
                    {
                        CWM::Point^ beforeBegin = gcnew CWM::Point(currentWord->top - offset - 1, i);
                        CWM::Point^ nextToEnd = gcnew CWM::Point(currentWord->top - offset + wrd->Length + 1, i);
                        CWM::Point^ crossPoint = gcnew CWM::Point(currentWord->top, i);

                        // проверяем соседей текущей буквы
                        if(!CheckHorizontalNeighbors(crossPoint, beforeBegin, nextToEnd))
                            InsertPossible = false;
                    }
                    else
                        InsertPossible = false;

                    // если InsertPossible все еще true вписываем слово
                    if(InsertPossible)
                    {
                        // чтобы не запортить экземпляр для следующих итераций, скопируем его
                        Board^ temp = gcnew Board(height, width);

                        for(int i = 0; i < height; ++i)
                            for(int j = 0; j < width; ++j)
                                temp->board[i, j] = board[i, j];

                        temp->words = gcnew array<Word^ >(words->Length);
                        for(int i = 0; i < words->Length; ++i)
                            temp->words[i] = gcnew Word(words[i]);

                        // абсолютная координата начала нового слова
                        int absTop = currentWord->top - offset;
                        // если она отрицательна
                        if(absTop < 0)
                        {
                            // добавляем столбцы сверху
                            IncreaseTop(temp, Math::Abs(absTop));
                            // теперь эта абсолютная координата в начале доски
                            absTop = 0;
                        }

                        // абсолютная координата конца нового слова
                        int bottomDeviation = absTop + wrd->Length;
                        // если она за нижней границей поля
                        if(bottomDeviation > temp->height)
                            // двигаем доску влево (абсолютная координата не изменится)
                            IncreaseBottom(temp, bottomDeviation - temp->height);

                        // запишем новое слово начиная с этой координаты на доску
                        for(int k = absTop, j = 0; k < absTop + wrd->Length; ++k)
                            temp->board[k, i] = wrd[j++].ToString();

                        // добавим это слово к словам
                        Word^ newWord = gcnew Word(wrd, CWM::Layout::Vertical, absTop, i);
                        temp->CollectWord(newWord);

                        // сохраняем эту доску в стек
                        result->Push(temp);
                    }
                }
            }
        }

        return result;
    }

public:
    property int Width {
        int get() { return width; }
    }
    property int Height {
        int get() { return height; }
    }

    virtual ~Board();
    Board(int height, int width);

    void Show();
    void ShowFramework();
    array<String^, 2>^ gimmeBoard();	// winForms method
    array<Word^ >^ GetWords();
    Generic::Stack<Board^ >^ Alter(String^ wrd);
};




inline Board::~Board()
{ }
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
inline void Board::ShowFramework()
{
    Console::WriteLine();
    String^ head = gcnew String('-', width > 2 ? width * (int)2.7 : 1);
    head = "+" + head;
    head += "+";
    Console::WriteLine(head);

    for(int i = 0; i < height; ++i)
    {
        for(int j = 0; j < width; ++j)
        {
            int num = GetWordNumber(i, j);
            String^ str = num > 9 ? num.ToString() + " " : num.ToString() + "  ";
            Console::Write(num != -1 ? str : "   ");
        }
        Console::WriteLine();
    }

    Console::WriteLine(head);
    Console::WriteLine();
}
inline array<String^, 2>^ Board::gimmeBoard()
{
    return board;
}
inline array<Word^>^ Board::GetWords()
{
    return words;
}
inline Generic::Stack<Board^ >^ Board::Alter(String^ wrd)
{
    // если доска пуста, добавим первое слово
    if(IsEmpty())
    {
        // пишем номер слово в нулевой столбец
        for(int i = 0; i < height; ++i)
            board[i, 0] = wrd[i].ToString();

        // добавляем слово в список слов
        CollectWord(gcnew Word(wrd, CWM::Layout::Vertical, 0, 0));

        // создаем временный стек для результата
        auto result = gcnew Generic::Stack<Board^ >();
        result->Push(this);

        return result;
    }
    else // если доска не пуста
    {
        // пробуем вписать слово горизонтально
        auto result = InsertHorizontally(wrd);
        // пробуем вписать слово вертикально
        auto extraResult = InsertVertically(wrd);

        // дополняем стек результатов вставки вертикально
        while(extraResult->Count)
        {
            //Draw((extraResult->Peek())->board);
            result->Push(extraResult->Pop());
        }

        return result;
    }
}
