#ifndef COMMAND_MATCHER_H
#define COMMAND_MATCHER_H

#include "trie.h"

#include "command.h"

using CommandConstructor = Command * (*)(std::string, std::string);

//TODO: Rename/refactor this class
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

//TODO:return unique_ptr instead of raw pointer
class StringCommandMatcher {
	protected:
		StringMatcher<CommandConstructor> _matcher;
	public:
		void add(std::string string, CommandConstructor constructor);

		std::pair<Command *, int>  match(const std::string &string) const;
};

//TODO: Use Command * (*)(std::string) instead of Command * (*)(std::string, std::string), since suffix arguments cannot be obtained.
class CharacterCommandMatcher {
	protected:
		CharacterMatcher<CommandConstructor> _matcher;
		DigitExtractor _extractor;
	public:
		void add(std::string string, CommandConstructor constructor);

		std::pair<Command *, int> match(char character);

		void reset();
};

#endif
