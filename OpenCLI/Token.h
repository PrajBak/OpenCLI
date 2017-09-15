#pragma once
#include<iomanip>
#include<string>
#include<stack>
#include<queue>

namespace myCalc {

	class Token
	{
		int mTokenPriority;
		std::string mTokenSymbol;
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
			mTokenSymbol = "";
		}

		Token stringToToken(std::string str);

	};

}