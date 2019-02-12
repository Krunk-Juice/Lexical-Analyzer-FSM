#include "Lexical Analyzer.h"

int main()
{
	ifstream infile;
	string str;
	FSM T;
	vector<Token> tokens;

	while (!infile.eof()) {
		getline(infile, str);

		tokens = T.lexer(str);

		for (int i = 0; i < tokens.size(); i++) {
			cout << tokens[i].getToken() << "   " <<
				tokens[i].getLexeme() << endl;
		}
	}

	return 0;
}