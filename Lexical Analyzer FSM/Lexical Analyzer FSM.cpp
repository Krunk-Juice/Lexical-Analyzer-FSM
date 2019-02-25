#include "Lexical Analyzer.h"

int main()
{
	ifstream infile;
	ofstream outfile("OutputFile.txt");
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

	cout << left << setw(15) << "TOKENS" << "LEXEMES" << endl << endl;
	outfile << left << setw(15) << "TOKENS" << "LEXEMES" << endl << endl;

	while (!infile.eof()) {
		getline(infile, str);

		tokens = T.lexer(str);

		for (int i = 0; i < tokens.size(); i++) {
			cout << left << setw(12) << tokens[i].getToken() << setw(4) << "=" <<
				tokens[i].getLexeme() << endl;
			outfile << left << setw(12) << tokens[i].getToken() << setw(4) << "=" <<
				tokens[i].getLexeme() << endl;
		}
	}

	infile.close();

	return 0;
}