#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "commands.h"
#include "field.h"
#include "matcher.h"

inline constexpr int NO_MATCH = -2;
inline constexpr int PARTIAL_MATCH = -1;
inline constexpr int FULL_MATCH = 0;

using PatternMatcherVector = std::vector<PatternMatcher>;

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
class Processor {
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
