#ifndef FILE_H
#define FILE_H

#include <string>

class text_file;
class text_output_file;
class text_input_file;

using namespace std;

class file{
protected:
    string _filename;
public:
    virtual void close() = 0;
};

#endif // FILE_H
