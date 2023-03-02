#ifndef TOKEN_H
#define TOKEN_H

//change to inline constexpr?
const int CHR_TOKEN = 0;
const int NUM_TOKEN = CHR_TOKEN + 1;
const int STR_TOKEN = NUM_TOKEN + 1;

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
