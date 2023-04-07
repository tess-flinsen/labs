#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct Break{int start_time, end_time;};
void print_file(const string& filename);
int get_time();
void check_availability(const string& filename);
void add_break(fstream& file);
void append_records(const string& filename);
string get_filename();
int get_choice();