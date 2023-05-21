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

class StringCommandMatcher {
	protected:
		using callback = std::unique_ptr<Command> (*)(std::string, std::string);

		StringMatcher<callback> _matcher;
	public:
		void add(std::string string, callback creator);

		std::pair<std::unique_ptr<Command>, MatchResult>  match(const std::string &string) const;
};

//TODO: Use Command * (*)(std::string) instead of Command * (*)(std::string, std::string), since suffix arguments cannot be obtained.
class CharacterCommandMatcher {
	protected:
		using callback = std::unique_ptr<Command> (*)(std::string, std::string);

		CharacterMatcher<callback> _matcher;
		DigitExtractor _extractor;
	public:
		void add(std::string string, callback creator);

		std::pair<std::unique_ptr<Command>, MatchResult> match(char character);

		void reset();
};

#endif
