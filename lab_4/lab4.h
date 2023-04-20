#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

class ComplexNumber {

    double p_modul; // модуль числа
    double q_argument; // аргумент числа

    public:

        //конструктори
        ComplexNumber();
        ComplexNumber(double modul, double argument = 0);
        ComplexNumber(const ComplexNumber& other);

        //геттери
        double getModul();
        double getArgument();

        //методи
        void toAlgebraicForm(double& realPart, double& imaginaryPart) const;
        void fromAlgebraicForm(double& realPart, double& imaginaryPart);
        void print(int i);

        //перевантажені оператори
        ComplexNumber operator+(const ComplexNumber& other);
        ComplexNumber& operator++(); //префіксний
        ComplexNumber operator++(int); //постфіксний
};