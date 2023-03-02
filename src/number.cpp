#include "number.h"

long _strtol(const char *str, char **str_end) {
	return strtol(str, str_end, 10);
}

long long _strtoll(const char *str, char **str_end) {
	return strtoll(str, str_end, 10);
}

unsigned long _strtoul(const char *str, char **str_end) {
	return strtoul(str, str_end, 10);
}

unsigned long long _strtoull(const char *str, char **str_end) {
	return strtoul(str, str_end, 10);
}

template<>
long Number<long>::strton(const std::string &string) {
	return _strton<long, _strtol>(string);
}

template<>
long long Number<long long>::strton(const std::string &string) {
	return _strton<long long, _strtoll>(string);
}

template<>
unsigned long Number<unsigned long>::strton(const std::string &string) {
	return _strton<unsigned long, _strtoul>(string);
}

template<>
unsigned long long Number<unsigned long long>::strton(const std::string &string) {
	return _strton<unsigned long long, _strtoull>(string);
}

template<>
float Number<float>::strton(const std::string &string) {
	return _strton<float, strtof>(string);
}

template<>
double Number<double>::strton(const std::string &string) {
	return _strton<double, strtod>(string);
}
