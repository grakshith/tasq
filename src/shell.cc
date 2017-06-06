#include "shell.h"
using namespace std;

Shell::Shell(){
	count=1;
}

Shell::~Shell(){}

void Shell::repl(int argc, char** argv){
	while(1){
		cout<<"["<<count++<<"] ";
		string input = getString();
		cout<<input<<endl;
	}
}

string Shell::getString(){
	string input;
	getline(cin,input);
	return input;
}

int main(int argc, char **argv)
{
	Shell shell;
	shell.repl(argc, argv);
	return 0;
}