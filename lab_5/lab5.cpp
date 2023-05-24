#include "lab5.h"

TIntNumber::TIntNumber()
{
    number = 1 + rand() % 100;
    base = 10;
}
bool TIntNumber::operator<(const TIntNumber& other) const {
            return number < other.getNumber();
}


TIntNumber2::TIntNumber2()
{
    base = 2;
    Convert();
}
void TIntNumber2::Convert()
{
    binary = "";
    if (number == 0) {
         binary = "0";
    }
    int decimal = number;
    while (decimal > 0) {
        int remainder = decimal % 2;
        binary = to_string(remainder) + binary;
        decimal /= 2;
    }
}
void TIntNumber2::print()
{
    int buff = (20 - binary.length()) / 2 ;
    cout << "|" << setw((buff + binary.length() + binary.length() % 2)) << binary << setw(buff) << '|' << setw(12) << number << setw(7) << '|' << endl;
}
bool TIntNumber2::operator<(const TIntNumber2& other) const {
            return number < other.getNumber();
        }
TIntNumber2 TIntNumber2::operator+(const TIntNumber2& other) const {
    TIntNumber2 temp;
    int sum = number + other.getNumber();
    temp.setNumber(sum);
    temp.Convert();
    return temp;
}
TIntNumber2 TIntNumber2::FindSum(const TIntNumber2* A, int count) {
    TIntNumber2 temp;
    temp.setNumber(0);
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum = sum + A[i].getNumber();
    }
    temp.setNumber(sum);
    return temp;
}  


TIntNumber16::TIntNumber16()
{
    base = 16;
    Convert();
}
void TIntNumber16::Convert()
{
    hex = "";
    int copy = number;
    if (copy == 0) {
        hex += "0";
    }
    while (copy > 0) {
        int digit = copy % 16;
        if (digit < 10) {
            hex = to_string(digit) + hex;
        }
        else {
            hex = char(digit - 10 + 'A') + hex;
        }
        copy /= 16;
    }
}
void TIntNumber16::print()
{
    int buff = (20 - hex.length()) / 2;
    cout << "|" << setw((buff + hex.length() + hex.length() % 2)) << hex << setw(buff) << '|' << setw(12) << number << setw(7) << '|' << endl;
}
bool TIntNumber16::operator<(const TIntNumber16& other) const {
            return number < other.getNumber();
        }
TIntNumber16 TIntNumber16::operator+(const TIntNumber16& other)  {
    TIntNumber16 temp;
    int sum;
    sum = number + other.getNumber();
    temp.setNumber(sum);
    return temp;
}
TIntNumber16 TIntNumber16::FindSum(const TIntNumber16* A, int count) {
    TIntNumber16 sum; 
    sum.setNumber(0);
    for (int i = 0; i < count; i++) {
        sum = sum + A[i];
    }
    sum.Convert();
    return sum;
}
void printLine()
{
    for (int i = 0; i < 40; i++)
    {
        if (i == 0 || i == 40 / 2 || i == 40)
        {
            cout << "+";
        }
        else {
            cout << "-";
        }
    }
    cout << endl;
}

void PrintBinMatrix(TIntNumber2* A, int size)
{
    cout << endl;
    printLine();
    cout << "|" << setw(21) << "Двійкова" << setw(7) << '|' << setw(23) << "Десяткова" << setw(5) << '|' << endl;
    printLine();

    for (int i = 0; i < size; i++)
    {
        A[i].print();
        printLine();
    }
} 

void PrintHexMatrix(TIntNumber16* A, int size)
{
    cout << endl;
    printLine();
    cout << "|" << setw(14) << "  Шістнадцяткова" << setw(4) << '|' << setw(15) << "     Десяткова" << setw(5) << '|' << endl;
    printLine();

    for (int i = 0; i < size; i++)
    {
        A[i].print();
        printLine();
    }
}

int take_input(int num)
{
    int error = 0;
    do
    {
        error = 0;
        cin >> num;
        if (num < 1 || num > 30)
        {
            cout << "Некоректний ввід! Значення повинно бути цілим числом в діапазоні від 1 до 30." << endl;
            error = 1;
        }
    } while (error == 1);
    return num;
}
