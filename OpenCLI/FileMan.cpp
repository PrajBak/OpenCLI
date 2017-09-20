#include"FileMan.h"

using namespace OpenCLI::FileMan;

FileMan::FileMan() {
	name = "NA";
	size = 0;
}

FileMan::FileMan(char* fileName) {
	name = fileName;
	std::fstream f;
	f.open(name, std::ios::in);
	f.seekg(std::ios::end);
	size = f.tellg();
	f.close();
}

bool FileMan::init() {

	std::stringstream fileStream;
	std::fstream f1;
	f1.open(name, std::ios::in | std::ios::out);

	if (!f1.good())
		return false;

	fileStream << f1.rdbuf();
	
	std::string fileString = fileStream.str();

	std::cout << fileString << std::endl << std::endl;

	f1.close();

	return true;
}