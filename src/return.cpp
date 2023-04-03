#include <string>

#include "return.h"

size_t _returnCode;

std::string _returnMessage;

size_t returnCode() {
	return _returnCode;
}

size_t returnType() {
	return (_returnCode + RETURN_TYPE_CODES - 1) / RETURN_TYPE_CODES;
}

std::string returnMessage() {
	return _returnMessage;
}

void setReturnCode(const size_t returnCode_) {
	_returnCode = returnCode_;
}

/*template<int Behaviour>
void setReturnCode(const size_t returnCode_, const std::string &returnMessage_) {
		//_returnCode = returnCode_;
		setReturnCode(returnCode_);
		if constexpr(Behaviour == PREPEND_TO_MESSAGE)
				_returnMessage = returnMessage_ + std::string(" - ") + _returnMessage;
		else if constexpr(Behaviour == OVERWRITE_MESSAGE)
				_returnMessage = returnMessage_;
		else if constexpr(Behaviour == APPEND_TO_MESSAGE)
				_returnMessage = _returnMessage + " - " + returnMessage_;
}*/

void setReturnCode(const size_t returnCode_, const std::string &returnMessage_) {
	_returnCode = returnCode_;
	_returnMessage = returnMessage_;
}

void setReturnCode(const size_t returnCode_, std::string &&returnMessage_) {
	_returnCode = returnCode_;
	_returnMessage = std::move(returnMessage_);
}

/*
template void setReturnCode<PREPEND_TO_MESSAGE>(const size_t returnCode_, const std::string &returnMessage_);
template void setReturnCode<OVERWRITE_MESSAGE>(const size_t returnCode_, const std::string &returnMessage_);
template void setReturnCode<APPEND_TO_MESSAGE>(const size_t returnCode_, const std::string &returnMessage_);
*/
