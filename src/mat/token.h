#ifndef TOKEN_H
#define TOKEN_H

//change to inline constexpr?
//need additional token types: variadic strings, single char string, variadic char string
const int CHR_TOKEN = 0;
const int NUM_TOKEN = 1;
const int STR_TOKEN = 2;

class Token {
	protected:
		int _type;
		char _character;
	public:
		Token(int type);
		Token(char character);

		bool match(const char character) const;

		int type() const;
		char character() const;
};

#endif
