#include <iostream>
#include <cstring>
#include "my_file.h"



static const char* err_open_file_msg = "Error opening input file: ";
static const char* err_write_file_msg = "Error opening for write file: ";

MyException::MyException(const char* msg_) :
    msg(msg_)
{}

MyException::~MyException()
{}

const char* MyException::what() const noexcept
{
    return msg;
}

MyFile::MyFile(const char* path_, bool isRw_, const unsigned int segment_) :
    path(path_),
    segment(segment_),
    isRw(isRw_)
{
    if (isRw)
    {
        write();
    }
    else
    {
        read();
    }

    std::cout << "MyFile object build.\n";
}

MyFile::~MyFile()
{
    delete[] data;
    data = nullptr;
}

void MyFile::data_resize(int i)
{
    if (i >= segment)
    {
        char* temp = new char[i + segment];
        for (int j = 0; j >= i; ++j)
        {
            temp[j] = data[j];
        }
        delete[] data;
        data = temp;
    }
}

void MyFile::write(const char* data_)
{
    fout.open(path);
    
    if (fout.fail())
    {
        throw MyException(err_write_file_msg);
    }

    data = new char[segment];
    int i = 0;
    while (data_[i] != 0)
    {
        data_resize(i);

        data[i] = data_[i];
        fout << data[i];
        ++i;
    }

    size = i + 1;
    fout.close();
}

void MyFile::read()
{
    fin.open(path);
    if (fin.fail())
    {
        throw MyException(err_open_file_msg);
    }
    else
    {
        data = new char[segment]{};
        
        unsigned int i = 0;
        while (!fin.eof())
        {
            data_resize(i);

            fin >> data[i];
            ++i;
        }

        size = i + 1;
    }
    fin.close();
}

const char* MyFile::to_str()
{
    // std::cout << "Devider: ";
    // int i = 0;

    // while (devider[i] == 0)
    // {
    //     std::cout << devider[i];
    // }
    // std::cout << "\n";

    // std::cout << "Char string: ";
    // for (int i = 0; i <= size; ++i)
    // {
    //     std::cout << data[i];
    //     if (data[i] == 0)
    //     {
    //         return "End char string.";
    //     }
    // }
    // std::cout << "\n";

    unsigned int size_str = size + 1;
    char* temp = new char[size_str];

    for (int i = 0; i < size; ++i)
    {
        temp[i] = data[i];
    }

    temp[size] = 0;
    data_str = temp;

    return data_str;
}