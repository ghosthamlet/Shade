#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <set>
#include <sstream>
#include <cstdlib>
#include <cstddef>
#include <cctype>
using namespace std;
class parser {
	public:
		parser(const char *pathname);
		void parse();
	private:
		string getToken();
		char getChar();
		string getLine();
		void readUntil(char cur);
		ifstream input;
		map<string, int> instructions;
};
parser::parser(const char *pathname) : input(pathname){
	instructions["if"] = 1;
	instructions["else"] = 2;
	instructions["while"] = 3;
	instructions["int"] = 4;
	instructions["string"] = 5;
	instructions["call"] = 6;
}
void parser::parse() {
	stringstream codestream;
	codestream << "defmain\n";
	codestream << "shinit\n";
	stringstream bssstream;
	bssstream << "shbss\n";
	stringstream headerstream;
	headerstream << "%include \"shade.asm\"\n";
	headerstream << "shextern\n";
	stringstream datastream;
	datastream << "shdata\n";
	string first = getToken();
	cout << "first: " << first << endl;
	bool flag;
	//CASE-SPECIFIC VARS//
	string varname;
	string endop;
	char operation;
	//////////////////////
	while (flag) {
		switch (instructions[first]) {
			case 1:
				printf("if\n");
				break;
			case 2:
				printf("else\n");
				break;
			case 3:
				printf("while\n");
				break;
			case 4:
				printf("int\n");
				varname = getToken();
				cout << varname << endl;
				datastream << "integer " << varname << "," << getToken() << endl;
				datastream << "string __index_" << varname << "," << "\"" << varname << "\"\n";
				codestream << "shsetint __index_" << varname << "," << varname << endl;
				getLine();
				break;
			case 5:
				printf("string\n");
				varname = getToken();
				cout << varname << endl;
				datastream << "string " << varname << "," << getToken() << endl;
				datastream << "string __index_" << varname << "," << "\"" << varname << "\"\n";
				codestream << "shsetstr __index_" << varname << "," << varname << endl;
				getLine();
				break;
			case 6:
				printf("call\n");
				varname = getToken();
				codestream << "shcall " << varname << ",__index_";
				codestream << getToken() << endl;
				getLine();
				break;
			default://If we got here, it means that the first token is a symbol.
				if (!isspace(first[0]) && iscntrl(first[0])){
					flag = false;
					break;
				}
				printf("Default\n");
				/*operation = getChar();
				cout << operation << endl;
				while (operation == ' ') {
					operation = getChar();
				}
				if (operation == '=') {
						codestream << "shmov " << first << "," << getToken() << endl;
				}*/
				break;
		}
		first = getToken();
		cout << first << endl;
	}
	ofstream output("out.asm");
	output << headerstream.str() << datastream.str() << bssstream.str() << codestream.str();
	output << "exit\n";
    output.close();
	system("nasm -f elf out.asm");
	system("gcc out.o");
//	system("rm out.asm out.o");
}
string parser::getToken() {
	string token;
	input >> token;
	return token;
}
char parser::getChar() {
	return (char) input.get();
}
string parser::getLine() {
	char line[100];
	input.getline(line, 100, '\n');
	return line;
}
void parser::readUntil(char end) {
	char cur;
	while (cur != end){
		cur = getChar();
	}
}
int main(int argc, char **argv){
	parser p(argv[1]);
	p.parse();
}
