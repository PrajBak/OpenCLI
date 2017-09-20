#pragma once
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

namespace OpenCLI {
	namespace FileMan {

		class FileMan {
		public:
			std::string name;
			long size;

		public:
			FileMan();
			FileMan(char* fileName);
			bool init();
		};
	}
}
