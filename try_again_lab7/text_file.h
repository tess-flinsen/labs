#ifndef TEXT_FILE_H
#define TEXT_FILE_H

#include <string>
#include <fstream>
#include "file.h"

using namespace std;

class text_file;
class text_input_file;


class text_file : public file{
    fstream _file;
    friend class text_output_file;
    friend class text_input_file;
public:
    text_file(const string &name);
    //text_file(const string& name, text_file &other);
    //text_file(const string& name, text_file &other, const string& word);
    ~text_file();

    void endp();
    void beginp();

    void endg();
    void beging();

    friend bool getline(text_file& file, string& text);

    friend text_file& operator >> (text_file& tf, string& text);
    friend text_file& operator << (text_file& tf, const string &text);

    void close();
};


#endif // TEXT_FILE_H
