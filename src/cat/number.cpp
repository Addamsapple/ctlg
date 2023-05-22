#include "number.h"

#include <iomanip>

#include "return.h"


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

template<typename Type>
std::string Number<Type>::ntostr(const Type value, const int precision) {
	return (std::ostringstream() << std::fixed << std::setprecision(precision) << value).str();
}

template<typename Type>
std::string Number<Type>::ntostr(const Type value) { return std::to_string(value); }

template<typename Type>
int Number<Type>::compare(const Field &field) const {
	return (_value > static_cast<const Number<Type> &>(field)._value) - (_value < static_cast<const Number<Type> &>(field)._value);
}

template<typename T>
auto _strton(T callback, const std::string &string) {
	setReturnCode(0, "");
	char *pointer;
	auto result = callback(string.c_str(), &pointer);
	if (*pointer != '\0' || string.size() == 0)
		setReturnCode(420, "Invalid number format");
	if (errno == ERANGE)
		setReturnCode(69420, "Number out of range");
	return result;
}

long _strtol(const char *str, char **str_end) { return strtol(str, str_end, 10); }
long long _strtoll(const char *str, char **str_end) { return strtoll(str, str_end, 10); }
unsigned long _strtoul(const char *str, char **str_end) { return strtoul(str, str_end, 10); }
unsigned long long _strtoull(const char *str, char **str_end) { return strtoul(str, str_end, 10); }

template<> long Number<long>::strton(const std::string &string) { return _strton(_strtol, string); }
template<> long long Number<long long>::strton(const std::string &string) { return _strton(_strtoll, string); }
template<> unsigned long Number<unsigned long>::strton(const std::string &string) { return _strton(_strtoul, string);}
template<> unsigned long long Number<unsigned long long>::strton(const std::string &string) { return _strton(_strtoull, string); }
template<> float Number<float>::strton(const std::string &string) { return _strton(strtof, string); }
template<> double Number<double>::strton(const std::string &string) { return _strton(strtod, string); }

template<typename T>
std::unique_ptr<Field> NumberFactory<T>::_createWithArgs(std::string &&field) const { return std::make_unique<Number<T>>(std::move(field), _precision); }

template<typename T>
std::unique_ptr<Field> NumberFactory<T>::_createWithoutArgs(std::string &&field) const { return std::make_unique<Number<T>>(std::move(field)); }

template<typename T>
NumberFactory<T>::NumberFactory(const std::string &arguments) : FieldFactory("") {
	if (arguments.size() > 0) {
		_precision = Number<T>::strton(arguments);
		_callback = &NumberFactory<T>::_createWithArgs;
	} else
		_callback = &NumberFactory<T>::_createWithoutArgs;
}

template<typename T>
std::unique_ptr<Field> NumberFactory<T>::create(std::string &&number) const { return (this->*_callback)(std::move(number)); }

template class Number<size_t>;
template class Number<long>;
template class Number<float>;
template class NumberFactory<size_t>;
template class NumberFactory<long>;
template class NumberFactory<float>;
