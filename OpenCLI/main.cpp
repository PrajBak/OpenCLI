#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<cstdio>
#include<sstream>


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

		if (symbols[0] == "quit") {
			running = false;
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
	}
	return 0;
}