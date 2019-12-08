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
		array<String^ >^ wordsArray = words->ToArray();


		auto watch = Stopwatch::StartNew();
		List<String^ >^ lst = gcnew List<String^ >(words);
		mkr->Handle(words);
		watch->Stop();
		Console::WriteLine("Calculation has been done in {0} ms", watch->ElapsedMilliseconds);

		mkr->ShowBoard();
		//mkr->ShowFramework();
		mkr->ShowWordsList();


		Console::WriteLine("To resume making attempts press any key\nTo exit program press \"Escape\"");
		key = Console::ReadKey();
		Console::WriteLine();
	}
	while(key->Key != ConsoleKey::Escape);

	return 0;
}