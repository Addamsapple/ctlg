#include <iomanip>
#include <stdexcept>

#include "return.h"

//why assign string then reassign? just construct _value first, then assign _string
//field and hence string member will definitely be constructed first, but if its getting overwritten anyways, rather keep in a temp variable 
template<typename Type>
Number<Type>::Number(std::string &&string, const int precision) : Field(std::move(string)), _value(strton(this->_string)) {
	//check if string is empty, then set default value?
	this->_string = ntostr(_value, precision);
}

template<typename Type>
Number<Type>::Number(std::string &&string) : Field(std::move(string)), _value(strton(this->_string)) {
	this->_string = ntostr(_value);
}

template<typename Type>
void Number<Type>::reassign(std::string &&string, const int precision) {
	_value = strton(string);
	this->_string = ntostr(_value, precision);
}

template<typename Type>
void Number<Type>::reassign(std::string &&string) {
	_value = strton(string);
	this->_string = ntostr(_value);
}

template<typename Type, Type (*callback)(const char *, char **)>
Type _strton(const std::string &string) {
	setReturnCode(0, "");
	char *pointer;
	Type result = callback(string.c_str(), &pointer);
	if (*pointer != '\0' || string.size() == 0)
		//setReturnCode<-1>(420, "Invalid number format");
		setReturnCode(420, "Invalid number format");
	if (errno == ERANGE)
		//setReturnCode<-1>(69420, "Number out of range");
		setReturnCode(69420, "Number out of range");
	return result;
}

template<typename Type>
std::string Number<Type>::ntostr(const Type value, const int precision) {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(precision) << value;
	return stream.str();
}

template<typename Type>
std::string Number<Type>::ntostr(const Type value) {
	return std::to_string(value);
}

template<typename Type>
bool Number<Type>::operator<(const Field &field) const {
	return _value < static_cast<const Number<Type> &>(field)._value;
}
