#include "item.h"
#include "processor.h"

#include "undo.h"

int PatternProcessor::match(const char character, const bool returnOnFirstMatch) {
	for (size_t matcher = 0; matcher < _remainingMatchers.size();) {
		if (!_matchers[_remainingMatchers[matcher]].match(character))
			_remainingMatchers.erase(_remainingMatchers.begin() + matcher);
		else {
			if (returnOnFirstMatch && _matchers[_remainingMatchers[matcher]].match())
				return _remainingMatchers[matcher];
			matcher++;
		}
	}
	if (_remainingMatchers.size() == 0)
		return NO_MATCH;
	if (_remainingMatchers.size() != 1 || !_matchers[_remainingMatchers[0]].match())
		return PARTIAL_MATCH;
	return _remainingMatchers[0];
}

int PatternProcessor::match(const std::string &string) {
	int result = NO_MATCH;
	for (size_t character = 0; _remainingMatchers.size() > 0 && character < string.size(); character++)
		result = match(string[character], false);
	if (result == NO_MATCH)
		return NO_MATCH;
	if (result > PARTIAL_MATCH)
		return _remainingMatchers[0];
	for (size_t matcher = 0; matcher < _remainingMatchers.size(); matcher++)
		if (_matchers[_remainingMatchers[matcher]].match())
			return _remainingMatchers[matcher];
	return PARTIAL_MATCH;
}

void PatternProcessor::add(PatternMatcher &&matcher) {
	_matchers.emplace_back(std::move(matcher));
}

void PatternProcessor::reset() {
	_remainingMatchers.clear();
	for (size_t matcher = 0; matcher < _matchers.size(); matcher++) {
		_matchers[matcher].reset();
		_remainingMatchers.emplace_back(matcher);
	}
}

template<>
void Processor<CommandConstructor>::invoke(const int rule) {
	//memory leak
	//Command *command = _callbacks[rule](_processor._matchers[rule].arguments());
	Command *command = _callbacks[rule]("bruh");
	command->execute();
	if (command->undoable())
		recordCommand(static_cast<UndoableCommand *>(command));
}

template<>
void Processor<FieldConstructorConstructor, FieldConstructorInterface *&>::invoke(const int rule, FieldConstructorInterface *&constructor) {
	constructor = _callbacks[rule](std::move(_processor._matchers[rule].arguments()));
}
