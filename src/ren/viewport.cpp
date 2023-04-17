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
int clamp(int &value, int increment, int limit) {
	int result = Function(value + increment, limit) - value;
	value += result;
	return result;
}

void Viewport::refresh() {
	if (int scrolled = clamp<std::min<int>>(_firstElement, 0, std::max(_totalElements() - viewableElements(), 0)))
		clamp<std::min<int>>(_selectedElement, -scrolled, std::min(_viewableElements(), _totalElements()) - 1);
	else if (int moved = clamp<std::min<int>>(_selectedElement, 0, std::min(_viewableElements(), _totalElements()) - 1))
		clamp<std::min<int>>(_firstElement, -moved, std::max(_totalElements() - viewableElements(), 0));
}

void Viewport::moveBackward(int elements) {
	clamp<std::max<int>>(_firstElement, -elements - clamp<std::max<int>>(_selectedElement, -elements, 0), 0);
}

void Viewport::moveForward(int elements) {
	clamp<std::min<int>>(_firstElement, elements - clamp<std::min<int>>(_selectedElement, elements, std::min(_viewableElements(), _totalElements()) - 1), std::max(_totalElements() - _viewableElements(), 0));
}

void Viewport::scrollBackward(int elements) {
	clamp<std::min<int>>(_selectedElement, -clamp<std::max<int>>(_firstElement, -elements, 0), std::min(_viewableElements(), _totalElements()) - 1);
}

void Viewport::scrollForward(int elements) {
	clamp<std::max<int>>(_selectedElement, -clamp<std::min<int>>(_firstElement, elements, std::max(_totalElements() - _viewableElements(), 0)), 0);
}

void Viewport::selectElement(int element) {
	if (int elements = element - (_firstElement + _selectedElement); elements < 0)
		moveBackward(-elements);
	else
		moveForward(elements);
}
