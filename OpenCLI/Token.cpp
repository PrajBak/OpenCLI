#include"Token.h"

using namespace myCalc;

Token Token::stringToToken(std::string str)
{
	Token token;

	if (isdigit(std::stof(str)))
		token.mTokenType = Number;
	else if (str == "(")
		token.mTokenType = leftBraces;
	else if (str == ")")
		token.mTokenType = rightBraces;
	else if (str == "(")
		token.mTokenType = leftBraces;
	else
	{
		if (str == "+") {
			token.mTokenType = Operator;
			token.mTokenAssoc = Left;
			token.mTokenPriority = 10;
			token.mTokenSymbol = "+";
		}
		else if (str == "-") {
			token.mTokenType = Operator;
			token.mTokenAssoc = Left;
			token.mTokenPriority = 10;
			token.mTokenSymbol = "-";
		}
		else if (str == "*") {
			token.mTokenType = Operator;
			token.mTokenAssoc = Left;
			token.mTokenPriority = 20;
			token.mTokenSymbol = "*";
		}
		else if (str == "/") {
			token.mTokenType = Operator;
			token.mTokenAssoc = Left;
			token.mTokenPriority = 20;
			token.mTokenSymbol = "/";
		}
		else if (str == "^") {
			token.mTokenType = Operator;
			token.mTokenAssoc = Left;
			token.mTokenPriority = 30;
			token.mTokenSymbol = "^";
		}

		return token;
	}
}
