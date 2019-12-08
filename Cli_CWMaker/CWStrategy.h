#pragma once
#include "IStrategy.h"
#include "../CWMaker/Classes/Board.h"
#include "../CWMaker/Classes/CompareByLength.h"

// ��������� ���������� ����������� ����� ���������� ����������
#define ADVANCED

using namespace System::Windows::Forms;
using namespace System::Diagnostics;


ref class CWStrategy : IStrategy
{
    Generic::Stack<Board^ >^ states;		// ���� ���������
    Generic::Stack<String^ >^ failedWords;	// ���� ��� �� ����������� ����
    Stopwatch^ watch;                       // �������� ��������� ������������������
    Board^ currentState;                    // ������� �������������� ���������
    List<String^>^ vWords;                  // ����� �� ��������� �������� ���������
    List<String^>^ hWords;                  // ����� �� ����������� �������� ���������
    Form^ mainForm;
    float scale;


public:
    CWStrategy(Form^% mainForm, float scale);

    // ������������ ����� IStrategy
    virtual void reset();
    virtual void inputFieldEnter(Control^ input);
    virtual void inputFieldLeave(Control^ input);
    virtual void clearField(Control^ field);
    virtual void handle();
    virtual void next();


private:
    // ��������������� ������
    Object^ getControl(String^ name);
    List<String^>^ splitInput(Array^ arr);
    void handleStates();
    void handleFails();
    void setCurrentState(int stateNo);
    List<String^>^ gimmeVWords();
    List<String^>^ gimmeHWords();
    void vhTextBoxesFill();
    void drawBoard(Graphics^% easel, bool resetZeroPoint, bool cutWords);
    void drawWords(Graphics^% easel);


     // ����������� ������
    void compose(List<String^>^ words);
    void callback(IAsyncResult^ result);
    void handlingResults();
};




inline Object^ CWStrategy::getControl(String^ name)
{
    auto ctrl = mainForm->Controls->Find(name, true);
    if(ctrl->Length)
        return ctrl[0];

    for each(auto item in mainForm->Controls)
    {
        if(item->GetType() == ToolStrip::typeid)
        {
            auto ct = ((ToolStrip^)item)->Items->Find(name, true);
            if(ct->Length)
                return ct[0];
        }
        else if(item->GetType() == StatusStrip::typeid)
        {
            auto ct = ((StatusStrip^)item)->Items->Find(name, true);
            if(ct->Length)
                return ct[0];
        }
    }

    return nullptr;
}
inline List<String^>^ CWStrategy::splitInput(Array^ arr)
{
    auto list = gcnew List<String^>();
    for each(String ^ item in arr)
    {
        auto split = item->Split(' ');
        for each(auto % one in split)
            if(one->Length > 0)
                list->Add(one);
    }

    return list;
}
inline void CWStrategy::handleStates()
{
    if(states->Count)
    {
        ((ToolStripButton^)getControl("bCutWords"))->Enabled = true;
        ((NumericUpDown^)getControl("numericUpDown1"))->Minimum = 1;
        ((NumericUpDown^)getControl("numericUpDown1"))->Maximum = states->Count;
        ((NumericUpDown^)getControl("numericUpDown1"))->Value = 1;
        ((TextBox^)getControl("tbCountStates"))->Text = states->Count.ToString();

        ((TabControl^)getControl("tabControl1"))->SelectedIndex = 1;
        next();
    }
}
inline void CWStrategy::handleFails()
{
    if(failedWords->Count)
    {
        auto tbNotFitted = (TextBox^)getControl("tbNotFitted");
        auto toolTip = gcnew System::Windows::Forms::ToolTip();
        toolTip->SetToolTip(tbNotFitted, String::Join("\n", failedWords->ToArray()));

        tbNotFitted->Text = failedWords->Count.ToString();
    }
}
inline void CWStrategy::compose(List<String^>^ words)
{
    Console::WriteLine("\nStarted handling words at " + DateTime::Now);

    // ��������� �� ����� �����
    words->Sort(gcnew CompareByLength());

    auto wrds = gcnew Generic::Stack<String^>(words);

    // ������� ��������� ���� ��� ����������� ��������� � ������ �������
    Generic::Stack<Board^ >^ reserve;

    // ������� ���� ������� � ����� ������� �����
    states->Push(gcnew Board(wrds->Peek()->Length, 1));

    // ���� � ����� ���� ���� �����
    while(wrds->Count)
    {
        // �������� ���� ���� ��������� � �����
        do
        {
            // ������� �� ����� ��������� ���������
            Board^ lastState = states->Pop();

            // ��������� ���� ��� �������� ����������� ���������� ������ �����
            Generic::Stack<Board^ >^ results = gcnew Generic::Stack<Board^ >();

            // ������� ���� ����������� ���������� ����� � ����� ���������
            // �������� �� ������� ����� � ����� ���� ��� �� ������
            results = lastState->Alter(wrds->Peek());

            // ���� ���������� � ��������� �� ������
            if(results->Count != 0)
            {
                // ������ ����� �� ����� ����
                wrds->Pop();
                // � ���� � ����� �� ����������� ���� ���-�� ����, �������
                // ����� ����������� ��� ��� ��������
                if(failedWords->Count)
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
        while(states->Count);

        // ���� �� �������� ���������
        if(!states->Count)
        {
            // �� ���� ���� ��� �� ����
            if(wrds->Count)
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
inline void CWStrategy::callback(IAsyncResult^ result)
{
    auto act = gcnew Action(this, &CWStrategy::handlingResults);
    act->Invoke();
}
inline void CWStrategy::handlingResults()
{
    handleStates();
    handleFails();

    auto stLabel = ((ToolStripStatusLabel^)getControl("statusLabel1"));
    stLabel->Text += String::Format(", ������ �������� �����: {0} ms", watch->ElapsedMilliseconds);
    watch->Stop();
}
inline void CWStrategy::setCurrentState(int stateNo)
{
    currentState = states->ToArray()[stateNo];
}
inline List<String^>^ CWStrategy::gimmeVWords()
{
    auto result = gcnew List<String^>();
    auto words = currentState->GetWords();

    for each(auto % item in words)
    {
        if(item->lyt == "Vertical")
            result->Add(item->word);
    }

    return result;
}
inline List<String^>^ CWStrategy::gimmeHWords()
{
    auto result = gcnew List<String^>();
    auto words = currentState->GetWords();

    for each(auto % item in words)
    {
        if(item->lyt == "Horizontal")
            result->Add(item->word);
    }

    return result;
}
inline void CWStrategy::vhTextBoxesFill()
{
    auto vWordsList = vWords->ToArray();
    auto hWordsList = hWords->ToArray();

    for(int i = 0; i < vWordsList->Length; ++i)
        vWordsList[i] = (i + 1).ToString() + ". " + vWordsList[i];

    for(int i = 0; i < hWordsList->Length; ++i)
        hWordsList[i] = (i + 1).ToString() + ". " + hWordsList[i];


    ((TextBox^)getControl("tbVertical"))->Lines = vWordsList;
    ((TextBox^)getControl("tbHorizontal"))->Lines = hWordsList;
}
inline void CWStrategy::drawBoard(Graphics^% easel, bool resetZeroPoint, bool cutWords)
{
    auto easelWidth = easel->VisibleClipBounds.Width;
    auto easelHeight = easel->VisibleClipBounds.Height;

    auto zeroTop = easelHeight / 2.5f;
    auto zeroLeft = easelWidth / 2;

    if(resetZeroPoint)
    {
        zeroTop = 0.0f;
        zeroLeft = 0.0f;
    }

    // ���������� ������ ����
    int nVertical = 1;
    int nHorizontal = 1;

    auto words = currentState->GetWords();
    for each(auto item in words)
    {
        for(int i = 0; i < item->length; ++i)
        {
            Cell^ cell;

            float currentVerticalLeft = zeroLeft + item->left * scale;
            float currentVertiaclTop = zeroTop + item->top * scale + i * scale;
            float currentHorizontalLeft = zeroLeft + item->left * scale + i * scale;
            float currentHorizontalTop = zeroTop + item->top * scale;

            if(item->lyt == "Horizontal")
                cell = gcnew Cell(currentHorizontalLeft,
                                  currentHorizontalTop,
                                  scale,
                                  cutWords ? " " : item[i]->ToUpper(),
                                  i == 0 ? (nHorizontal++).ToString() : "",
                                  false);
            else
                cell = gcnew Cell(currentVerticalLeft,
                                  currentVertiaclTop,
                                  scale,
                                  cutWords ?
                                  " " : item[i]->ToUpper(),
                                  i == 0 ? (nVertical++).ToString() : "",
                                  true);

            cell->draw(easel);
        }
    }
}
inline void CWStrategy::drawWords(Graphics^% easel)
{
    float top = scale;
    float left = currentState->Width * scale + scale * 2;

    easel->DrawString("�� �����������:", gcnew Drawing::Font("Calibri", scale / 2, FontStyle::Bold), Brushes::Black, left, top);
    top += scale * 0.75f;

    for(auto i = 0; i < hWords->Count; ++i)
    {
        easel->DrawString(i + 1 + ". " + hWords[i], gcnew Drawing::Font("Calibri", scale / 2), Brushes::Black, left, top);
        top += scale * 0.6f;
    }

    top += scale * 0.75f;
    easel->DrawString("�� ���������:", gcnew Drawing::Font("Calibri", scale / 2, FontStyle::Bold), Brushes::Black, left, top);
    top += scale * 0.75f;

    for(auto i = 0; i < vWords->Count; ++i)
    {
        easel->DrawString(i + 1 + ". " + vWords[i], gcnew Drawing::Font("Calibri", scale / 2), Brushes::Black, left, top);
        top += scale * 0.6f;
    }

    easel->DrawString("�slimHouse 2019", gcnew Drawing::Font("Calibri", scale / 2), Brushes::LightGray, -scale, -scale);
}



inline CWStrategy::CWStrategy(Form^% mainForm, float scale)
{
    this->mainForm = mainForm;
    this->scale = scale;
    states = gcnew Generic::Stack<Board^>();
    failedWords = gcnew Generic::Stack<String^>();
}

inline void CWStrategy::reset()
{
    states->Clear();

    // ������������ ��������� ����������� �����
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

    auto tbNotFitted = (TextBox^)getControl("tbNotFitted");
    auto toolTip = gcnew System::Windows::Forms::ToolTip();
    toolTip->SetToolTip(tbNotFitted, "��� ���������� ����");

    auto easel = ((Panel^)getControl("panel1"))->CreateGraphics();
    easel->Clear(SystemColors::Info);
}
inline void CWStrategy::inputFieldEnter(Control^ input)
{
    if(input->GetType() == TextBox::typeid)
    {
        auto tb = (TextBox^)input;
        if(tb->Lines->Length && tb->Lines[0] == "������� �����")
        {
            tb->Lines = nullptr;
            tb->ForeColor = Color::Black;
        }
    }
}
inline void CWStrategy::inputFieldLeave(Control^ input)
{
    if(input->GetType() == TextBox::typeid)
    {
        auto tb = (TextBox^)input;
        if(!tb->Lines->Length)
        {
            tb->ForeColor = SystemColors::ButtonShadow;
            tb->Lines = gcnew array<String^>{ "������� �����", "����� ������", "��� � ����� �����" };
        }
    }
}
inline void CWStrategy::clearField(Control^ field)
{
    if(field->GetType() == TextBox::typeid)
    {
        auto tb = (TextBox^)field;
        tb->ForeColor = SystemColors::ButtonShadow;
        tb->Lines = gcnew array<String^>{ "������� �����", "����� ������", "��� � ����� �����" };
    }
}
inline void CWStrategy::handle()
{
    ((Label^)getControl("lOverflow"))->Visible = false;

    auto input = ((TextBox^)getControl("tbSource"))->Lines;
    auto inputList = splitInput(input);

    if(inputList->Count < 2 || input->Length && input[0] == "������� �����")
        MessageBox::Show(mainForm, "������� ���� �� ��� �����!");
    else
    {
        watch = Stopwatch::StartNew();
        String^ statusString;

        #ifdef ADVANCED
        // ������ ����������� ���������� ����������
        auto transcend = gcnew Action<List<String^>^>(this, &CWStrategy::compose);
        auto callBk = gcnew AsyncCallback(this, &CWStrategy::callback);
        transcend->BeginInvoke(inputList, callBk, this);
        statusString = String::Format("������������� >> ����� ������ ��������� �����: {0} ms", watch->ElapsedMilliseconds);
        #else
        // ������ ����������� ���������� ���������
        compose(inputList);
        handleStates();
        handleFails();
        watch->Stop();
        statusString = String::Format("������ �������� �� {0} ms", watch->ElapsedMilliseconds);
        #endif // ADVANCED

        ((Label^)getControl("statusLabel1"))->Text = statusString;
    }
}
inline void CWStrategy::next()
{
    if(states->Count)
    {
        auto numericValue = ((NumericUpDown^)getControl("numericUpDown1"))->Value;
        auto stateNo = Convert::ToInt32(numericValue) - 1;
        setCurrentState(stateNo);

        vWords = gimmeVWords();
        hWords = gimmeHWords();

        vhTextBoxesFill();

        auto boardHeight = currentState->Height;
        auto boardWidth = currentState->Width;

        auto panel = ((Panel^)getControl("panel1"));
        if(boardHeight * scale < panel->Height && boardWidth * scale < panel->Width)
        {
            auto easel = panel->CreateGraphics();
            easel->Clear(SystemColors::Info);
            auto cutWords = ((ToolStripButton^)getControl("bCutWords"))->Checked;

            drawBoard(easel, false, cutWords);
        }
        else
            ((Label^)getControl("lOverflow"))->Visible = true;
    }
}

