#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// These are the transition states for the FSM.
enum TRANSITION_STATES {
	REJECT = 0,				// REJECT is the starting state.
	INTEGER = 1,
	REAL = 2,
	OPERATOR = 3,
	STRING = 4,
	UNKNOWN = 5,
	SPACE = 6,
	COMMENT = 7,
	SEPARATOR = 8,
	DOLLAR = 9
};

struct StateTable {				 /* INTEGER,   REAL,      OPERATOR,  STRING,    UNKNOWN,   SPACE,   COMMENT,  SEPARATOR, DOLLAR */
	int table[10][10] = { {REJECT,	INTEGER,   REAL,      OPERATOR,  STRING,    UNKNOWN,   SPACE,   COMMENT,  SEPARATOR, DOLLAR},
	/* STATE 1 */		{INTEGER,   INTEGER,   REAL,      REJECT,	 REJECT,	REJECT,	   REJECT,  COMMENT,  REJECT, REJECT},
	/* STATE 2 */		{REAL,      REAL,      UNKNOWN,   REJECT,	 REJECT,	REJECT,    REJECT,  COMMENT,  REJECT, UNKNOWN},
	/* STATE 3 */		{OPERATOR,  REJECT,	   REJECT,	  REJECT,	 STRING,    REJECT,    REJECT,  COMMENT,  REJECT, REJECT},
	/* STATE 4 */		{STRING,    STRING,    REJECT,	  REJECT,    STRING,    REJECT,    REJECT,  COMMENT,  REJECT, STRING},
	/* STATE 5 */		{UNKNOWN,   UNKNOWN,   UNKNOWN,   UNKNOWN,   UNKNOWN,   UNKNOWN,   REJECT,  COMMENT,  REJECT, REJECT},
	/* STATE 6 */		{SPACE,     REJECT,	   REJECT,	  REJECT,	 REJECT,	REJECT,    REJECT,  COMMENT,  REJECT,	 REJECT},
	/* STATE 7 */		{COMMENT,	COMMENT,   COMMENT,	  COMMENT,	 COMMENT,	COMMENT,   COMMENT, REJECT,	  COMMENT,	 COMMENT},
	/* STATE 8 */		{SEPARATOR, REJECT,	   REJECT,	  REJECT,	 REJECT,	REJECT,	   REJECT,	COMMENT,  REJECT,	 REJECT},
	/* STATE 9 */		{DOLLAR,	REJECT,	   REJECT,	  REJECT,	 REJECT,	REJECT,	   REJECT,	COMMENT,  REJECT,	 REJECT}
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
	bool isKeyword();
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
			if (prevState != SPACE && prevState != COMMENT) {
				T.setToken(currToken);
				T.setLexeme(getLexName(prevState));
				tokens.push_back(T);
			}
			currToken = "";
		}
		else if (currState == COMMENT)
			i++;
		else {
			currToken += currChar;
			i++;
		}
		prevState = currState;
	}

	if (currState != SPACE && currToken != "") {
		T.setToken(currToken);
		T.setLexeme(getLexName(currState));
		tokens.push_back(T);
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

	else if (isAlpha(currChar))
		return STRING;

	else if (isOperator(currChar))
		return OPERATOR;

	else if (isSeparator(currChar))
		return SEPARATOR;

	else if (isComment(currChar))
		return COMMENT;

	else if (currChar == '$')
		return DOLLAR;

	return UNKNOWN;
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
		if (isKeyword())
			return "KEYWORD";
		return "IDENTIFIER";
	case SPACE:
		break;
	case SEPARATOR:
		return "SEPARATOR";
		break;
	case COMMENT:
		return "COMMENT";
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

bool FSM::isKeyword() {
	if (currToken == "int" || currToken == "float" || currToken == "bool" ||
		currToken == "if" || currToken == "else" || currToken == "then" ||
		currToken == "for" || currToken == "while" || currToken == "whileend" ||
		currToken == "do" || currToken == "doend" || currToken == "and" ||
		currToken == "or" || currToken == "function")
		return true;
	return false;
}