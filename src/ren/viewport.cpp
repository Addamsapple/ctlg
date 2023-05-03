#include <algorithm>

#include "viewport.h"

Viewport::Viewport(int (*viewableElements)(), int (*totalElements)()) :
		_firstElement(0),
		_selectedElement(0),
		_viewableElements(viewableElements),
		_totalElements(totalElements) {}

int Viewport::firstElement() const { return _firstElement; }

int Viewport::selectedElement() const { return _selectedElement; }

int Viewport::viewableElements() const { return _viewableElements(); }

int Viewport::totalElements() const { return _totalElements(); }

template<const int & (*Function)(const int &, const int &)>
int clamp(int &value, int increment, int limit) {
	int result = Function(value + increment, limit) - value;
	value += result;
	return result;
}

#define first\
	_firstElement

#define selected\
	_selectedElement

#define viewable\
	_viewableElements()

#define total\
	_totalElements()

//potential bug:
//when viewable/total = 0, min clamping selected to std::min(viewable, total) - 1 will set it to -1
//this affects refresh(), moveForward() and scrollBackward()
//consider wrapping this expression as: std::max(<expression>, 0)

void Viewport::refresh() {
	if (int scrolled = clamp<std::min<int>>(first, 0, std::max(total - viewable, 0)))
		clamp<std::min<int>>(selected, -scrolled, std::min(viewable, total) - 1);
	else if (int moved = clamp<std::min<int>>(selected, 0, std::min(viewable, total) - 1))
		clamp<std::min<int>>(first, -moved, std::max(total - viewable, 0));
}

void Viewport::moveBackward(int elements) {
	clamp<std::max<int>>(first, -elements - clamp<std::max<int>>(selected, -elements, 0), 0);
}

void Viewport::moveForward(int elements) {
	clamp<std::min<int>>(first, elements - clamp<std::min<int>>(selected, elements, std::min(viewable, total) - 1), std::max(total - viewable, 0));
}

void Viewport::scrollBackward(int elements) {
	clamp<std::min<int>>(selected, -clamp<std::max<int>>(first, -elements, 0), std::min(viewable, total) - 1);
}

void Viewport::scrollForward(int elements) {
	clamp<std::max<int>>(selected, -clamp<std::min<int>>(first, elements, std::max(total - viewable, 0)), 0);
}

void Viewport::selectElement(int element) {
	if (int elements = element - (first + selected); elements < 0)
		moveBackward(-elements);
	else
		moveForward(elements);
}
