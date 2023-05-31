#ifndef MY_FILE_H
#define MY_FILE_H


#include <fstream>

class MyException : public std::exception
{
	private:
	const char* msg;

	public:
		MyException(const char* msg_);
		virtual ~MyException();

		const char* what() const noexcept override;
};

class MyFile
{
	private:
		const unsigned int segment;
		const char* path;
		std::ifstream fin;
		std::ofstream fout;
		char* data;
		const char* data_str;
		unsigned int size;
		bool isRw;

		void data_resize(int i);
		void write(const char* data_ = "");
		void read();

	public:
		MyFile(const char* path_, bool isRw_ = false, const unsigned int segment_ = 1024);
		virtual ~MyFile();
	
	const char* to_str();
};

#endif