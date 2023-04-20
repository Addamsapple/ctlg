#ifndef VIEWPORT_H
#define VIEWPORT_H

class Viewport {
	protected:
		int _firstElement;
		int _selectedElement;
		
		int (*_viewableElements)();
		int (*_totalElements)();
	public:
		Viewport(int (*viewableElements)(), int (*totalElements)());

		int firstElement() const;
		int selectedElement() const;

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
