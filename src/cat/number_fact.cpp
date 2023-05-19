#include "number.h"

template<typename T>
Field * NumberFactory<T>::_createWithArgs(std::string field) const {
	return new Number<T>(field, _precision);
}

template<typename T>
Field * NumberFactory<T>::_createWithoutArgs(std::string field) const {
	return new Number<T>(field);
}

template<typename T>
NumberFactory<T>::NumberFactory(std::string arguments) : FieldFactory("") {
	if (arguments.size() > 0) {
		_precision = Number<T>::strton(arguments);
		_callback = &NumberFactory<T>::_createWithArgs;
	} else
		_callback = &NumberFactory<T>::_createWithoutArgs;
}

template<typename T>
Field * NumberFactory<T>::create(std::string number) const {
	return (this->*_callback)(number);
}

template class NumberFactory<size_t>;
template class NumberFactory<long>;
template class NumberFactory<float>;
