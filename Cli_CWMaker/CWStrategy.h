#pragma once
#include "IStrategy.h"
#include "BoardDealer.h"
#include "PaintDealer.h"
using namespace System::Diagnostics;


ref class CWStrategy : IStrategy
{

public:
	CWStrategy() { toolTip = gcnew System::Windows::Forms::ToolTip(); }

	// Унаследовано через IStrategy
	virtual void setObject(Form^ obj);  // установка объекта манипулирования

	virtual void reset();
	virtual void inputFieldEnter();
	virtual void inputFieldLeave();
	virtual void clearField();
	virtual void handle();
	virtual void next();
	virtual void preview();
	virtual void about();
	virtual void newOne();


private:
	BoardDealer^ bDealer;		// класс инкапсулирующий математическую модель доски

	Form^ mainForm;             // указатель объекта, с которым будем делать "всякое"..
	Stopwatch^ watch;			// часы для замера производительности
	ToolTip^ toolTip;           // экземпляр подсказки
	List<String^>^ vWords;      // слова по вертикали текущего состояния
	List<String^>^ hWords;      // слова по горизонтали текущего состояния


	Object^ getControl(String^ name);       // вытаскивает нужный элемент из объекта формы
	List<String^>^ splitInput(Array^ arr);  // обработка введенных слов
	void handleStates();
	void handleFails();
	void vhTextBoxesFill();
};


void CWStrategy::setObject(Form^ obj)
{
	bDealer = gcnew BoardDealer();
	mainForm = obj;
}
void CWStrategy::reset()
{
	bDealer->reset();

	// динамическое изменение компонентов формы
	((TabControl^)getControl("tabControl1"))->SelectedIndex = 0;
	((TextBox^)getControl("tbVertical"))->Text = "";
	((TextBox^)getControl("tbHorizontal"))->Text = "";
	((TextBox^)getControl("tbCountStates"))->Text = "0";
	((TextBox^)getControl("tbNotFitted"))->Text = "0";
	((ToolStripButton^)getControl("bCutWords"))->Checked = false;
	((ToolStripButton^)getControl("bCutWords"))->Enabled = false;
	((NumericUpDown^)getControl("numericUpDown1"))->Minimum = 0;
	((NumericUpDown^)getControl("numericUpDown1"))->Maximum = 0;
	((Label^)getControl("lOverflow"))->Visible = false;

	auto easel = ((Panel^)getControl("panel1"))->CreateGraphics();
	easel->Clear(SystemColors::Info);
}
void CWStrategy::inputFieldEnter()
{
	auto input = ((TextBox^)getControl("tbSource"));

	if (input->GetType() == TextBox::typeid)
	{
		auto tb = (TextBox^)input;
		if (tb->Lines->Length && tb->Lines[0] == "Введите слова")
		{
			tb->Lines = nullptr;
			tb->ForeColor = Color::Black;
		}
	}
}
void CWStrategy::inputFieldLeave()
{
	auto input = ((TextBox^)getControl("tbSource"));

	if (input->GetType() == TextBox::typeid)
	{
		auto tb = (TextBox^)input;
		if (!tb->Lines->Length)
		{
			tb->ForeColor = SystemColors::ButtonShadow;
			tb->Lines = gcnew array<String^>{ "Введите слова", "через пробел", "или с новых строк" };
		}
	}
}
void CWStrategy::clearField()
{
	auto field = ((TextBox^)getControl("tbSource"));

	if (field->GetType() == TextBox::typeid)
	{
		auto tb = (TextBox^)field;
		tb->ForeColor = SystemColors::ButtonShadow;
		tb->Lines = gcnew array<String^>{ "Введите слова", "через пробел", "или с новых строк" };
	}
}
void CWStrategy::handle()
{
	((Label^)getControl("lOverflow"))->Visible = false;

	auto input = ((TextBox^)getControl("tbSource"))->Lines;
	auto inputList = splitInput(input);

	if (inputList->Count < 2 || input->Length && input[0] == "Введите слова")
		MessageBox::Show(mainForm, "Введите хотя бы два слова!");
	else
	{
		watch = Stopwatch::StartNew();
		String^ statusString;

		bDealer->handle(inputList);
		watch->Stop();

		handleStates();
		handleFails();
		statusString = String::Format("Расчет выполнен за {0} ms", watch->ElapsedMilliseconds);

		((ToolStripStatusLabel^)getControl("statusLabel1"))->Text = statusString;
	}
}
void CWStrategy::next()
{
	if (bDealer->StatesCount > 0)
	{
		auto numericValue = ((NumericUpDown^)getControl("numericUpDown1"))->Value;
		auto stateNo = Convert::ToInt32(numericValue) - 1;

		bDealer->setCurrentBoard(stateNo);

		vWords = bDealer->gimmeVWords();
		hWords = bDealer->gimmeHWords();

		vhTextBoxesFill();

		auto boardHeight = bDealer->CurrentHeight;
		auto boardWidth = bDealer->CurrentWidth;

		auto panel = ((Panel^)getControl("panel1"));
		auto easel = panel->CreateGraphics();
		easel->Clear(SystemColors::Info);

		// инициализация класса рисования доски
		auto painter = gcnew PaintDealer(bDealer);

		if (boardHeight * painter->Scale < panel->Height && boardWidth * painter->Scale < panel->Width)
		{
			auto cutWords = ((ToolStripButton^)getControl("bCutWords"))->Checked;

			painter->drawBoard(easel, false, cutWords);
		}
		else
			((Label^)getControl("lOverflow"))->Visible = true;
	}
}
void CWStrategy::preview()
{
	if (bDealer->StatesCount > 0)
	{
		auto stateNo = (int)((NumericUpDown^)getControl("numericUpDown1"))->Value - 1;
		bDealer->setCurrentBoard(stateNo);

		auto cutWords = ((ToolStripButton^)getControl("bCutWords"))->Checked;
		auto painter = gcnew PaintDealer(bDealer);
		painter->preview(cutWords);
	}
	else
		MessageBox::Show("Составьте кроссворд!", "Application");
}
void CWStrategy::about()
{
	MessageBox::Show("©slimHouse\n2019", "about");
}
void CWStrategy::newOne()
{
	this->reset();
	auto field = ((TextBox^)getControl("tbSource"));
	this->clearField();

	auto panel = ((Panel^)getControl("panel1"))->Focus();
}


Object^ CWStrategy::getControl(String^ name)
{
	auto ctrl = mainForm->Controls->Find(name, true);
	if (ctrl->Length)
		return ctrl[0];

	for each (auto item in mainForm->Controls)
	{
		if (item->GetType() == ToolStrip::typeid)
		{
			auto ct = ((ToolStrip^)item)->Items->Find(name, true);
			if (ct->Length)
				return ct[0];
		}
		else if (item->GetType() == StatusStrip::typeid)
		{
			auto ct = ((StatusStrip^)item)->Items->Find(name, true);
			if (ct->Length)
				return ct[0];
		}
	}

	return nullptr;
}
List<String^>^ CWStrategy::splitInput(Array^ arr)
{
	auto list = gcnew List<String^>();
	for each (String ^ item in arr)
	{
		auto split = item->Split(' ');
		for each (auto % one in split)
			if (one->Length > 0)
				list->Add(one);
	}

	return list;
}
void CWStrategy::handleStates()
{
	if (bDealer->StatesCount > 0)
	{
		((ToolStripButton^)getControl("bCutWords"))->Enabled = true;
		((NumericUpDown^)getControl("numericUpDown1"))->Minimum = 1;
		((NumericUpDown^)getControl("numericUpDown1"))->Maximum = bDealer->StatesCount;
		((NumericUpDown^)getControl("numericUpDown1"))->Value = 1;
		((TextBox^)getControl("tbCountStates"))->Text = bDealer->StatesCount.ToString();

		((TabControl^)getControl("tabControl1"))->SelectedIndex = 1;
		next();
	}
}
void CWStrategy::handleFails()
{
	auto tbNotFitted = (TextBox^)getControl("tbNotFitted");

	if (bDealer->FailsCount > 0)
	{
		toolTip->SetToolTip(tbNotFitted, String::Join("\n", bDealer->gimmeFails()));
		tbNotFitted->Text = bDealer->FailsCount.ToString();
		return;
	}

	toolTip->SetToolTip(tbNotFitted, "Нет невошедших слов");
}
void CWStrategy::vhTextBoxesFill()
{
	auto vWordsList = vWords->ToArray();
	auto hWordsList = hWords->ToArray();

	for (int i = 0; i < vWordsList->Length; ++i)
		vWordsList[i] = (i + 1).ToString() + ". " + vWordsList[i];

	for (int i = 0; i < hWordsList->Length; ++i)
		hWordsList[i] = (i + 1).ToString() + ". " + hWordsList[i];


	((TextBox^)getControl("tbVertical"))->Lines = vWordsList;
	((TextBox^)getControl("tbHorizontal"))->Lines = hWordsList;
}