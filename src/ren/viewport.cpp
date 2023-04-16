#include <algorithm>

#include "viewport.h"

Viewport::Viewport(int (*viewableElements)(), int (*totalElements)()) : _firstElement(0), _selectedElement(0), _viewableElements(viewableElements), _totalElements(totalElements) {}

int Viewport::firstElement() const {
	return _firstElement;
}

int Viewport::selectedElement() const {
	return _selectedElement;
}

int Viewport::viewableElements() const {
	return _viewableElements();
}

int Viewport::totalElements() const {
	return _totalElements();
}

template<const int & (*Function)(const int &, const int &)>
int moveTowardBound(int &element, int elements, int elementBound) {
	int moved = Function(element + elements, elementBound) - element;
	element += moved;
	return moved;
}

void Viewport::moveBackward(int elements) {
	moveTowardBound<std::max<int>>(_firstElement, -elements - moveTowardBound<std::max<int>>(_selectedElement, -elements, 0), 0);
}

void Viewport::moveForward(int elements) {
	moveTowardBound<std::min<int>>(_firstElement, elements - moveTowardBound<std::min<int>>(_selectedElement, elements, std::min(_viewableElements(), _totalElements()) - 1), std::max(_totalElements() - _viewableElements(), 0));
}

void Viewport::scrollBackward(int elements) {
	moveTowardBound<std::min<int>>(_selectedElement, -moveTowardBound<std::max<int>>(_firstElement, -elements, 0), std::min(_viewableElements(), _totalElements()) - 1);
}

void Viewport::scrollForward(int elements) {
	moveTowardBound<std::max<int>>(_selectedElement, -moveTowardBound<std::min<int>>(_firstElement, elements, std::max(_totalElements() - _viewableElements(), 0)), 0);
}

void Viewport::selectElement(int element) {
	int elements = element - (_firstElement + _selectedElement);
	if (elements < 0)
		moveBackward(-elements);
	else
		moveForward(elements);
}
