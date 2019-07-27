#pragma once
#include "Board.h"
#include "CompareByLength.h"
using namespace System;
using namespace System::Collections::Generic;



ref class Maker
{
	Stack<Board^ >^ states;
	Stack<String^ >^ wrds;

public:
	virtual ~Maker();
	Maker();

	bool Handle(IEnumerable<String^ >^ words);
	void ShowBoard();
};



inline Maker::~Maker()
{
}
inline Maker::Maker()
{
	states = gcnew Stack<Board^ >();
}

inline bool Maker::Handle(IEnumerable<String^ >^ words)
{
	Console::WriteLine("\nStarted handling words");

	// ��������� �� ����� �����
	((List<String^>^)words)->Sort(gcnew CompareByLength());
	// ��������� ����� � ����
	wrds = gcnew Stack<String^>(words);

	// ������� ��������� ���� ��� ����������� ��������� � ������ �������
	Stack<Board^ >^ reserve;

	// ������� ���� ������� � ����� ������� ����� � ������� ������ ������� �� �����
	states->Push(gcnew Board(wrds->Peek()->Length, 1));

	// ��������� ����� �� �����
	while(wrds->Count)
	{
		// ���� ��������� ��������� �����������
		bool success;

		do
		{
			// ��������� ���� success � true
			success = true;

			// ���� ���� ��������� �� ����
			while(states->Count)
			{
				// ������� �� ����� ��������� ���������
				Board^ lastBoard = states->Pop();

				// ��������� ���� ��� �������� ����������� ���������� ������ �����
				Stack<Board^ >^ results = gcnew Stack<Board^ >();

				// ������� ���� ����������� ���������� ����� � ����� ���������
				// �������� �� ������� ����� � ����� ���� ��� �� ������
				results = lastBoard->Alter(wrds->Peek());

				// ���� ���������� � ��������� �� ������
				if(results->Count != 0)
				{
					// ���� � ��� ���������� �������� ����� - ������ ��� �� ����� ����
					wrds->Pop();

					// ������� ���� ���������
					states->Clear();
					// ������ ���������� � ���� ���������
					states = gcnew Stack<Board^ >(results);

					// ������ ���������� � ��������� ������
					reserve = gcnew Stack<Board^ >(states);

					// � �.�. success �� �������� � true - ������� �� �����
					break;
				}
				else
				{
					// ���� �� ���������� �������� �����, �� �������� � ��������
					// ��������� ��������� � ��������� ���� �������� ��� �����
					success = false;
					break;
				}
			}

			// ���� �� �� ����� ��������� ����� ������� ��������, �� ������ ����������
			if(!states->Count)
			{
				states = gcnew Stack<Board^ >(reserve);
				Console::WriteLine("Cannot handle all of words, but");
				return false;
			}
		}
		while(!success);
	}

	return true;
}
inline void Maker::ShowBoard()
{
	Console::WriteLine("Found {0} solutions:", states->Count);
	while(states->Count)
		states->Pop()->Show();
	Console::WriteLine("There are {0} words left: ", wrds->Count);
	while(wrds->Count)
		Console::WriteLine(wrds->Pop());
	Console::WriteLine();
}