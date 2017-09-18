#include"Token.h"

bool vectorToString(std::string& myString, std::vector<std::string>& myVector);
void stringToString(std::string& str);

using namespace myCalc;

int main()
{
	bool running = true;
	std::cout << std::setw(55) << "OpenCLI" << std::endl;
	std::cout << "USE THE COMMAND 'manual' (without the colons) TO GET STARTED"<<std::endl<<std::endl;
	while (running) {
		std::string input;
		std::cout << "> ";

		std::getline(std::cin, input);

		if (input.empty())
			continue;

		std::stringstream parse(input);

		std::vector<std::string> symbols;

		std::string symbol;
		while (std::getline(parse, symbol, ' ')) {
			symbols.push_back(symbol);
		}

		if (symbol == "quit") {
			running = false;
		}

		else if (symbols[0] == "") {
			continue;
		}
		else if (symbols[0] == "notepad") {
			system("notepad");
		}
		else if (symbols[0] == "paint") {
			system("mspaint");
		}
		else if (symbols[0] == "add") {
			float a = std::stof(symbols[1]);
			float b = std::stof(symbols[2]);
			std::cout << "Result: " << (a + b) << std::endl;
		}
		else if (symbols[0] == "manual") {
			system("notepad manual.txt");
		}
		else if (symbols[0] == "shutdown") {
			system("shutdown -s");
		}
		else if (symbols[0] == "calculate") {

			std::string myString;
			if (vectorToString(myString, symbols))
			{
				stringToString(myString);
				const std::vector<Token> myVec = Token::Tokenise(myString);
				std::deque<Token> myQueue = Token::shuntingYard(myVec);
				std::cout << "RESULT : "<< Token::EvaluateExpression(myQueue)<<std::endl;
			}
			
			else std::cout << "[ERROR] : ENTER AN EXPRESSION NEXT TIME" << std::endl;
		}
	}
	return 0;
}

// FUNCTION TO CONVERT A VECTOR OF STRINGS BACK TO A STRING(WILL NOT COPY THE FIRST ELEMENT)
bool vectorToString(std::string& myString, std::vector<std::string>& myVector)
{
	auto length = myVector.size();
	if (length == 0 || length == 1)
		return false;

	for (auto i = 1; i<length; ++i)
		myString += myVector[i];
	return true;
}

void stringToString(std::string& str) 
{
	for (auto i = 0; i < str.size();){
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^' || str[i] == '(' || str[i] == ')') {
			if (i == 0) 			
				str.insert(i + 1, 1, ' ');
			else {
				str.insert(i + 1, 1, ' ');
				str.insert(i, 1, ' ');
			}

			i += 2;
		}
		i++;
	}

	char symbol = ' ';

	str.erase(
		std::unique(
			str.begin(),
			str.end(),
			[symbol](char l, char r) -> bool {
		return (l == symbol) && (l == r);
			}
		),
		str.end()
			);
}