#include <cstring>
#include "my_file.h"



class MyException : public std::exception
{
    private:
    const char* msg;

    public:
        MyException(const char* msg_) : msg(msg_){}
        virtual ~MyException(){}

        const char* what() const noexcept override
        {
            return msg;
        }
};

MyFile::MyFile(const char* path_) :
    path(path_)
{
    fin.open(path);
    if (fin.fail())
    {
        char* err_open_file_msg = "Error opening input file: ";
        strcat(err_open_file_msg, path);
        throw MyException(err_open_file_msg);
    }
    
}