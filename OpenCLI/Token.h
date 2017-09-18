#pragma once
#include<iomanip>
#include<iostream>
#include<string>
#include<stack>
#include<deque>
#include<vector>
#include<sstream>

namespace myCalc {

	class Token
	{
	public:
		int mTokenPriority;
		double mTokenValue;
		int mTokenParameter;
		char mTokenSymbol;
		enum tokenType
		{
			Nothing,
			Operator,
			Number,
			leftBraces,
			rightBraces
		};
		enum tokenAssociavity
		{
			Left,
			Right
		};
		tokenType mTokenType;
		tokenAssociavity mTokenAssoc;

	public:

		Token()
		{
			mTokenType = Nothing;
			mTokenAssoc = Left;
			mTokenPriority = 0;
			mTokenValue = 0;
			int mTokenParameter = 0;
		}

		static Token stringToToken(const std::string& str);
		static std::vector<Token> Tokenise(std::string& expression);
		static Token EvaluateOperator(const Token& T, std::vector<Token>& arguments);
		static double EvaluateExpression(const std::deque<Token>& tokens);
		static std::deque<Token> shuntingYard(const std::vector<Token>& tokens);
	};

}