#pragma once
#include "CWStrategy.h"
#include "CWBuilder.h"
#include "CWFactory.h"


namespace CliCWMaker
{
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;


    /// <summary>
    /// �������� ����� ����������
    /// </summary>
    public ref class MainForm : public Form
    {
        IStrategy^ strategy;    // ��������� ����������
        IBuilder^ builder;      // ��������� ������� �����
        IFactory^ factory;      // ����������� ������� ��� ���������

        #pragma region formComponentsDeclaration

        System::ComponentModel::IContainer^ components;
        System::Windows::Forms::ToolTip^ toolTip1;

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
            strategy->setObject(this); // �������� ������ �������� ������� ���������� Strategy
        }



    /*------------------------------+
        �������� ������ ������
    +------------------------------*/
    private: void InitializeComponent(void)
    {
        this->SuspendLayout();

        factory = gcnew CWFactory();
        builder = gcnew CWBuilder();

        builder->setFactory(factory)
            ->setOwner(this)
            ->buildStatusStrip()
            ->buildToolStrip()
            ->buildPanel()
            ->buildTabControl();

        auto ctrls = builder->getObject();
        for each(Control ^ item in ctrls)
        {
            item->Parent = this;
            this->Controls->Add(item);
        }

        strategy = gcnew CWStrategy();
        strategy->setObject(this);
        strategy->bind();

        //this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
        //// tbNotFitted
        //this->toolTip1->SetToolTip(this->tbNotFitted, L"��� ���������� ����");

        // MainForm
        this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
        this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
        this->ClientSize = System::Drawing::Size(784, 562);
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
        this->MaximizeBox = false;
        this->Name = L"MainForm";
        this->Text = L"CrossWRD 1.0";

        this->ResumeLayout(false);
        this->PerformLayout();
    }

    };
}