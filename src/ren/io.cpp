#include "io.h"
#include "keys.h"
#include "populate.h"
#include "render.h"
#include "return.h"

void setIOColourPair(const int colourPair) {
	wattron(ioWindow, COLOR_PAIR(colourPair));
}

void setOutput(const std::string &string) {
	ioString = std::vector<char>(string.cbegin(), string.cend());
	ioString.push_back('\0');
	ioView.moveForward(ioString.size() - 1);
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
	ioString.insert(ioString.cbegin() + ioView.firstElement() + ioView.selectedElement(), character);
	ioView.moveForward(1);
}

//delch with backspace key
void delchFromIOB() {
	int effectiveIOColumn = ioView.firstElement() + ioView.selectedElement();
	if (effectiveIOColumn > 0) {
		ioString.erase(ioString.cbegin() + effectiveIOColumn - 1);
		if (ioString.size() - ioView.firstElement() == ioWindowWidth - 1 && ioView.firstElement() > 0)
			ioView.moveForward(0);
		else
			ioView.moveBackward(1);
	}
}

//delch with delete key
void delchFromIOD() {
	int effectiveIOColumn = ioView.firstElement() + ioView.selectedElement();
	if (effectiveIOColumn < (int) ioString.size() - 1) {
		ioString.erase(ioString.cbegin() + effectiveIOColumn);
		if (ioString.size() - ioView.firstElement() == ioWindowWidth - 1 && ioView.firstElement() > 0)
			ioView.moveForward(0);
	}
}

//pass string to use as prefix?
bool getInput() {
	enableCursor();
	int character;
	while ((character = wgetch(ioWindow))) {
		if (character == KEY_RESIZE) resize();
		else if (character == '\n' || character == KEY_ESCAPE) break;
		//character is printable
		else if (character >= 32 && character <= 126) inschToIO(character);
		else if (character == '\b' || character == KEY_BACKSPACE) delchFromIOB();
		else if (character == KEY_DC) delchFromIOD();
		else if (character == KEY_LEFT) ioView.moveBackward(1);
		else if (character == KEY_RIGHT) ioView.moveForward(1);
		else if (character == KEY_SLEFT) ioView.scrollBackward(1);
		else if (character == KEY_SRIGHT) ioView.scrollForward(1);
		else if (character == KEY_HOME) ioView.moveBackward(ioView.firstElement() + ioView.selectedElement());
		else if (character == KEY_END) ioView.moveForward(ioString.size() - 1);
		updateIO();//temp
		doupdate();
	}
	disableCursor();
	return character == '\n';
}
