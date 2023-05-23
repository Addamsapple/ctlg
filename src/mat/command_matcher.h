#ifndef COMMAND_MATCHER_H
#define COMMAND_MATCHER_H

#include "trie.h"

#include "command.h"

using CommandConstructor = Command * (*)(std::string, std::string);

class StringCommandMatcher {
	protected:
		using callback = std::unique_ptr<Command> (*)(std::string &&, std::string &&);

		StringMatcher<callback> _matcher;
	public:
		template<typename... Ts> StringCommandMatcher(Ts... arguments) {
			(add(arguments.first, arguments.second), ...);
		}

		void add(std::string string, callback creator);

		std::pair<std::unique_ptr<Command>, MatchResult>  match(const std::string &string) const;
};

class CharacterCommandMatcher {
	protected:
		using callback = std::unique_ptr<Command> (*)(std::string &&, std::string &&);

		CharacterMatcher<callback> _matcher;

		std::string _modifier;
		bool _modifierFinished;

		bool _matchToModifier(char character);
	public:
		template<typename... Ts> CharacterCommandMatcher(Ts... arguments) {
			(add(arguments.first, arguments.second), ...);
		}

		void add(std::string string, callback creator);

		std::pair<std::unique_ptr<Command>, MatchResult> match(char character);

		void reset();
};

#endif
