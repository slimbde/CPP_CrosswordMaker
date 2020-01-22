#pragma once
using namespace System;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;


interface class IStrategy
{
public:
	void setObject(Form^ obj);  // ��������� ������� ���������������

	void inputFieldEnter();		// ������ ���������������
	void inputFieldLeave();
	void clearField();
	void reset();
	void handle();
	void next();
	void preview();
	void consolePreview();
	void about();
	void newOne();
};

