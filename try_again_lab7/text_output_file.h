#ifndef TEXT_OUTPUT_FILE_H
#define TEXT_OUTPUT_FILE_H

#include <fstream>
#include "file.h"
#include "text_file.h"

using namespace std;

class text_output_file:public file{
    ofstream _file;
    friend class text_file;
    friend class text_input_file;
public:
    text_output_file(const string &name);
    text_output_file(const string& name, text_file &other);
    text_output_file(const string& name, text_file &other, const string& word);
    ~text_output_file();

    void endp();
    void beginp();

    friend text_output_file& operator << (text_output_file& tf, const string &text);

    void close();
};
#endif // TEXT_OUTPUT_FILE_H
