#include "MainForm.h"
#include "BoardDealer.h"
using namespace CliCWMaker;


[STAThreadAttribute]
Int32 main(array<System::String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	
	BoardDealer^ dealer = gcnew BoardDealer();
	Application::Run(gcnew MainForm(dealer));


	return 0;
}