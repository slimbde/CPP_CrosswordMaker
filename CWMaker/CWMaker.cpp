#include "Classes\Maker.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Diagnostics;


int main(array<System::String ^> ^args)
{
	// создаем список слов
	List<String^ >^ words = gcnew List<String^ >();

	// создаем экземпляр составителя кроссвордов
	Maker^ mkr = gcnew Maker();

	ConsoleKeyInfo^ key;
	do
	{
		Console::Clear();
		Console::WriteLine(".:: Crossword Maker. Coded by slimbde 2019 ::.");
		Console::WriteLine("Write words separated by a space");
		String^ input = Console::ReadLine();
		words = gcnew List<String^ >((input->Split(' ')));

		auto watch = Stopwatch::StartNew();
		mkr->Handle(words);
		watch->Stop();
		Console::WriteLine("Calculation has been done in {0} ms", watch->ElapsedMilliseconds);

		mkr->ShowBoard();
		Console::WriteLine("To exit program press \"Escape\"\nTo resume making attempts press any key");
		key = Console::ReadKey();
		Console::WriteLine();
	}
	while(key->Key != ConsoleKey::Escape);

	return 0;
}