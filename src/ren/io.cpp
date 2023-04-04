#include "io.h"
#include "keys.h"
#include "navigate.h"
#include "resize.h"
#include "render.h"
#include "return.h"

void setIOColourPair(const int colourPair) {
	wattron(ioWindow, COLOR_PAIR(colourPair));
}

void setOutput(const std::string &string) {
	ioString = std::vector<char>(string.cbegin(), string.cend());
	ioString.push_back('\0');
	startingIOColumn = 0;
	selectedIOColumn = std::min((int) ioString.size() - 1, screenWidth - 1);
	updateIO();
}

void displayReturnMessage() {
	size_t returnType_ = returnType();
	switch (returnType_) {
		case RETURN_TYPE_WARNING:
			setIOColourPair(IO_WARNING); break;
		case RETURN_TYPE_ERROR:
			setIOColourPair(IO_ERROR); break;
	}
	setOutput(returnMessage());
}

void inschToIO(const chtype character) {
	ioString.insert(ioString.cbegin() + startingIOColumn + selectedIOColumn, character);
	moveRightThroughIO(1);
}

//delch with backspace key
void delchFromIOB() {
	int effectiveIOColumn = startingIOColumn + selectedIOColumn;
	if (effectiveIOColumn > 0) {
		ioString.erase(ioString.cbegin() + effectiveIOColumn - 1);
		if (startingIOColumn + screenWidth - 2 != (int) ioString.size() - 1 || screenWidth - 1 == (int) ioString.size())
			moveLeftThroughIO(1);
		else
			scrollLeftThroughIO(1);
	}
}

//delch with delete key
void delchFromIOD() {
	int effectiveIOColumn = startingIOColumn + selectedIOColumn;
	if (effectiveIOColumn < (int) ioString.size() - 1) {
		ioString.erase(ioString.cbegin() + effectiveIOColumn);
		if (startingIOColumn + screenWidth - 2 != (int) ioString.size() - 1 || screenWidth - 1 == (int) ioString.size())
			updateIO();
		else
			scrollLeftThroughIO(1);
	}
}

//pass string to use as prefix?
bool getInput() {
	enableCursor();
	int character;
	while ((character = wgetch(ioWindow))) {
		if (character == KEY_RESIZE) resizeScreen();
		else if (character == '\n' || character == KEY_ESCAPE) break;
		//character is printable
		if (character >= 32 && character <= 126) inschToIO(character);
		else if (character == '\b' || character == KEY_BACKSPACE) delchFromIOB();
		else if (character == KEY_DC) delchFromIOD();
		else if (character == KEY_LEFT) moveLeftThroughIO(1);
		else if (character == KEY_RIGHT) moveRightThroughIO(1);
		else if (character == KEY_SLEFT) scrollLeftThroughIO(1);
		else if (character == KEY_SRIGHT) scrollRightThroughIO(1);
		else if (character == KEY_HOME) moveThroughIO(0);
		else if (character == KEY_END) moveThroughIO(ioString.size() - 1);
		doupdate();
	}
	disableCursor();
	return character == '\n';
}
