#include "text_input_file.h"

///text_input_file

text_input_file::text_input_file(const string& name){

    if (name.substr(0, name.find(".")).empty())
        throw invalid_argument("Задано пусте ім'я файлу");
    if (name.find_first_of("&!@#$%^*?/\\=`~\"'") != string::npos)
        throw invalid_argument("Ім'я файлу не може містити символи  &!@#$%^*?/\\=`~\"'");
    if (name.length() > 20)
        throw invalid_argument("Ім'я файлу задовге");
    if (name.substr(0, name.rfind(".")).find(".") != string::npos)
        throw invalid_argument("Будь-ласка, задайте ім'я файлу без розширення");

    _filename = name;
    _file.open(_filename);
    if (!_file)
        throw fstream::failure("file can't be created");
}

text_input_file::~text_input_file(){
    _file.close();
}

void text_input_file::endg(){
    _file.seekg(0 , ios::end);
}

void text_input_file::beging(){
    _file.seekg(0 , ios::beg);
}


bool getline(text_input_file& file, string& text){
    return (bool)getline(file._file, text);
}

text_input_file& operator >> (text_input_file& tf, string &text){
    tf._file>>text;
    return tf;
}

void text_input_file::close(){
    _file.close();
}
