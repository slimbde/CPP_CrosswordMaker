#pragma once
#include "../CWMaker/Classes/Cell.h"
#include "CWStrategy.h"



namespace CliCWMaker
{
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::Diagnostics;


    /// <summary>
    /// Îñíîâíîé êëàññ ïðèëîæåíèÿ
    /// </summary>
    public ref class MainForm : public System::Windows::Forms::Form
    {
        IStrategy^ strategy;    // àáñòðàêòíûé óêàçàòåëü êîìïîíåíòà Strategy èíêàïñóëÿöèÿ ëîãèêè ïðèëîæåíèÿ
        float scale = 20.0f;    // ðàçìåðû êëåòêè


        #pragma region formComponentsDeclaration

        System::ComponentModel::IContainer^ components;
        System::Windows::Forms::ToolStripButton^ bCutWords;
        System::Windows::Forms::Label^ lOverflow;
        System::Windows::Forms::ToolStripButton^ ñïðàâêàToolStripButton;
        System::Drawing::Printing::PrintDocument^ printDocument1;
        System::Windows::Forms::PrintPreviewDialog^ printPreviewDialog1;
        System::Windows::Forms::Label^ label2;
        System::Windows::Forms::TextBox^ tbCountStates;
        System::Windows::Forms::GroupBox^ groupBox1;
        System::Windows::Forms::GroupBox^ groupBox2;
        System::Windows::Forms::TextBox^ tbHorizontal;
        System::Windows::Forms::Label^ label3;
        System::Windows::Forms::TextBox^ tbNotFitted;
        System::Windows::Forms::ToolTip^ toolTip1;
        System::Windows::Forms::StatusStrip^ statusStrip1;
        System::Windows::Forms::ToolStrip^ toolStrip1;
        System::Windows::Forms::ToolStripButton^ ñîçäàòüToolStripButton;
        System::Windows::Forms::ToolStripButton^ îòêðûòüToolStripButton;
        System::Windows::Forms::ToolStripButton^ ñîõðàíèòüToolStripButton;
        System::Windows::Forms::ToolStripButton^ ïå÷àòüToolStripButton;
        System::Windows::Forms::TabControl^ tabControl1;
        System::Windows::Forms::TabPage^ tabPage1;
        System::Windows::Forms::TabPage^ tabPage2;
        System::Windows::Forms::ToolStripStatusLabel^ statusLabel1;
        System::Windows::Forms::Button^ bHandle;
        System::Windows::Forms::Button^ bClear;
        System::Windows::Forms::TextBox^ tbSource;
        System::Windows::Forms::Panel^ panel2;
        System::Windows::Forms::Button^ bReset;
        System::Windows::Forms::Panel^ panel1;
        System::Windows::Forms::Label^ label1;
        System::Windows::Forms::NumericUpDown^ numericUpDown1;
        System::Windows::Forms::TextBox^ tbVertical;
    private: System::Windows::Forms::ToolStripStatusLabel^ toolStripStatusLabel1;
           System::Windows::Forms::Panel^ panel3;

           #pragma endregion

    public:
        virtual ~MainForm()
        {
            if(components)
                delete components;
        }
        MainForm()
        {
            InitializeComponent();
            strategy = gcnew CWStrategy(this, scale);
        }


    /*------------------------------+
        Çàêðûòûå ìåòîäû êëàññà
    +------------------------------*/
    private: void InitializeComponent(void)
    {
        this->components = (gcnew System::ComponentModel::Container());
        System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
        this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
        this->statusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
        this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
        this->ñîçäàòüToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
        this->îòêðûòüToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
        this->ñîõðàíèòüToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
        this->ïå÷àòüToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
        this->bCutWords = (gcnew System::Windows::Forms::ToolStripButton());
        this->ñïðàâêàToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
        this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
        this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
        this->bHandle = (gcnew System::Windows::Forms::Button());
        this->bClear = (gcnew System::Windows::Forms::Button());
        this->tbSource = (gcnew System::Windows::Forms::TextBox());
        this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
        this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
        this->tbHorizontal = (gcnew System::Windows::Forms::TextBox());
        this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
        this->tbVertical = (gcnew System::Windows::Forms::TextBox());
        this->panel3 = (gcnew System::Windows::Forms::Panel());
        this->label3 = (gcnew System::Windows::Forms::Label());
        this->tbNotFitted = (gcnew System::Windows::Forms::TextBox());
        this->tbCountStates = (gcnew System::Windows::Forms::TextBox());
        this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
        this->label2 = (gcnew System::Windows::Forms::Label());
        this->label1 = (gcnew System::Windows::Forms::Label());
        this->panel2 = (gcnew System::Windows::Forms::Panel());
        this->bReset = (gcnew System::Windows::Forms::Button());
        this->panel1 = (gcnew System::Windows::Forms::Panel());
        this->lOverflow = (gcnew System::Windows::Forms::Label());
        this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
        this->printDocument1 = (gcnew System::Drawing::Printing::PrintDocument());
        this->printPreviewDialog1 = (gcnew System::Windows::Forms::PrintPreviewDialog());
        this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
        this->statusStrip1->SuspendLayout();
        this->toolStrip1->SuspendLayout();
        this->tabControl1->SuspendLayout();
        this->tabPage1->SuspendLayout();
        this->tabPage2->SuspendLayout();
        this->groupBox2->SuspendLayout();
        this->groupBox1->SuspendLayout();
        this->panel3->SuspendLayout();
        (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
        this->panel2->SuspendLayout();
        this->panel1->SuspendLayout();
        this->SuspendLayout();
        // 
        // statusStrip1
        // 
        this->statusStrip1->BackColor = System::Drawing::SystemColors::Control;
        this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->statusLabel1, this->toolStripStatusLabel1 });
        this->statusStrip1->Location = System::Drawing::Point(0, 540);
        this->statusStrip1->Name = L"statusStrip1";
        this->statusStrip1->ShowItemToolTips = true;
        this->statusStrip1->Size = System::Drawing::Size(784, 22);
        this->statusStrip1->SizingGrip = false;
        this->statusStrip1->TabIndex = 2;
        this->statusStrip1->Text = L"statusStrip1";
        // 
        // statusLabel1
        // 
        this->statusLabel1->Name = L"statusLabel1";
        this->statusLabel1->Size = System::Drawing::Size(0, 17);
        // 
        // toolStrip1
        // 
        this->toolStrip1->BackColor = System::Drawing::SystemColors::Control;
        this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6)
        {
            this->ñîçäàòüToolStripButton,
                this->îòêðûòüToolStripButton, this->ñîõðàíèòüToolStripButton, this->ïå÷àòüToolStripButton, this->bCutWords, this->ñïðàâêàToolStripButton
        });
        this->toolStrip1->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::HorizontalStackWithOverflow;
        this->toolStrip1->Location = System::Drawing::Point(0, 0);
        this->toolStrip1->Name = L"toolStrip1";
        this->toolStrip1->Padding = System::Windows::Forms::Padding(1);
        this->toolStrip1->Size = System::Drawing::Size(784, 27);
        this->toolStrip1->TabIndex = 4;
        this->toolStrip1->Text = L"toolStrip1";
        // 
        // ñîçäàòüToolStripButton
        // 
        this->ñîçäàòüToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ñîçäàòüToolStripButton.Image")));
        this->ñîçäàòüToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
        this->ñîçäàòüToolStripButton->Name = L"ñîçäàòüToolStripButton";
        this->ñîçäàòüToolStripButton->Size = System::Drawing::Size(70, 22);
        this->ñîçäàòüToolStripButton->Text = L"&Ñîçäàòü";
        this->ñîçäàòüToolStripButton->ToolTipText = L"Ñîçäàòü íîâûé êðîññâîðä";
        this->ñîçäàòüToolStripButton->Click += gcnew System::EventHandler(this, &MainForm::ñîçäàòüToolStripButton_Click);
        // 
        // îòêðûòüToolStripButton
        // 
        this->îòêðûòüToolStripButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
        this->îòêðûòüToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"îòêðûòüToolStripButton.Image")));
        this->îòêðûòüToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
        this->îòêðûòüToolStripButton->Name = L"îòêðûòüToolStripButton";
        this->îòêðûòüToolStripButton->Size = System::Drawing::Size(23, 22);
        this->îòêðûòüToolStripButton->Text = L"&Îòêðûòü";
        this->îòêðûòüToolStripButton->Visible = false;
        // 
        // ñîõðàíèòüToolStripButton
        // 
        this->ñîõðàíèòüToolStripButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
        this->ñîõðàíèòüToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ñîõðàíèòüToolStripButton.Image")));
        this->ñîõðàíèòüToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
        this->ñîõðàíèòüToolStripButton->Name = L"ñîõðàíèòüToolStripButton";
        this->ñîõðàíèòüToolStripButton->Size = System::Drawing::Size(23, 22);
        this->ñîõðàíèòüToolStripButton->Text = L"&Ñîõðàíèòü";
        this->ñîõðàíèòüToolStripButton->Visible = false;
        // 
        // ïå÷àòüToolStripButton
        // 
        this->ïå÷àòüToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ïå÷àòüToolStripButton.Image")));
        this->ïå÷àòüToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
        this->ïå÷àòüToolStripButton->Name = L"ïå÷àòüToolStripButton";
        this->ïå÷àòüToolStripButton->Size = System::Drawing::Size(110, 22);
        this->ïå÷àòüToolStripButton->Text = L"&Ïðåäïðîñìîòð";
        this->ïå÷àòüToolStripButton->ToolTipText = L"Ïðåäïðîñìîòð è ïå÷àòü";
        this->ïå÷àòüToolStripButton->Click += gcnew System::EventHandler(this, &MainForm::ïå÷àòüToolStripButton_Click);
        // 
        // bCutWords
        // 
        this->bCutWords->BackColor = System::Drawing::SystemColors::Control;
        this->bCutWords->CheckOnClick = true;
        this->bCutWords->Enabled = false;
        this->bCutWords->Font = (gcnew System::Drawing::Font(L"Calibri", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                                             static_cast<System::Byte>(204)));
        this->bCutWords->ForeColor = System::Drawing::SystemColors::HotTrack;
        this->bCutWords->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"bCutWords.Image")));
        this->bCutWords->ImageTransparentColor = System::Drawing::Color::Magenta;
        this->bCutWords->Name = L"bCutWords";
        this->bCutWords->Size = System::Drawing::Size(133, 22);
        this->bCutWords->Text = L"ÒÎËÜÊÎ ÊÀÐÊÀÑ";
        this->bCutWords->ToolTipText = L"Óáðàòü ñëîâà èç ñåòêè êðîññâîðäà";
        this->bCutWords->Click += gcnew System::EventHandler(this, &MainForm::bCutWords_Click);
        // 
        // ñïðàâêàToolStripButton
        // 
        this->ñïðàâêàToolStripButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
        this->ñïðàâêàToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ñïðàâêàToolStripButton.Image")));
        this->ñïðàâêàToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
        this->ñïðàâêàToolStripButton->Name = L"ñïðàâêàToolStripButton";
        this->ñïðàâêàToolStripButton->Size = System::Drawing::Size(23, 22);
        this->ñïðàâêàToolStripButton->Text = L"Ñïð&àâêà";
        this->ñïðàâêàToolStripButton->ToolTipText = L"Ïðîñìîòðåòü ñïðàâêó";
        this->ñïðàâêàToolStripButton->Click += gcnew System::EventHandler(this, &MainForm::ñïðàâêàToolStripButton_Click);
        // 
        // tabControl1
        // 
        this->tabControl1->Appearance = System::Windows::Forms::TabAppearance::Buttons;
        this->tabControl1->Controls->Add(this->tabPage1);
        this->tabControl1->Controls->Add(this->tabPage2);
        this->tabControl1->Dock = System::Windows::Forms::DockStyle::Right;
        this->tabControl1->Location = System::Drawing::Point(573, 27);
        this->tabControl1->Name = L"tabControl1";
        this->tabControl1->Padding = System::Drawing::Point(0, 0);
        this->tabControl1->SelectedIndex = 0;
        this->tabControl1->Size = System::Drawing::Size(211, 513);
        this->tabControl1->TabIndex = 5;
        // 
        // tabPage1
        // 
        this->tabPage1->BackColor = System::Drawing::SystemColors::Control;
        this->tabPage1->Controls->Add(this->bHandle);
        this->tabPage1->Controls->Add(this->bClear);
        this->tabPage1->Controls->Add(this->tbSource);
        this->tabPage1->Location = System::Drawing::Point(4, 25);
        this->tabPage1->Name = L"tabPage1";
        this->tabPage1->Size = System::Drawing::Size(203, 484);
        this->tabPage1->TabIndex = 0;
        this->tabPage1->Text = L"Ââîä";
        // 
        // bHandle
        // 
        this->bHandle->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
        this->bHandle->AutoSize = true;
        this->bHandle->DialogResult = System::Windows::Forms::DialogResult::OK;
        this->bHandle->FlatStyle = System::Windows::Forms::FlatStyle::System;
        this->bHandle->Location = System::Drawing::Point(98, 452);
        this->bHandle->Name = L"bHandle";
        this->bHandle->Padding = System::Windows::Forms::Padding(5);
        this->bHandle->Size = System::Drawing::Size(90, 33);
        this->bHandle->TabIndex = 1;
        this->bHandle->Text = L"ÑÎÁÐÀÒÜ >";
        this->bHandle->UseVisualStyleBackColor = true;
        this->bHandle->Click += gcnew System::EventHandler(this, &MainForm::bHandle_Click);
        // 
        // bClear
        // 
        this->bClear->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
        this->bClear->AutoSize = true;
        this->bClear->FlatStyle = System::Windows::Forms::FlatStyle::System;
        this->bClear->Location = System::Drawing::Point(0, 452);
        this->bClear->Name = L"bClear";
        this->bClear->Padding = System::Windows::Forms::Padding(5);
        this->bClear->Size = System::Drawing::Size(91, 33);
        this->bClear->TabIndex = 1;
        this->bClear->Text = L"Î×ÈÑÒÈÒÜ";
        this->bClear->UseVisualStyleBackColor = true;
        this->bClear->Click += gcnew System::EventHandler(this, &MainForm::bClear_Click);
        // 
        // tbSource
        // 
        this->tbSource->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
        this->tbSource->Dock = System::Windows::Forms::DockStyle::Top;
        this->tbSource->Font = (gcnew System::Drawing::Font(L"Calibri", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                                            static_cast<System::Byte>(204)));
        this->tbSource->ForeColor = System::Drawing::SystemColors::ButtonShadow;
        this->tbSource->Location = System::Drawing::Point(0, 0);
        this->tbSource->Multiline = true;
        this->tbSource->Name = L"tbSource";
        this->tbSource->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
        this->tbSource->Size = System::Drawing::Size(203, 447);
        this->tbSource->TabIndex = 0;
        this->tbSource->Text = L"Ââåäèòå ñëîâà\r\n÷åðåç ïðîáåë\r\nèëè ñ íîâûõ ñòðîê";
        this->tbSource->Enter += gcnew System::EventHandler(this, &MainForm::tbSource_Enter);
        this->tbSource->Leave += gcnew System::EventHandler(this, &MainForm::tbSource_Leave);
        // 
        // tabPage2
        // 
        this->tabPage2->BackColor = System::Drawing::SystemColors::Control;
        this->tabPage2->Controls->Add(this->groupBox2);
        this->tabPage2->Controls->Add(this->groupBox1);
        this->tabPage2->Controls->Add(this->panel3);
        this->tabPage2->Controls->Add(this->panel2);
        this->tabPage2->Location = System::Drawing::Point(4, 25);
        this->tabPage2->Name = L"tabPage2";
        this->tabPage2->Size = System::Drawing::Size(203, 484);
        this->tabPage2->TabIndex = 1;
        this->tabPage2->Text = L"Ðåçóëüòàò";
        // 
        // groupBox2
        // 
        this->groupBox2->Controls->Add(this->tbHorizontal);
        this->groupBox2->Dock = System::Windows::Forms::DockStyle::Bottom;
        this->groupBox2->Location = System::Drawing::Point(0, 254);
        this->groupBox2->Name = L"groupBox2";
        this->groupBox2->Size = System::Drawing::Size(203, 193);
        this->groupBox2->TabIndex = 6;
        this->groupBox2->TabStop = false;
        this->groupBox2->Text = L"Ñëîâà ïî ãîðèçîíòàëè:";
        // 
        // tbHorizontal
        // 
        this->tbHorizontal->BackColor = System::Drawing::SystemColors::ButtonHighlight;
        this->tbHorizontal->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
        this->tbHorizontal->Dock = System::Windows::Forms::DockStyle::Fill;
        this->tbHorizontal->Location = System::Drawing::Point(3, 16);
        this->tbHorizontal->Multiline = true;
        this->tbHorizontal->Name = L"tbHorizontal";
        this->tbHorizontal->ReadOnly = true;
        this->tbHorizontal->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
        this->tbHorizontal->Size = System::Drawing::Size(197, 174);
        this->tbHorizontal->TabIndex = 0;
        // 
        // groupBox1
        // 
        this->groupBox1->Controls->Add(this->tbVertical);
        this->groupBox1->Dock = System::Windows::Forms::DockStyle::Top;
        this->groupBox1->Location = System::Drawing::Point(0, 62);
        this->groupBox1->Name = L"groupBox1";
        this->groupBox1->Size = System::Drawing::Size(203, 192);
        this->groupBox1->TabIndex = 5;
        this->groupBox1->TabStop = false;
        this->groupBox1->Text = L"Ñëîâà ïî âåðòèêàëè:";
        // 
        // tbVertical
        // 
        this->tbVertical->BackColor = System::Drawing::SystemColors::ButtonHighlight;
        this->tbVertical->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
        this->tbVertical->Dock = System::Windows::Forms::DockStyle::Fill;
        this->tbVertical->Location = System::Drawing::Point(3, 16);
        this->tbVertical->Multiline = true;
        this->tbVertical->Name = L"tbVertical";
        this->tbVertical->ReadOnly = true;
        this->tbVertical->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
        this->tbVertical->Size = System::Drawing::Size(197, 173);
        this->tbVertical->TabIndex = 4;
        // 
        // panel3
        // 
        this->panel3->BackColor = System::Drawing::SystemColors::Control;
        this->panel3->Controls->Add(this->label3);
        this->panel3->Controls->Add(this->tbNotFitted);
        this->panel3->Controls->Add(this->tbCountStates);
        this->panel3->Controls->Add(this->numericUpDown1);
        this->panel3->Controls->Add(this->label2);
        this->panel3->Controls->Add(this->label1);
        this->panel3->Dock = System::Windows::Forms::DockStyle::Top;
        this->panel3->Location = System::Drawing::Point(0, 0);
        this->panel3->Name = L"panel3";
        this->panel3->Size = System::Drawing::Size(203, 62);
        this->panel3->TabIndex = 3;
        // 
        // label3
        // 
        this->label3->AutoSize = true;
        this->label3->Location = System::Drawing::Point(42, 37);
        this->label3->Name = L"label3";
        this->label3->Size = System::Drawing::Size(106, 13);
        this->label3->TabIndex = 4;
        this->label3->Text = L"Íåâîøåäøèå ñëîâà";
        // 
        // tbNotFitted
        // 
        this->tbNotFitted->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
        this->tbNotFitted->Cursor = System::Windows::Forms::Cursors::Hand;
        this->tbNotFitted->Location = System::Drawing::Point(150, 35);
        this->tbNotFitted->Name = L"tbNotFitted";
        this->tbNotFitted->ReadOnly = true;
        this->tbNotFitted->Size = System::Drawing::Size(35, 20);
        this->tbNotFitted->TabIndex = 3;
        this->tbNotFitted->Text = L"0";
        this->toolTip1->SetToolTip(this->tbNotFitted, L"Íåò íåâîøåäøèõ ñëîâ");
        // 
        // tbCountStates
        // 
        this->tbCountStates->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
        this->tbCountStates->Location = System::Drawing::Point(150, 4);
        this->tbCountStates->Name = L"tbCountStates";
        this->tbCountStates->ReadOnly = true;
        this->tbCountStates->Size = System::Drawing::Size(35, 20);
        this->tbCountStates->TabIndex = 3;
        this->tbCountStates->Text = L"0";
        // 
        // numericUpDown1
        // 
        this->numericUpDown1->Location = System::Drawing::Point(57, 4);
        this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 0, 0, 0, 0 });
        this->numericUpDown1->Name = L"numericUpDown1";
        this->numericUpDown1->Size = System::Drawing::Size(46, 20);
        this->numericUpDown1->TabIndex = 1;
        this->numericUpDown1->ValueChanged += gcnew System::EventHandler(this, &MainForm::numericUpDown1_ValueChanged);
        // 
        // label2
        // 
        this->label2->AutoSize = true;
        this->label2->Location = System::Drawing::Point(110, 6);
        this->label2->Name = L"label2";
        this->label2->Size = System::Drawing::Size(37, 13);
        this->label2->TabIndex = 2;
        this->label2->Text = L"Âñåãî";
        // 
        // label1
        // 
        this->label1->AutoSize = true;
        this->label1->Location = System::Drawing::Point(5, 6);
        this->label1->Name = L"label1";
        this->label1->Size = System::Drawing::Size(49, 13);
        this->label1->TabIndex = 2;
        this->label1->Text = L"Âàðèàíò";
        // 
        // panel2
        // 
        this->panel2->BackColor = System::Drawing::SystemColors::Control;
        this->panel2->Controls->Add(this->bReset);
        this->panel2->Dock = System::Windows::Forms::DockStyle::Bottom;
        this->panel2->Location = System::Drawing::Point(0, 447);
        this->panel2->Name = L"panel2";
        this->panel2->Size = System::Drawing::Size(203, 37);
        this->panel2->TabIndex = 0;
        // 
        // bReset
        // 
        this->bReset->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
        this->bReset->AutoSize = true;
        this->bReset->FlatStyle = System::Windows::Forms::FlatStyle::System;
        this->bReset->Location = System::Drawing::Point(3, 4);
        this->bReset->Name = L"bReset";
        this->bReset->Padding = System::Windows::Forms::Padding(5);
        this->bReset->Size = System::Drawing::Size(98, 33);
        this->bReset->TabIndex = 2;
        this->bReset->Text = L"< ÑÁÐÎÑÈÒÜ";
        this->bReset->UseVisualStyleBackColor = true;
        this->bReset->Click += gcnew System::EventHandler(this, &MainForm::bReset_Click);
        // 
        // panel1
        // 
        this->panel1->AutoScroll = true;
        this->panel1->BackColor = System::Drawing::SystemColors::Info;
        this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
        this->panel1->Controls->Add(this->lOverflow);
        this->panel1->Dock = System::Windows::Forms::DockStyle::Top;
        this->panel1->Location = System::Drawing::Point(0, 27);
        this->panel1->Name = L"panel1";
        this->panel1->Size = System::Drawing::Size(573, 509);
        this->panel1->TabIndex = 6;
        this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::panel1_Paint);
        // 
        // lOverflow
        // 
        this->lOverflow->AutoSize = true;
        this->lOverflow->Font = (gcnew System::Drawing::Font(L"Calibri Light", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                                             static_cast<System::Byte>(204)));
        this->lOverflow->ForeColor = System::Drawing::Color::IndianRed;
        this->lOverflow->Location = System::Drawing::Point(144, 9);
        this->lOverflow->Name = L"lOverflow";
        this->lOverflow->Size = System::Drawing::Size(414, 38);
        this->lOverflow->TabIndex = 0;
        this->lOverflow->Text = L"Ñîñòàâëåííûé êðîññâîðä íå âìåùàåòñÿ â ðàáî÷óþ îáëàñòü.\r\nÂîñïîëüçóéòåñü ïðåäïðîñìî"
            L"òðîì.";
        this->lOverflow->TextAlign = System::Drawing::ContentAlignment::TopRight;
        this->lOverflow->Visible = false;
        // 
        // printDocument1
        // 
        this->printDocument1->PrintPage += gcnew System::Drawing::Printing::PrintPageEventHandler(this, &MainForm::printDocument1_PrintPage);
        // 
        // printPreviewDialog1
        // 
        this->printPreviewDialog1->AutoScrollMargin = System::Drawing::Size(0, 0);
        this->printPreviewDialog1->AutoScrollMinSize = System::Drawing::Size(0, 0);
        this->printPreviewDialog1->ClientSize = System::Drawing::Size(400, 300);
        this->printPreviewDialog1->Document = this->printDocument1;
        this->printPreviewDialog1->Enabled = true;
        this->printPreviewDialog1->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"printPreviewDialog1.Icon")));
        this->printPreviewDialog1->Name = L"printPreviewDialog1";
        this->printPreviewDialog1->Visible = false;
        // 
        // toolStripStatusLabel1
        // 
        this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
        this->toolStripStatusLabel1->Size = System::Drawing::Size(118, 17);
        this->toolStripStatusLabel1->Text = L"toolStripStatusLabel1";
        // 
        // MainForm
        // 
        this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
        this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
        this->ClientSize = System::Drawing::Size(784, 562);
        this->Controls->Add(this->panel1);
        this->Controls->Add(this->tabControl1);
        this->Controls->Add(this->toolStrip1);
        this->Controls->Add(this->statusStrip1);
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
        this->MaximizeBox = false;
        this->Name = L"MainForm";
        this->Text = L"CrossWRD 1.0";
        this->statusStrip1->ResumeLayout(false);
        this->statusStrip1->PerformLayout();
        this->toolStrip1->ResumeLayout(false);
        this->toolStrip1->PerformLayout();
        this->tabControl1->ResumeLayout(false);
        this->tabPage1->ResumeLayout(false);
        this->tabPage1->PerformLayout();
        this->tabPage2->ResumeLayout(false);
        this->groupBox2->ResumeLayout(false);
        this->groupBox2->PerformLayout();
        this->groupBox1->ResumeLayout(false);
        this->groupBox1->PerformLayout();
        this->panel3->ResumeLayout(false);
        this->panel3->PerformLayout();
        (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
        this->panel2->ResumeLayout(false);
        this->panel2->PerformLayout();
        this->panel1->ResumeLayout(false);
        this->panel1->PerformLayout();
        this->ResumeLayout(false);
        this->PerformLayout();

    }



    /*--------------------------+
        Ñîáûòèÿ
    +--------------------------*/
    private: System::Void tbSource_Enter(System::Object^ sender, System::EventArgs^ e)
    {
        strategy->inputFieldEnter(tbSource);
    }
    private: System::Void tbSource_Leave(System::Object^ sender, System::EventArgs^ e)
    {
        strategy->inputFieldLeave(tbSource);
    }

    private: System::Void bClear_Click(System::Object^ sender, System::EventArgs^ e)
    {
        strategy->clearField(tbSource);
    }
    private: System::Void bReset_Click(System::Object^ sender, System::EventArgs^ e)
    {
        strategy->reset();
    }
    private: System::Void bHandle_Click(System::Object^ sender, System::EventArgs^ e)
    {
        strategy->handle();
    }
    private: System::Void bCutWords_Click(System::Object^ sender, System::EventArgs^ e)
    {
        numericUpDown1_ValueChanged(this, EventArgs::Empty);
    }

    private: System::Void numericUpDown1_ValueChanged(System::Object^ sender, System::EventArgs^ e)
    {
        strategy->next();
    }
    private: System::Void ïå÷àòüToolStripButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if(strategy->gimmeStatesCount() > 0)
        {
            strategy->setCurrentState(Convert::ToInt32(numericUpDown1->Value) - 1);

            auto wMargin = scale;
            auto hMargin = scale;

            auto hWords = strategy->gimmeHWords();
            auto vWords = strategy->gimmeVWords();

            // èùåì äëèííåéøåå ãîðèçîíòàëüíîå ñëîâî
            int maxLength = 0;
            for each(auto item in hWords)
                maxLength = maxLength > item->Length ? maxLength : item->Length;

            auto paperWidth = int(strategy->gimmeBoardWidth() * scale + wMargin * 2 + 1 / hWords->Count * scale * 7 + maxLength * scale);
            auto paperHeight = int(strategy->gimmeBoardHeight() * scale + hMargin * 2 + 1 / vWords->Count * scale * 4);
            printDocument1->DefaultPageSettings->PaperSize = gcnew Printing::PaperSize("MySize", paperWidth, paperHeight);
            printDocument1->OriginAtMargins = true;
            printDocument1->DefaultPageSettings->Margins = gcnew Printing::Margins((int)wMargin, (int)wMargin, (int)hMargin, (int)hMargin);

            printPreviewDialog1->StartPosition = FormStartPosition::CenterParent;
            printPreviewDialog1->WindowState = System::Windows::Forms::FormWindowState::Maximized;
            printPreviewDialog1->ShowDialog();
        }
        else
            MessageBox::Show("Ñîñòàâüòå êðîññâîðä!", "Application");
    }
    private: System::Void printDocument1_PrintPage(System::Object^ sender, System::Drawing::Printing::PrintPageEventArgs^ e)
    {
        auto easel = e->Graphics;
        strategy->drawBoard(scale, easel, true, bCutWords->Checked);
        strategy->drawWords(scale, easel);
    }
    private: System::Void ñïðàâêàToolStripButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        MessageBox::Show("©slimHouse\n2019", "about");
    }
    private: System::Void ñîçäàòüToolStripButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        bReset_Click(this, EventArgs::Empty);
        bClear_Click(this, EventArgs::Empty);
        panel1->Focus();
    }

    private: System::Void panel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
    {
        numericUpDown1_ValueChanged(this, EventArgs::Empty);
    }
    };
}