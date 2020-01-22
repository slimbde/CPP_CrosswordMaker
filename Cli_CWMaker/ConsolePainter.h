#pragma once
#include "IPainter.h"
#include "Board.h"
using namespace System;
using namespace System::IO;
using namespace System::Runtime::InteropServices;


[DllImport("kernel32.dll", EntryPoint = "AllocConsole", SetLastError = true, CharSet = CharSet::Auto, CallingConvention = CallingConvention::StdCall)]
extern int AllocConsole();

[DllImport("kernel32.dll", EntryPoint = "GetStdHandle", SetLastError = true, CharSet = CharSet::Auto, CallingConvention = CallingConvention::StdCall)]
extern IntPtr GetStdHandle(int nStdHandle);

[DllImport("kernel32.dll")]
extern IntPtr GetConsoleWindow();

[DllImport("user32.dll")]
extern bool ShowWindow(IntPtr hWnd, int nCmdShow);


const int SW_HIDE = 0;
const int SW_SHOW = 5;
const int STD_OUTPUT_HANDLE = -11;
//const int MY_CODE_PAGE = 437;
const int MY_CODE_PAGE = 866;


ref class ConsolePainter : IPainter
{

public:
	virtual property float Scale;
	virtual property bool CutWords;
	virtual property bool ResetZeroPoint;

	ConsolePainter(array<String^, 2>^ board, Board^ readyBoard);

	virtual void drawWords() { };
	virtual void drawBoard() { };
	virtual void preview();


private:
	float scale = 10.0f;
	array<String^, 2>^ board;
	Board^ readyBoard;
};



ConsolePainter::ConsolePainter(array<String^, 2>^ board, Board^ readyBoard)
{
	this->board = board;
	this->readyBoard = readyBoard;
}
void ConsolePainter::preview()
{
	// show console
	AllocConsole();
	auto handle = GetConsoleWindow();
	ShowWindow(handle, SW_SHOW);
	auto stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	auto safeFileHandle = gcnew Microsoft::Win32::SafeHandles::SafeFileHandle(stdHandle, true);
	FileStream^ fileStream = gcnew FileStream(safeFileHandle, FileAccess::Write);
	auto encoding = System::Text::Encoding::GetEncoding(MY_CODE_PAGE);
	auto standardOutput = gcnew StreamWriter(fileStream, encoding);
	standardOutput->AutoFlush = true;
	Console::SetOut(standardOutput);
	Console::Clear();

	// show chart
	int Height = board->GetUpperBound(0) + 1;
	int Width = board->GetUpperBound(1) + 1;

	String^ title = ".:: Crossword Maker. Coded by slimbde 2019 ::.\n";

	auto head = gcnew String('-', Width > 2 ? Width * 2 - 1 : 0);
	head = "+" + head;
	head += "+\n";

	String^ body = "";
	for (int i = 0; i < Height; ++i)
	{
		body += "|";
		for (int j = 0; j < Width; ++j)
		{
			body += String::IsNullOrEmpty(board[i, j]) ? " " : board[i, j];
			body += "|";
		}
		body += "\n";
	}

	auto result = title + head + body + head;
	Console::WriteLine(result);

	// show Words
	Console::WriteLine("Words to guess:");
	auto tmp = gcnew Generic::Stack<Word^>(readyBoard->Words);
	auto wrds = gcnew Generic::Stack<Word^ >();
	while (tmp->Count)
		wrds->Push(tmp->Pop());

	int number = 1;
	while (wrds->Count)
		Console::WriteLine("{0}. {1}", (number++).ToString(), wrds->Pop()->word);
	Console::WriteLine();


	// Hide
	Console::Write("Для закрытия этого окна нажмите любую кнопку");
	Console::ReadKey();
	ShowWindow(handle, SW_HIDE);
}