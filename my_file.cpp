// #ifdef DEB_CONST
// #define DEB_RAW
#ifdef DEB_RAW
#include <iostream>
#endif

#include <string>
#include <cstring>
#include "my_file.h"


static const std::string err_open_file_msg = "Error opening input file: ";
static const std::string err_write_file_msg = "Error opening for write file: ";
static const std::string err_buzzy_data = "Error value data buzzy.";

class MyException : public std::exception
{
    private:
    const std::string msg;

    public:
        MyException(const std::string msg_) : msg(msg_){}
        virtual ~MyException(){}

        const char* what() const noexcept override
        {
            return msg.c_str();
        }
};

MyFile::MyFile(const char* path_, std::string str_, const unsigned int segment_) :
    path(path_),
    segment(segment_),
    str(str_),
    data(nullptr),
    size(0),
    isRw(false)
{
    if (str.length() != 0)
    {
        write();    
    }
    else
    {
        if(exist()) read();
    }

#ifdef DEB_CONST
    std::cout << "MyFile object build. Size = " << size << '\n';
#endif
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
        for (int j = 0; j <= i; ++j)
        {
            temp[j] = data[j];
        }
        delete[] data;
        data = temp;
    }
}

void MyFile::write()
{
    fout.open(path);
    
    if (fout.fail())
    {
        throw MyException(err_write_file_msg);
    }

    size = str.length();
    data_str = str.c_str();
    data = new char[segment]{};
    data_resize(size);

    for (int i = 0; i <= size; ++i)
    {
        data[i] = data_str[i];
        fout << data_str[i];
    }

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

            fin.get(data[i]);
            ++i;
        }

        //size = i + 1;
        size = i;
        data[size] = 0;
    }
    fin.close();
    data_str = data;

#ifdef DEB_RAW
    std::cout << "!!! data_str: " << data_str << "\n!!! data_str end.\n";
#endif

    str = data_str;
}

bool MyFile::exist()
{
    if(stat(path, &sb) == 0) return true;

    return false;
}

void MyFile::set_str(const char* str_)
{
    if(data == nullptr)
    {
        str = str_;
        write();
    }
    else
    {
        // throw MyException(err_buzzy_data);
        delete data;
        data = nullptr;
        size = 0;
        str = str_;
        write();
    }
}

std::string MyFile::to_str(const char divider)
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
        if (data[i] == '\n' || data[i] == '\t')
        {
            temp[i] = divider;
        }
        else
        {
            temp[i] = data[i];
        }
    }

    temp[size] = 0;
    data_str = temp;

    return data_str;
}

std::vector<std::string> MyFile::to_words()
{
    std::string word = "";
    std::vector<std::string> words;

    for (unsigned int i = 0; i < size; ++i)
    {
        bool div = data[i] == ' ' || data[i] == '\n' || data[i] == '\t';
        //std::cout << "Is divider: " << div << '\n';

        if (div)
        {
            words.push_back(word);
            word.clear();
        }
        else 
        {
            // Append the char to the temp string.
            word += data[i]; 
        }

    }
    
    //words.push_back(word);

    return words;
}

std::string MyFile::raw_str()
{

#ifdef DEB_RAW
    std::cout << "!!! File raw text: " << str.c_str() << '\n' ;
    std::cout << "!!! End file raw text.\n";
#endif

    return str;
}