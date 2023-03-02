#include "keys.h"
#include "token.h"

Token::Token(int type) : _type(type), _character('\0') {}

Token::Token(char character) : _type(CHR_TOKEN), _character(character) {}

//consider combing type and character into one variable, since first 32 charcter symbols unused
//consider adding VNUM_TOKEN and VSTR_TOKEN, to match 0 or more NUM/STR tokens
//num could use any non digit symbol to seperate numbers, but STR would have to use the delimiter character
//would have to modify some match methods to return ints, so that we can distinguish between match/fail and also a VNUM/STR delimiter

bool Token::match(const char character) const {
	if (_type == CHR_TOKEN)
		return _character == character;
	else if (_type == NUM_TOKEN)
		return character >= '0' && character <= '9';
	else if (_type == STR_TOKEN)
		return character >= 32 && character <= 126 && character != KEY_DELIMITER;
	return false;
}

int Token::type() const {
	return _type;
}

char Token::character() const {
	return _character;
}
