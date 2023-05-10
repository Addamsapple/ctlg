#include <iomanip>
#include <stdexcept>

#include "return.h"

//opportunity to make this a variadic template function
template<typename Type>
Number<Type>::Number(const std::string &string, const int precision) : Field("") {
	Type value = strton(string);
	if (returnCode() == 0)
		_value = value;
	else
		_value = 0;
	_string = ntostr(_value, precision);
}

template<typename Type>
Number<Type>::Number(const std::string &string) : Field("") {
	Type value = strton(string);
	if (returnCode() == 0)
		_value = value;
	else
		_value = 0;
	_string = ntostr(_value);
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
int Number<Type>::compare(const Field &field) const {
	return (_value > static_cast<const Number<Type> &>(field)._value) - (_value < static_cast<const Number<Type> &>(field)._value);
}

