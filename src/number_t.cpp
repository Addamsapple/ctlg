#include <iomanip>
#include <stdexcept>

template<typename Type>
Number<Type>::Number(std::string &&string, const int precision) : Field(std::move(string)), _value(strton(this->_string)) {
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

template<typename Type, Type (*Function)(const char *, char **)>
Type _strton(const std::string &string) {
	char *pointer;
	Type result = Function(string.c_str(), &pointer);
	if (*pointer != '\0' || string.size() == 0)
		throw std::runtime_error("Invalid number format - \"" + string + '\"');
	if (errno == ERANGE)
		throw std::runtime_error("Number out of range - \"" + string + '\"');
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
