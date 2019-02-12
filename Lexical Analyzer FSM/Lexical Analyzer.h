#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// These are the transition states for the FSM.
enum TRANSITION_STATES {
	DELIMITER = 0,
	INTEGER = 1,
	REAL = 2,
	OPERATOR = 3,
	STRING = 4,
	UNKNOWN = 5,
	SPACE = 6
};

//class StateTable {
//private:
//	int table[7][7] =
//	{ {TRANSITION_STATES::DELIMITER, TRANSITION_STATES::INTEGER, TRANSITION_STATES::REAL, TRANSITION_STATES::OPERATOR, TRANSITION_STATES::STRING, TRANSITION_STATES::UNKNOWN, TRANSITION_STATES::SPACE},
//	TRANSITION_STATES::INTEGER,  } };
//};

class StateTable {				 /* INTEGER,   REAL,      OPERATOR,  STRING,    UNKNOWN,   SPACE */
	int table[7][7] = { {DELIMITER, INTEGER,   REAL,      OPERATOR,  STRING,    UNKNOWN,   SPACE},
	/* STATE 1 */		{INTEGER,   INTEGER,   REAL,      DELIMITER, DELIMITER, DELIMITER, DELIMITER},
	/* STATE 2 */		{REAL,      REAL,      UNKNOWN,   DELIMITER, DELIMITER, DELIMITER, DELIMITER},
	/* STATE 3 */		{OPERATOR,  DELIMITER, DELIMITER, DELIMITER, STRING,    DELIMITER, DELIMITER},
	/* STATE 4 */		{STRING,    STRING,    DELIMITER, STRING,    STRING,    DELIMITER, DELIMITER},
	/* STATE 5 */		{UNKNOWN,   UNKNOWN,   UNKNOWN,   UNKNOWN,   UNKNOWN,   UNKNOWN,   DELIMITER},
	/* STATE 6 */		{SPACE,     DELIMITER, DELIMITER, DELIMITER, DELIMITER, DELIMITER, DELIMITER}
	};
};

class Token {
private:
	string token;
	string lexeme;
public:
	string getToken(){ return token; }
	string getLexeme() { return lexeme; }
	void setToken(string t) { token = t; }
	void setLexeme(string l) { lexeme = l; }
};

class FSM {
private:
	//string token;
	//int lexeme;
	//string lexeme;
	Token T;
	int getCol(char currChar);
	bool isSpace(char currChar);
	bool isDigit(char currChar);
	bool isReal(char currChar);
	bool isAlpha(char currChar);
public:
	vector<Token> lexer(string);
};

vector<Token> FSM::lexer(string expression) {
	vector<Token> tokens;
	char currChar = ' ';
	int col = DELIMITER;
	int currState = DELIMITER;
	string currToken = "";


	for (int i = 0; i < expression.length();) {
		currChar = expression[i];


	}

	return tokens;
}

int FSM::getCol(char currChar) {
	if (isSpace(currChar))
		return SPACE;

	else if (isDigit(currChar))
		return INTEGER;

	else if (isReal(currChar))
		return REAL;
}

bool FSM::isSpace(char currChar) {
	if (currChar == ' ')
		return true;
	return false;
}

bool FSM::isDigit(char currChar) {
	if (currChar == '0' || currChar == '1' || currChar == '2' || currChar == '3' ||
		currChar == '4' || currChar == '5' || currChar == '5' || currChar == '6' ||
		currChar == '7' || currChar == '8' || currChar == '9')
		return true;
	return false;
}

bool FSM::isReal(char currChar) {
	if (currChar == '.')
		return true;
	return false;
}

bool FSM::isAlpha(char currChar) {
	if ((currChar >= 65 && currChar <= 90) || (currChar >= 97 && currChar <= 122))
		return true;
	return false;
}