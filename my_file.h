#ifndef MY_FILE_H
#define MY_FILE_H


#include <fstream>

class MyFile
{
	private:
		const char* path;
		std::ifstream fin;
		std::ofstream fout;
		char* data;
		unsigned int size;

	public:
		MyFile(const char* path_);
		virtual ~MyFile();
	
	const char* file_to_chars();
};

#endif