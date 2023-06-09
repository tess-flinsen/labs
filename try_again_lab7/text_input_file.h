#ifndef TEXT_INPUT_FILE_H
#define TEXT_INPUT_FILE_H

#include <fstream>
#include "file.h"

class text_input_file:public file{
    ifstream _file;
    friend class text_file;
    friend class text_output_file;
public:
    text_input_file(const string& name);
    ~text_input_file();

    void endg();
    void beging();

    friend bool getline(text_input_file& file, string& text);

    friend text_input_file& operator >> (text_input_file& tf, string &text);

    void close();
};

#endif // TEXT_INPUT_FILE_H

