#include "text_file.h"
#include <fstream>
#include <iostream>
//#include <conio.h>   find out what is conio used for!!! and exchange for my libraries
#include <string>

///text_file

text_file::text_file(const string& name)
{
    if (name.substr(0, name.find(".")).empty())
        throw invalid_argument("Задано пусте ім'я файлу");
    if (name.substr(0, name.rfind(".")).find(".") != string::npos)
        throw invalid_argument("Будь-ласка, задайте ім'я файлу без розширення");
    if (name.find_first_of("&!@#$%^*?/\\=`~\"'") != string::npos)
        throw invalid_argument("Ім'я файлу не може містити символи  &!@#$%^*?/\\=`~\"'");
    if (name.length() > 20)
        throw invalid_argument("Ім'я файлу задовге");

    _filename = name;
    _file.open(_filename);
    if (!_file)
        throw fstream::failure("file can't be open");
}

text_file::~text_file(){
    _file.close();
}

void text_file::endp(){
    _file.seekp(0 , ios::end);
}

void text_file::beginp(){
    _file.seekp(0 , ios::beg);
}

void text_file::endg(){
    _file.seekg(0 , ios::end);
}

void text_file::beging(){
    _file.seekg(0 , ios::beg);
}

bool getline(text_file& file, string& text){
    return (bool)getline(file._file, text);
}

text_file& operator << (text_file& tf, const string &text){
    tf._file<<text;
    return tf;
}

text_file& operator >> (text_file& tf, string& text){
    tf._file >> text;
    return tf;
}

void text_file::close(){
    _file.close();
}
