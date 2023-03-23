#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <string>

using namespace std;

bool isFileExisting(const string& fileName);
bool isFileEmpty(const string& fileName);

void processFile(const string& fileName);
void processFile(const char* fileName);

void printFile(const string& filename);
void printFile(const char* filename);

string shiftString(string s, int k);
char* shiftString(const char* s, int k);

void encryptFile(const string& fileName);
void encryptFile(const char* fileName);

int countWords(const string& str, const char* delimiters);
int countWords(const char* str, const char* delimiters);

string findSecondToLastWord(const string& str, const char* delimiters);
char* findSecondToLastWord(const char* str, const char* delimiters);

string findSecondWord(const string& str, const char* delimiters);
char* findSecondWord(const char* str, const char* delimiters);

int findIndex(const string& str, const string& word);
int findIndex(char* str, char* word);

void modifyFile(const string& inputFileName, const string& outputFileName);
void modifyFile(const char* inputFileName, const char* outputFileName);