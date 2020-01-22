#pragma once


interface class IPainter
{
	property float Scale { float get(); }
	property bool CutWords { bool get(); void set(bool value); }
	property bool ResetZeroPoint { bool get(); void set(bool value); }

	void drawWords();
	void drawBoard();
	void preview();
};
