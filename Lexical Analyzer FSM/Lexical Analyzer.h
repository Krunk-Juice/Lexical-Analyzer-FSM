#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// These are the transition states for the FSM.
enum TRANSITION_STATES {
	REJECT = 0,
	INTEGER = 1,
	REAL = 2,
	OPERATOR = 3,
	STRING = 4,
	UNKNOWN = 5,
	SPACE = 6,
	COMMENT = 7
};

//class StateTable {
//private:
//	int table[7][7] =
//	{ {TRANSITION_STATES::REJECT, TRANSITION_STATES::INTEGER, TRANSITION_STATES::REAL, TRANSITION_STATES::OPERATOR, TRANSITION_STATES::STRING, TRANSITION_STATES::UNKNOWN, TRANSITION_STATES::SPACE},
//	TRANSITION_STATES::INTEGER,  } };
//};

struct StateTable {				 /* INTEGER,   REAL,      OPERATOR,  STRING,    UNKNOWN,   SPACE,   COMMENT */
	int table[8][8] = { {REJECT,	INTEGER,   REAL,      OPERATOR,  STRING,    UNKNOWN,   SPACE,   COMMENT},
	/* STATE 1 */		{INTEGER,   INTEGER,   REAL,      REJECT,	 REJECT,	REJECT,	   REJECT,  COMMENT},
	/* STATE 2 */		{REAL,      REAL,      UNKNOWN,   REJECT,	 REJECT,	REJECT,    REJECT,  COMMENT},
	/* STATE 3 */		{OPERATOR,  REJECT,	   REJECT,	  REJECT,	 STRING,    REJECT,    REJECT,  COMMENT},
	/* STATE 4 */		{STRING,    STRING,    REJECT,	  STRING,    STRING,    REJECT,    REJECT,  COMMENT},
	/* STATE 5 */		{UNKNOWN,   UNKNOWN,   UNKNOWN,   UNKNOWN,   UNKNOWN,   UNKNOWN,   REJECT,  COMMENT},
	/* STATE 6 */		{SPACE,     REJECT,	   REJECT,	  REJECT,	 REJECT,	REJECT,    REJECT,  COMMENT},
	/* STATE 7 */		{COMMENT,	COMMENT,   COMMENT,	  COMMENT,	 COMMENT,	COMMENT,   COMMENT, REJECT}
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
	string currToken;
	Token T;
	StateTable S;
	int getCol(char currChar);
	string getLexName(int lex);
	bool isSpace(char currChar);
	bool isDigit(char currChar);
	bool isReal(char currChar);
	bool isAlpha(char currChar);
	bool isOperator(char currChar);
	bool isSeparator(char currChar);
	bool isComment(char currChar);
	bool isKeyword(string currToken);
public:
	vector<Token> lexer(string);
};

vector<Token> FSM::lexer(string expression) {
	vector<Token> tokens;
	char currChar = ' ';
	int col = REJECT;
	int currState = REJECT;
	int prevState = REJECT;
	currToken = "";


	for (int i = 0; i < expression.length();) {
		currChar = expression[i];

		col = getCol(currChar);

		currState = S.table[currState][col];

		if (currState == REJECT) {
			if (prevState != SPACE) {
				T.setToken(currToken);
				T.setLexeme(getLexName(prevState));
				tokens.push_back(T);
			}
			currToken = "";
		}
		else {
			currToken += currChar;
			i++;
		}
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

string FSM::getLexName(int lex) {
	switch (lex) {
	case INTEGER:
		return "INTEGER";
		break;
	case REAL:
		return "REAL";
		break;
	case OPERATOR:
		return "OPERATOR";
		break;
	case STRING:
		if (isKeyword(currToken))
			return "KEYWORD";
		return "IDENTIFIER";
	case SPACE:
		break;
	case COMMENT:
		break;
	case UNKNOWN:
		return "UNKNOWN";
		break;
	default:
		return "ERROR";
		break;
	}
}

bool FSM::isSpace(char currChar) {
	if (currChar == ' ')
		return true;
	return false;
}

bool FSM::isDigit(char currChar) {
				/*	 0 ---------------- 9	*/
	if (currChar >= '0' && currChar <= '9')
		return true;
	return false;
}

bool FSM::isReal(char currChar) {
	if (currChar == '.')
		return true;
	return false;
}

bool FSM::isAlpha(char currChar) {
				/*	 A -------------- Z						a --------------- z		*/
	if ((currChar >= 65 && currChar <= 90) || (currChar >= 97 && currChar <= 122))
		return true;
	return false;
}

bool FSM::isOperator(char currChar) {
	if (currChar == '+' || currChar == '-' || currChar == '*' || currChar == '/' ||
		currChar == '>' || currChar == '<' || currChar == '=')
		return true;
	return false;
}

bool FSM::isComment(char currChar) {
	if (currChar == '!')
		return true;
	return false;
}

bool FSM::isSeparator(char currChar) {
	if (currChar == '(' || currChar == ')' || currChar == '[' || currChar == ']' ||
		currChar == '{' || currChar == '}')
		return true;
	return false;
}