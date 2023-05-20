#ifndef COMMAND_MATCHER_H
#define COMMAND_MATCHER_H

#include "trie.h"

#include "command.h"

using CommandConstructor = Command * (*)(std::string, std::string);

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
