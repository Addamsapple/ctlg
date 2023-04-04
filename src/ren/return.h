#ifndef RETURN_H
#define RETURN_H

#include <string>

inline constexpr int PREPEND_TO_MESSAGE = -1;
inline constexpr int OVERWRITE_MESSAGE = 0;
inline constexpr int APPEND_TO_MESSAGE = 1;

size_t returnCode();
size_t returnType();

std::string returnMessage();

void setReturnCode(const size_t returnCode_);

//template<int behaviour = OVERWRITE_MESSAGE>
//void setReturnCode(const size_t returnCode_, const std::string &returnMessage_);
//template<typename T>
//void setReturnCode(const size_t returnCode_, T &&returnMessage);

void setReturnCode(const size_t returnCode_, const std::string &returnMessage_);
void setReturnCode(const size_t returnCode_, std::string &&returnMessage_);

constexpr size_t RETURN_TYPE_CODES = 1000;

constexpr size_t RETURN_TYPE_NOTE = 1;
constexpr size_t RETURN_TYPE_WARNING = 2;
constexpr size_t RETURN_TYPE_ERROR = 3;

#define CODE(code, type)\
	RETURN_TYPE_CODES * ((type) - 1) + code

inline constexpr size_t CATALOGUE_EMPTY_FILE_WARNING = CODE(1, RETURN_TYPE_WARNING);

inline constexpr size_t CATALOGUE_TYPE_HEADER_ERROR = CODE(1, RETURN_TYPE_ERROR);
inline constexpr size_t ITEM_TOO_FEW_FIELDS_ERROR = CODE(2, RETURN_TYPE_ERROR);
inline constexpr size_t ITEM_TOO_MANY_FIELDS_ERROR = CODE(3, RETURN_TYPE_ERROR);
inline constexpr size_t ITEM_FIELD_CONSTRUCTION_ERROR = CODE(4, RETURN_TYPE_ERROR);
inline constexpr size_t ITEM_CONSTRUCTOR_TYPE_ERROR = CODE(5, RETURN_TYPE_ERROR);

#endif
