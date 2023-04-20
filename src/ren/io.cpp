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

namespace {

void insert(const chtype character) {
	ioString.insert(ioString.cbegin() + ioView.firstElement() + ioView.selectedElement(), character);
	ioView.moveForward(1);
}

void backspace() {
	int effectiveIOColumn = ioView.firstElement() + ioView.selectedElement();
	if (effectiveIOColumn > 0) {
		ioString.erase(ioString.cbegin() + effectiveIOColumn - 1);
		ioView.moveBackward(1);
		ioView.refresh();
	}
}

void erase_() {
	int effectiveIOColumn = ioView.firstElement() + ioView.selectedElement();
	if (effectiveIOColumn < (int) ioString.size() - 1) {
		ioString.erase(ioString.cbegin() + effectiveIOColumn);
		ioView.refresh();
	}
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
		else if (character >= 32 && character <= 126) insert(character);
		else if (character == '\b' || character == KEY_BACKSPACE) backspace();
		else if (character == KEY_DC) erase_();
		else if (character == KEY_LEFT) ioView.moveBackward(1);
		else if (character == KEY_RIGHT) ioView.moveForward(1);
		else if (character == KEY_SLEFT) ioView.scrollBackward(1);
		else if (character == KEY_SRIGHT) ioView.scrollForward(1);
		else if (character == KEY_HOME) ioView.selectElement(0);
		else if (character == KEY_END) ioView.selectElement(ioString.size() - 1);
		updateIO();//temp
		doupdate();
	}
	disableCursor();
	return character == '\n';
}
