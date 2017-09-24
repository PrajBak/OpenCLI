#include"Token.h"

using namespace OpenClI::myCalc;

Token Token::stringToToken(const std::string& str){
	Token token;
	double value = 0;
	try {
		value = std::stod(str);
	}
	catch (std::invalid_argument inv) {

		if (str == "(") {
			token.mTokenType = Token::leftBraces;
			return token;
		}
		else if (str == ")") {
			token.mTokenType = Token::rightBraces;
			return token;
		}
		else
		{
			if (str == "+") {
				token.mTokenType = Token::Operator;
				token.mTokenAssoc = Token::Left;
				token.mTokenPriority = 10;
				token.mTokenSymbol = '+';
				token.mTokenParameter = 2;
				return token;
			}
			else if (str == "-") {
				token.mTokenType = Token::Operator;
				token.mTokenAssoc = Token::Left;
				token.mTokenPriority = 10;
				token.mTokenSymbol = '-';
				token.mTokenParameter = 2;
				return token;
			}
			else if (str == "*") {
				token.mTokenType = Token::Operator;
				token.mTokenAssoc = Token::Left;
				token.mTokenPriority = 20;
				token.mTokenSymbol = '*';
				token.mTokenParameter = 2;
				return token;
			}
			else if (str == "/") {
				token.mTokenType = Token::Operator;
				token.mTokenAssoc = Token::Left;
				token.mTokenPriority = 20;
				token.mTokenSymbol = '/'; 
				token.mTokenParameter = 2;
				return token;
			}
			else if (str == "^") {
				token.mTokenType = Token::Operator;
				token.mTokenAssoc = Token::Left;
				token.mTokenPriority = 30;
				token.mTokenSymbol = '^';
				token.mTokenParameter = 2;
				return token;
			}
			else if (str == "sqrt") {
				token.mTokenType = Token::Operator;
				token.mTokenAssoc = Token::Left;
				token.mTokenPriority = 40;
				token.mTokenSymbol = "sqrt";
				token.mTokenParameter = 1;
				return token;
			}
			else if (str == "sin") {
				token.mTokenType = Token::Operator;
				token.mTokenAssoc = Token::Left;
				token.mTokenPriority = 40;
				token.mTokenSymbol = "sin";
				token.mTokenParameter = 1;
				return token;
			}
			else if (str == "cos") {
				token.mTokenType = Token::Operator;
				token.mTokenAssoc = Token::Left;
				token.mTokenPriority = 40;
				token.mTokenSymbol = "cos";
				token.mTokenParameter = 1;
				return token;
			}
			else if (str == "tan") {
				token.mTokenType = Token::Operator;
				token.mTokenAssoc = Token::Left;
				token.mTokenPriority = 40;
				token.mTokenSymbol = "tan";
				token.mTokenParameter = 1;
				return token;
			}
			else if (str == "asin") {
				token.mTokenType = Token::Operator;
				token.mTokenAssoc = Token::Left;
				token.mTokenPriority = 40;
				token.mTokenSymbol = "asin";
				token.mTokenParameter = 1;
				return token;
			}
			else if (str == "acos") {
				token.mTokenType = Token::Operator;
				token.mTokenAssoc = Token::Left;
				token.mTokenPriority = 40;
				token.mTokenSymbol = "acos";
				token.mTokenParameter = 1;
				return token;
			}
			else if (str == "atan") {
				token.mTokenType = Token::Operator;
				token.mTokenAssoc = Token::Left;
				token.mTokenPriority = 40;
				token.mTokenSymbol = "atan";
				token.mTokenParameter = 1;
				return token;
			}
		}
	}

	token.mTokenType =	Token::Number;
	token.mTokenValue = value;
	return token;
}

std::vector<Token> Token::Tokenise(std::string& expression){

	std::vector<Token> tokens;
	std::stringstream stringStream(expression);
	std::string temp;
	std::vector<std::string> stringsToken;

	while (std::getline(stringStream, temp, ' '))
		stringsToken.push_back(temp);

	for (const std::string& s : stringsToken) {
		Token T = Token::stringToToken(s);

		if (s == "-"){
			if (tokens.empty() || tokens.back().mTokenType == Token::leftBraces || tokens.back().mTokenType == Token::Operator) {
				T.mTokenSymbol = '_';
				T.mTokenAssoc = Token::Right;
				T.mTokenPriority = 40;
				T.mTokenParameter = 1;
			}
		}
		tokens.push_back(T);
	}

	return tokens;
}

std::deque<Token> Token::shuntingYard(const std::vector<Token>& tokens) {

	int index = 0;
	std::deque<Token> outputQueue;
	std::vector<Token> operatorStack;

	while (index < tokens.size()) {

		Token T = tokens[index];
		if (T.mTokenType == Token::Number) {
			outputQueue.push_back(T);
		}

		else if (T.mTokenType == Token::Operator) {

			while (operatorStack.size() != 0) {

				Token& o2 = operatorStack.back();

				if (o2.mTokenType != Token::Operator)
					break;

				else if ((T.mTokenAssoc == Token::Left && T.mTokenPriority == o2.mTokenPriority) || (T.mTokenPriority < o2.mTokenPriority)) {
					outputQueue.push_back(operatorStack.back());
					operatorStack.pop_back();
				}
				else
					break;
			}

			operatorStack.push_back(T);
		}

		else if (T.mTokenType == Token::leftBraces)
			operatorStack.push_back(T);

		else if (T.mTokenType == Token::rightBraces) {

			while (operatorStack.back().mTokenType != Token::leftBraces) {
				outputQueue.push_back(operatorStack.back());
				operatorStack.pop_back();

				if (operatorStack.size() == 0) {
					std::cout << "PARANTHESIS MISMATCHING"<<std::endl;
					return std::deque<Token>();
				}
			}

			operatorStack.pop_back();
		}

		index++;
	}

	while (!operatorStack.empty()) {
		if (operatorStack.back().mTokenType == Token::leftBraces || operatorStack.back().mTokenType == Token::rightBraces) {
			std::cout << "PARANTHESIS MISMATCH" << std::endl;
			return std::deque<Token>();
		}

		outputQueue.push_back(operatorStack.back());
		operatorStack.pop_back();
	}

	return std::move(outputQueue);
}

Token Token::EvaluateOperator(const Token& T, std::vector<Token>& arguments) {
	Token out;
	out.mTokenType = Token::Number;
	if (T.mTokenSymbol == "+")
		out.mTokenValue = arguments[0].mTokenValue + arguments[1].mTokenValue;
	
	else if (T.mTokenSymbol == "-") 
		out.mTokenValue = arguments[1].mTokenValue - arguments[0].mTokenValue;

	else if (T.mTokenSymbol == "*")
		out.mTokenValue = arguments[0].mTokenValue * arguments[1].mTokenValue;
	
	else if (T.mTokenSymbol == "/") {
		if (arguments[0].mTokenValue == 0.0) {
			std::cout << "Divison by zero!" << std::endl;
			out.mTokenValue = 0.0;
			return out;
		}
		out.mTokenValue = arguments[1].mTokenValue / arguments[0].mTokenValue;
	}

	else if (T.mTokenSymbol == "^")
		out.mTokenValue = std::pow(arguments[1].mTokenValue, arguments[0].mTokenValue);

	else if (T.mTokenSymbol == "_")
		out.mTokenValue = -arguments[0].mTokenValue;

	else if (T.mTokenSymbol == "sqrt")
		out.mTokenValue = std::sqrt(arguments[0].mTokenValue);

	else if (T.mTokenSymbol == "cos")
		out.mTokenValue = std::cos(arguments[0].mTokenValue / 180.0 * M_PI);
		
	else if (T.mTokenSymbol == "sin")
		out.mTokenValue = std::sin(arguments[0].mTokenValue / 180.0 * M_PI);
		
	else if (T.mTokenSymbol == "tan")
		out.mTokenValue = std::tan(arguments[0].mTokenValue / 180.0 * M_PI);
		
	else if (T.mTokenSymbol == "acos")
		out.mTokenValue = std::acos(arguments[0].mTokenValue) * 180.0 / M_PI;

	else if (T.mTokenSymbol == "asin")
		out.mTokenValue = std::asin(arguments[0].mTokenValue) * 180.0 / M_PI;
		
	else if (T.mTokenSymbol == "atan")
		out.mTokenValue = std::atan(arguments[0].mTokenValue) * 180.0 / M_PI;

	else
		std::cout << "Invalid operator '" << std::endl;

	return out;
}

double Token::EvaluateExpression(const std::deque<Token>& tokens) {
	std::vector<Token> operandStack;
	int index = 0;
	while (index < tokens.size()) {
		const Token& T = tokens[index];
		if (T.mTokenType == Token::Number) {
			operandStack.push_back(T);
		}
		else {
			if (operandStack.size() < T.mTokenParameter) {
				std::cout << "Syntax error!" << std::endl;
				return 0.0;
			}
			else {
				std::vector<Token> operands;
				for (int i = 0; i < T.mTokenParameter; i++) {
					operands.push_back(operandStack.back());
					operandStack.pop_back();
				}

				operandStack.push_back(Token::EvaluateOperator(T, operands));
			}
		}
		index++;
	}
	if (operandStack.size() == 1)
		return operandStack.back().mTokenValue;

	std::cout << "Too many values!" << std::endl;
	return 0.0;
}