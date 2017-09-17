#include<iostream>
#include<iomanip>
#include"Token.h"
#include<cstdio>
#include<sstream>

bool vectorToString(std::string& myString, std::vector<std::string>& myVector);

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
			vectorToString(myString, symbols);
			Token token;
			stringToToken(myString);
		}
	}
	return 0;
}

// FUNCTION TO CONVERT A VECTOR OF STRINGS BACK TO A STRING(WILL NOT COPY THE FIRST ELEMENT)
bool vectorToString(std::string& myString, std::vector<std::string>& myVector)
{
	auto length = myVector.size();

	if (length == 1)
		return false;

	for (auto i = 1; i<length; ++i)
	{
		myString += myVector[i];
		if (i != (length - 1))
			myString += " ";
	}

	return true;
}