#include "command.h"
#include "trie.h"

using CommandConstructor = Command * (*)(std::vector<std::string>);

class CommandMatcher {
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
};
