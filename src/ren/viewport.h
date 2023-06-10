#ifndef VIEWPORT_H
#define VIEWPORT_H

//TODO: use size_t and prevent overflow/underflow
//add effectiveElement?/effectiveSelectedElement?
class Viewport {
	protected:
		int _firstElement;
		int _selectedElement;
		
		int (*_viewableElements)();
		int (*_totalElements)();
	public:
		Viewport(int (*viewableElements)(), int (*totalElements)());

		int firstElement() const noexcept;
		int selectedElement() const noexcept;

		int viewableElements() const;
		int totalElements() const;

		void refresh();

		void moveBackward(int elements);
		void moveForward(int elements);
		void scrollBackward(int elements);
		void scrollForward(int elements);

		void selectElement(int element);
};

#endif
