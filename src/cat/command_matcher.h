#ifndef COMMAND_MATCHER_H
#define COMMAND_MATCHER_H

#include "trie.h"

#include "command.h"

using CommandConstructor = Command * (*)(std::string, std::string);

//make abstract class
//then make BufferedCommandMatcher
//and UnbufferedCommandMatcher, which just have different match() functions.
/*class CommandMatcher {
	protected:
		Matcher<CommandConstructor> _matcher;
		std::string _prefix;
		bool _prefixParsed;

		bool _addToPrefix(char character);
	public:
		void add(const std::string &string, CommandConstructor constructor);

		size_t match(char character, Command **command);
		size_t match(const std::string &string, Command **command);

		void reset();
};*/

class DigitExtractor {
	protected:
		std::string _digits;

		bool _finished;
	public:
		DigitExtractor();

		const std::string & digits() const ;

		bool match(char character);
		void reset();

};

class StringCommandMatcher {
	protected:
		StringMatcher<CommandConstructor> _matcher;
		DigitExtractor _extractor;//can just create this whenever match is called, dont need to keep instance?
	public:
		void add(std::string pattern, CommandConstructor constructor);

		std::pair<Command *, size_t>  match(const std::string &pattern);
};

class CharacterCommandMatcher {
	protected:
		CharacterMatcher<CommandConstructor> _matcher;
		DigitExtractor _extractor;
	public:
		void add(std::string pattern, CommandConstructor constructor);

		std::pair<Command *, size_t> match(char character);

		void reset();
};

#endif
