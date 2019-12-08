#pragma once


namespace test
{
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    /// <summary>
    /// —водка дл€ MyForm
    /// </summary>
    public ref class MyForm : public System::Windows::Forms::Form
    {

        /////////////////////////////////
        delegate String^ aDelegate();////
        /////////////////////////////////

    public:
        MyForm(void)
        {
            InitializeComponent();

            // SOLUTION MF!!!!
            /////////////////////////////////////////////////////////////////////////
            Action^ act = gcnew Action(this, &MyForm::method);///////////////////////
            AsyncCallback^ as = gcnew AsyncCallback(this, &MyForm::callback);////////
            act->BeginInvoke(as, this);//////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////
        }

    protected:
        /// <summary>
        /// ќсвободить все используемые ресурсы.
        /// </summary>
        ~MyForm()
        {
            if(components)
            {
                delete components;
            }
        }

    private:
        /// <summary>
        /// ќб€зательна€ переменна€ конструктора.
        /// </summary>
        System::ComponentModel::Container^ components;

        #pragma region Windows Form Designer generated code
                /// <summary>
                /// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
                /// содержимое этого метода с помощью редактора кода.
                /// </summary>
        void InitializeComponent(void)
        {
            this->components = gcnew System::ComponentModel::Container();
            this->Size = System::Drawing::Size(300, 300);
            this->Text = L"MyForm";
            this->Padding = System::Windows::Forms::Padding(0);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
        }
        #pragma endregion

    private: void method()
    {
        Console::WriteLine("Method has run\n");
    }
    private: void callback(IAsyncResult^ result)
    {
        Console::WriteLine("callback has run\n\n");
    }
    };
}
