#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;

class TIntNumber
{
    protected:
        int number;
        int base;
    public:
        TIntNumber();
        virtual void Convert() = 0;
        virtual bool operator<(const TIntNumber& other) const;
        int getNumber() const {return number;}
        void setNumber(int num){number = num; Convert();}
};

class TIntNumber2: public TIntNumber
{
	string binary;
    public:
        TIntNumber2();
        void Convert();
        void print();
        bool operator<(const TIntNumber2& other) const;
        TIntNumber2 operator+(const TIntNumber2& other) const;
        TIntNumber2 FindSum(const TIntNumber2* A, int count);
};

class TIntNumber16 : public TIntNumber
{
	string hex;
    public:
        TIntNumber16();
        void Convert();
        void print();
        bool operator<(const TIntNumber16& other) const;
        TIntNumber16 operator+(const TIntNumber16& other);
        TIntNumber16 FindSum(const TIntNumber16* A, int count);
};

void printLine();
void PrintBinMatrix(TIntNumber2* A, int size);
void PrintHexMatrix(TIntNumber16* A, int size);
int take_input(int num);