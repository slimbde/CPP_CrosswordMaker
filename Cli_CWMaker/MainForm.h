#pragma once
#include "BoardDealer.h"

namespace CliCWMaker
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Windows::Forms;
	using namespace System::Diagnostics;
	using namespace System::IO;


	public ref class MainForm : public Form
	{
		delegate int intListDelegate(List<String^>^);

		BoardDealer^ bDealer;		// ñîñòàâèòåëü ñëîâ
		Stopwatch^ watch;			// ÷àñû äëÿ çàìåðà ïðîèçâîäèòåëüíîñòè
		ToolTip^ toolTip;           // ýêçåìïëÿð ïîäñêàçêè

#pragma region formComponentsDeclaration

		System::ComponentModel::IContainer^ components;
		System::Windows::Forms::ToolStripButton^ bCutWords;
		System::Windows::Forms::ToolStripButton^ ñïðàâêàToolStripButton;
		System::Windows::Forms::Label^ label2;
		System::Windows::Forms::TextBox^ tbCountStates;
		System::Windows::Forms::GroupBox^ groupBox1;
		System::Windows::Forms::GroupBox^ groupBox2;
		System::Windows::Forms::TextBox^ tbHorizontal;
		System::Windows::Forms::Label^ label3;
		System::Windows::Forms::TextBox^ tbNotFitted;
		System::Windows::Forms::StatusStrip^ statusStrip1;
		System::Windows::Forms::ToolStrip^ toolStrip1;
		System::Windows::Forms::ToolStripButton^ ñîçäàòüToolStripButton;
		System::Windows::Forms::ToolStripButton^ loadToolStripButton;
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
		System::Windows::Forms::ToolStripStatusLabel^ toolStripStatusLabel1;
		System::Windows::Forms::Panel^ panel3;

#pragma endregion

	public:
		virtual ~MainForm()
		{
			if (components)
				delete components;
		}
		MainForm(BoardDealer^ dealer)
		{
			InitializeComponent();
			bDealer = dealer;
			toolTip = gcnew System::Windows::Forms::ToolTip();
		}


	private: void InitializeComponent(void)
	{
		System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
		this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
		this->statusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
		this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
		this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
		this->ñîçäàòüToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
		this->ïå÷àòüToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
		this->bCutWords = (gcnew System::Windows::Forms::ToolStripButton());
		this->ñïðàâêàToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
		this->loadToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
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
		// toolStripStatusLabel1
		// 
		this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
		this->toolStripStatusLabel1->Size = System::Drawing::Size(118, 17);
		this->toolStripStatusLabel1->Text = L"toolStripStatusLabel1";
		this->toolStripStatusLabel1->Visible = false;
		// 
		// toolStrip1
		// 
		this->toolStrip1->BackColor = System::Drawing::SystemColors::Control;
		this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5)
		{
			this->ñîçäàòüToolStripButton,
				this->ïå÷àòüToolStripButton, this->bCutWords, this->ñïðàâêàToolStripButton, this->loadToolStripButton
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
		// ïå÷àòüToolStripButton
		// 
		this->ïå÷àòüToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ïå÷àòüToolStripButton.Image")));
		this->ïå÷àòüToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
		this->ïå÷àòüToolStripButton->Name = L"ïå÷àòüToolStripButton";
		this->ïå÷àòüToolStripButton->Size = System::Drawing::Size(110, 22);
		this->ïå÷àòüToolStripButton->Text = L"Ïðåäïðîñìîòð";
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
		this->bCutWords->Size = System::Drawing::Size(78, 22);
		this->bCutWords->Text = L"ÊÀÐÊÀÑ";
		this->bCutWords->ToolTipText = L"Óáðàòü ñëîâà èç ñåòêè êðîññâîðäà";
		this->bCutWords->Click += gcnew System::EventHandler(this, &MainForm::bCutWords_Click);
		// 
		// ñïðàâêàToolStripButton
		// 
		this->ñïðàâêàToolStripButton->AutoToolTip = false;
		this->ñïðàâêàToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ñïðàâêàToolStripButton.Image")));
		this->ñïðàâêàToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
		this->ñïðàâêàToolStripButton->Name = L"ñïðàâêàToolStripButton";
		this->ñïðàâêàToolStripButton->Size = System::Drawing::Size(102, 22);
		this->ñïðàâêàToolStripButton->Text = L"Î ïð&îãðàììå";
		this->ñïðàâêàToolStripButton->ToolTipText = L"Ïðîñìîòðåòü ñïðàâêó";
		this->ñïðàâêàToolStripButton->Click += gcnew System::EventHandler(this, &MainForm::ñïðàâêàToolStripButton_Click);
		// 
		// loadToolStripButton
		// 
		this->loadToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"loadToolStripButton.Image")));
		this->loadToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
		this->loadToolStripButton->Name = L"loadToolStripButton";
		this->loadToolStripButton->Size = System::Drawing::Size(81, 22);
		this->loadToolStripButton->Text = L"Çàãðóçèòü";
		this->loadToolStripButton->ToolTipText = L"Çàãðóçèòü ñïèñîê ñëîâ èç ôàéëà";
		this->loadToolStripButton->Click += gcnew System::EventHandler(this, &MainForm::loadToolStripButton_Click);
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
		this->panel1->Dock = System::Windows::Forms::DockStyle::Top;
		this->panel1->Location = System::Drawing::Point(0, 27);
		this->panel1->Name = L"panel1";
		this->panel1->Size = System::Drawing::Size(573, 509);
		this->panel1->TabIndex = 6;
		this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::panel1_Paint);
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
		this->Text = L"Ñîñòàâèòåëü êðîññâîðäîâ";
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
		this->ResumeLayout(false);
		this->PerformLayout();

	}


	// Ñîáûòèÿ
	private: System::Void tbSource_Enter(System::Object^ sender, System::EventArgs^ e)
	{

		if (tbSource->GetType() == TextBox::typeid)
		{
			if (tbSource->Lines->Length && tbSource->Lines[0] == "Ââåäèòå ñëîâà")
			{
				tbSource->Lines = nullptr;
				tbSource->ForeColor = Color::Black;
			}
		}
	}
	private: System::Void tbSource_Leave(System::Object^ sender, System::EventArgs^ e)
	{
		if (tbSource->GetType() == TextBox::typeid)
		{
			if (!tbSource->Lines->Length)
			{
				tbSource->ForeColor = SystemColors::ButtonShadow;
				tbSource->Lines = gcnew array<String^>{ "Ââåäèòå ñëîâà", "÷åðåç ïðîáåë", "èëè ñ íîâûõ ñòðîê" };
			}
		}
	}
	private: System::Void bClear_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (tbSource->GetType() == TextBox::typeid)
		{
			tbSource->ForeColor = SystemColors::ButtonShadow;
			tbSource->Lines = gcnew array<String^>{ "Ââåäèòå ñëîâà", "÷åðåç ïðîáåë", "èëè ñ íîâûõ ñòðîê" };
		}
	}
	private: System::Void bReset_Click(System::Object^ sender, System::EventArgs^ e)
	{
		bDealer->reset();

		// äèíàìè÷åñêîå èçìåíåíèå êîìïîíåíòîâ ôîðìû
		tabControl1->SelectedIndex = 0;
		tbVertical->Text = "";
		tbHorizontal->Text = "";
		tbCountStates->Text = "0";
		tbNotFitted->Text = "0";
		bCutWords->Checked = false;
		bCutWords->Enabled = false;
		numericUpDown1->Minimum = 0;
		numericUpDown1->Maximum = 0;

		auto easel = panel1->CreateGraphics();
		easel->Clear(SystemColors::Info);
	}
	private: System::Void bHandle_Click(System::Object^ sender, System::EventArgs^ e)
	{
		auto input = tbSource->Lines;
		auto inputList = splitInput(input);

		if (inputList->Count < 2 || input->Length && input[0] == "Ââåäèòå ñëîâà")
			MessageBox::Show("Ââåäèòå õîòÿ áû äâà ñëîâà!");
		else
		{
			String^ alert = "Æäèòå. Èäåò ïîñòðîåíèå êðîññâîðäà...";
			auto easel = panel1->CreateGraphics();
			auto font = gcnew Drawing::Font("Calibri", 15.0f);
			easel->DrawString(alert, font, Brushes::Gray, 10.0f, 10.0f);
			panel1->Update();

			auto task = gcnew intListDelegate(this, &MainForm::handleDelegate);
			auto callback = gcnew AsyncCallback(this, &MainForm::handleCallback);
			task->BeginInvoke(inputList, callback, task);
		}
	}
	private: System::Void bCutWords_Click(System::Object^ sender, System::EventArgs^ e)
	{
		numericUpDown1_ValueChanged(sender, EventArgs::Empty);
	}
	private: System::Void numericUpDown1_ValueChanged(System::Object^ sender, System::EventArgs^ e)
	{
		if (bDealer->StatesCount > 0)
		{
			auto stateNo = Convert::ToInt32(numericUpDown1->Value) - 1;
			bDealer->setCurrentBoard(stateNo);

			vhTextBoxesFill();

			auto easel = panel1->CreateGraphics();
			bDealer->DrawBoard(easel, bCutWords->Checked, false);
		}
	}
	private: System::Void loadToolStripButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		ñîçäàòüToolStripButton_Click(sender, EventArgs::Empty);
		
		auto fod = gcnew OpenFileDialog();
		fod->Filter = "Text files(*.txt)|*.txt";
		fod->InitialDirectory = Environment::CurrentDirectory;

		if (fod->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			auto filename = fod->FileName;
			tbSource->Lines = File::ReadAllLines(filename);
			tbSource->ForeColor = Color::Black;
			tbSource->Focus();
		}
	}
	private: System::Void ïå÷àòüToolStripButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (bDealer->StatesCount > 0)
			bDealer->PreviewBoard(bCutWords->Checked);
		else
			MessageBox::Show("Ñîñòàâüòå êðîññâîðä!", "Application");
	}
	private: System::Void ñïðàâêàToolStripButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		MessageBox::Show("Ðàçðàáîò÷èê:\nÑòóäåíò ãðóïïû ÇÝÓ-271\nÃðèãîðèé Äîëãèé ©\n2020", "Î ïðîãðàììå");
	}
	private: System::Void ñîçäàòüToolStripButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		bDealer->reset();

		// äèíàìè÷åñêîå èçìåíåíèå êîìïîíåíòîâ ôîðìû
		tabControl1->SelectedIndex = 0;
		tbVertical->Text = "";
		tbHorizontal->Text = "";
		tbCountStates->Text = "0";
		tbNotFitted->Text = "0";
		bCutWords->Checked = false;
		bCutWords->Enabled = false;
		numericUpDown1->Minimum = 0;
		numericUpDown1->Maximum = 0;

		auto easel = panel1->CreateGraphics();
		easel->Clear(SystemColors::Info);

		if (tbSource->GetType() == TextBox::typeid)
		{
			tbSource->ForeColor = SystemColors::ButtonShadow;
			tbSource->Lines = gcnew array<String^>{ "Ââåäèòå ñëîâà", "÷åðåç ïðîáåë", "èëè ñ íîâûõ ñòðîê" };
		}

		panel1->Focus();
	}
	private: System::Void panel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
	{
		numericUpDown1_ValueChanged(sender, EventArgs::Empty);
	}


	// Auxiliaries
	private: List<String^>^ splitInput(Array^ arr)
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
	private: int handleDelegate(List<String^>^ source)
	{
		watch = Stopwatch::StartNew();
		bDealer->handle(source);
		watch->Stop();
		return (int)(watch->ElapsedMilliseconds);
	}
	private: void handleCallback(IAsyncResult^ result)
	{
		auto del = (intListDelegate^)result->AsyncState;
		int time = del->EndInvoke(result);

		String^ statusString = String::Format(L"Ðàñ÷åò âûïîëíåí çà {0} ms", time);

		auto i = gcnew Action<String^>(this, &MainForm::invoke);
		Invoke(i, statusString);
	}
	private: void invoke(String^ statusString)
	{
		if (bDealer->StatesCount > 0)
		{
			bCutWords->Enabled = true;
			numericUpDown1->Minimum = 1;
			numericUpDown1->Maximum = bDealer->StatesCount;
			numericUpDown1->Value = 1;
			tbCountStates->Text = bDealer->StatesCount.ToString();

			tabControl1->SelectedIndex = 1;
			numericUpDown1_ValueChanged(this, EventArgs::Empty);
		}

		if (bDealer->FailsCount > 0)
		{
			toolTip->SetToolTip(tbNotFitted, String::Join("\n", bDealer->gimmeFails()));
			tbNotFitted->Text = bDealer->FailsCount.ToString();
			return;
		}

		toolTip->SetToolTip(tbNotFitted, "Íåò íåâîøåäøèõ ñëîâ");

		statusLabel1->Text = statusString;
	}
	private: void vhTextBoxesFill()
	{
		auto vWords = bDealer->gimmeVWords();
		auto hWords = bDealer->gimmeHWords();
		
		auto vWordsList = vWords->ToArray();
		auto hWordsList = hWords->ToArray();

		for (int i = 0; i < vWordsList->Length; ++i)
			vWordsList[i] = (i + 1).ToString() + ". " + vWordsList[i];

		for (int i = 0; i < hWordsList->Length; ++i)
			hWordsList[i] = (i + 1).ToString() + ". " + hWordsList[i];


		tbVertical->Lines = vWordsList;
		tbHorizontal->Lines = hWordsList;
	}

	};
}