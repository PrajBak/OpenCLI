#include"Token.h"
#include<Windows.h>
#include<experimental\filesystem>
#define MAX_BUFFER_LENGTH 100

bool vectorToString(std::string& myString, std::vector<std::string>& myVector);
void stringToString(std::string& str);

using namespace myCalc;

int main()
{

	DWORD nBufferLength = MAX_BUFFER_LENGTH;
	char szCurrentDirectory[MAX_BUFFER_LENGTH + 1];
	szCurrentDirectory[MAX_BUFFER_LENGTH] = '\0';

	bool running = true;
	std::cout << std::setw(55) << "OpenCLI" << std::endl << std::endl;
	std::cout << "USE THE COMMAND 'manual' (without the colons) TO GET STARTED"<<std::endl<<std::endl<<std::endl;
	while (running) {
		std::string input;
		GetCurrentDirectory(nBufferLength, szCurrentDirectory);
		std::cout <<szCurrentDirectory<< "> ";

		std::getline(std::cin, input);

		if (input.empty())
			continue;

		std::stringstream parse(input);

		std::vector<std::string> symbols;

		std::string symbol;
		while (std::getline(parse, symbol, ' ')) {
			symbols.push_back(symbol);
		}

		if (symbol == "quit" || symbol == "exit") {
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
		else if (symbols[0] == "chdir" || symbols[0] == "cd") {
			std::string myString;
			vectorToString(myString, symbols);
			DWORD ftyp = GetFileAttributesA(myString.c_str());
			if (ftyp == INVALID_FILE_ATTRIBUTES) 
				std::cout << "[ERROR] : ENTER A VALID DIRECTORY" << std::endl;
			else
				SetCurrentDirectory(myString.c_str());
		}

		else if (symbols[0] == "ls") {
			auto lastSlash = 0;
			HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
			std::string path = szCurrentDirectory;
			std::string myPath;
			for (auto & p : std::experimental::filesystem::directory_iterator(path)) {
				myPath = p.path().string();
				std::cout<<std::endl;
				for (auto i = myPath.size() - 1; i >= 0; i--) {
					if (myPath[i] == '\\') {
						lastSlash = i;
						break;
					}
				}

				lastSlash++;
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
				myPath.erase(0, lastSlash);
				std::cout << "\t\t\t\t" << myPath << std::endl;
			}
			std::cout<<std::endl;
			SetConsoleTextAttribute(hStdOut, 15);
		}
		
		else if (symbols[0] == "pwd") {
			std::cout << "WORKING DIRECTORY : " << szCurrentDirectory << std::endl;
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