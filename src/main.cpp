#include "interface.h"

#include "com/trie.h"//testing
#include <iostream>//testing
#include "command.h"

int main(int argc, char **argv) {

	Matcher<Command * (*)(std::vector<std::string>)> matcher;
	/*Matcher<int> matcher;
	matcher.add("asdf", 4);
	matcher.add("bf", 69);
	matcher.add("asd5f", 22);

	std::cout << matcher.match("asdf") << '\n';
	std::cout << *matcher.get() << '\n';
	matcher.reset();
	std::cout << matcher.match("asd5f") << '\n';
	std::cout << *matcher.get() << '\n';
	matcher.reset();
	std::cout << matcher.match('b') << '\n';
	std::cout << *matcher.get() << '\n';
	matcher.reset();*/

	//run(argv[argc - 1]);
	return 0;
}
