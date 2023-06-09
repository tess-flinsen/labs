#include "text_output_file.h"

///text_output_file

text_output_file::text_output_file(const string& name)
{
    if (name.substr(0, name.find(".")).empty())
        throw invalid_argument("Задано пусте ім'я файлу");
    if (name.find_first_of("&!@#$%^*?/\\=`~\"'") != string::npos)
        throw invalid_argument("Ім'я файлу не може містити символи &!@#$%^*?/\\=`~\"'");
    if (name.length() > 20)
        throw invalid_argument("Ім'я файлу задовге");
    if (name.substr(0, name.rfind(".")).find(".") != string::npos)
        throw invalid_argument("Будь-ласка, задайте ім'я файлу без розширення");

    _filename = name;
    _file.open(_filename);
    if (!_file)
        throw fstream::failure("file can't be created");

}

text_output_file::text_output_file(const string& name, text_file &other){

    if (name.substr(0, name.find(".")).empty())
        throw invalid_argument("Задано пусте ім'я файлу");
    if (name.find_first_of("&!@#$%^*?/\\=`~\"'") != string::npos)
        throw invalid_argument("Ім'я файлу не може містити символи &!@#$%^*?/\\=`~\"'");
    if (name.length() > 20)
        throw invalid_argument("Ім'я файлу задовге");
    if (name.substr(0, name.rfind(".")).find(".") != string::npos)
        throw invalid_argument("Будь-ласка, задайте ім'я файлу без розширення");

    _filename = name;
    _file.open(_filename);
    if (!_file)
        throw fstream::failure("file can't be created");


    if (!other._file)
        throw fstream::failure("file can't be open");

    string text;

    other._file.seekg(0 , ios::beg);
    while (getline(other._file, text))
        _file<<text<<"\n";

}

text_output_file::text_output_file(const string& name, text_file &other, const string& word){

    if (name.substr(0, name.find(".")).empty())
        throw invalid_argument("Задано пусте ім'я файлу");
    if (name.find_first_of("&!@#$%^*?/\\=`~\"'") != string::npos)
        throw invalid_argument("Ім'я файлу не може містити символи &!@#$%^*?/\\=`~\"'");
    if (name.length() > 20)
        throw invalid_argument("Ім'я файлу задовге");
    if (name.substr(0, name.rfind(".")).find(".") != string::npos)
        throw invalid_argument("Будь-ласка, задайте ім'я файлу без розширення");

    _filename = name;
    _file.open(_filename);
    if (!_file)
        throw fstream::failure("file can't be created");


    if (!other._file)
        throw fstream::failure("file can't be open");

    string text;

    other._file.seekg(0 , ios::beg);
    while (getline(other._file, text)){
        if (text.find(word) != string::npos)
            _file<<text<<"\n";
    }


}

text_output_file::~text_output_file(){
    this->close();
}

void text_output_file::endp(){
    _file.seekp(0 , ios::end);
}

void text_output_file::beginp(){
    _file.seekp(0 , ios::beg);
}

text_output_file& operator << (text_output_file& tf, const string &text){
    tf._file<<text;
    return tf;
}

void text_output_file::close(){
    _file.close();
}
