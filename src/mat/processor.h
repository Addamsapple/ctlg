#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "commands.h"
#include "field_constructor.h"
#include "matcher.h"

inline constexpr int NO_MATCH = -2;
inline constexpr int PARTIAL_MATCH = -1;
inline constexpr int FULL_MATCH = 0;

using PatternMatcherVector = std::vector<PatternMatcher>;

//reorder class definitions?
//try to get working again with template construction, having an add() method allows bugs to occur, when add is called after matching, and prior to resetting. it may or may not affect code size, will have to check, but the there is no (current) intention to add/remove patterns/commands during runtime, and constructing the processors in one call removes the need for function calls to loadTypes(), loadCommands, etc.

class PatternProcessor {
	protected:
		std::vector<int> _remainingMatchers;
	public:
		PatternMatcherVector _matchers;

		int match(const char character, const bool returnOnFirstMatch);
		int match(const std::string &string);

		void add(PatternMatcher &&matcher);

		void reset();
};

using CommandConstructor = Command * (*)();
using FieldConstructorConstructor = FieldConstructorInterface* (*)(StringVector &&);

template<typename T, typename... Ts>
class Processor {//rename?
	protected:
		std::vector<T> _callbacks;
		PatternProcessor _processor;

		void invoke(const int rule, Ts... arguments);
	public:
		int match(const char character, Ts... arguments);
		int match(const std::string &string, Ts... arguments);

		void add(T callback, PatternMatcher &&matcher);

		void reset();
};

#include "processor_t.cpp"

#endif
