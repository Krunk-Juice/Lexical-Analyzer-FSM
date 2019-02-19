#include "Lexical Analyzer.h"

int main()
{
	ifstream infile;
	string str;
	string fileName;
	FSM T;
	vector<Token> tokens;

	cout << "Enter file name: ";
	getline(cin, fileName);

	if (infile.fail()) {
		cout << "File " << fileName << " cannot be found." << endl;
		exit;
	}

	infile.open(fileName.c_str());

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