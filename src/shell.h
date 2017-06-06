#include <iostream>
#include <cstring>
#include <string>

class Shell{
public:
	Shell();
	~Shell();

	unsigned int count;

	void repl(int argc, char **argv);
	std::string getString();

};
