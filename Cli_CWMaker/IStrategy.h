#pragma once
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

interface class IStrategy
{
public:
    void inputFieldEnter(Control^ input);
    void inputFieldLeave(Control^ input);
    void clearField(Control^ field);
    void reset();
    void handle();
    void next();
};

