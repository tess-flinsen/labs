#include "lab4.h"

// конструктор за замовчуванням
ComplexNumber::ComplexNumber() {p_modul = 0; q_argument = 0;}

// конструктор із заданням модуля та аргументу (за замовчуванням аргумент 0)
ComplexNumber::ComplexNumber(double modul, double argument) : p_modul(modul), q_argument(argument) {}

// конструктор копіювання
ComplexNumber::ComplexNumber(const ComplexNumber& other) : p_modul(other.p_modul), q_argument(other.q_argument) {}


// геттери
double ComplexNumber::getModul() { return p_modul; }
double ComplexNumber::getArgument() { return q_argument; }


// методи
void ComplexNumber::toAlgebraicForm(double& realPart, double& imaginaryPart) const{ //переведення числа в алгебраїчну форму
    realPart = p_modul * cos(q_argument);
    imaginaryPart = p_modul * sin(q_argument);
}
void ComplexNumber::fromAlgebraicForm(double& realPart, double& imaginaryPart)  { //переведення числа в показникову форму
    p_modul = sqrt(realPart * realPart + imaginaryPart * imaginaryPart);
    q_argument = atan2(imaginaryPart, realPart);
}
void ComplexNumber::print(int i) //друк алгебраїчної та комплексної форм комплексного числа (і - номер числа за порядком)
{
    double real, imag;
    toAlgebraicForm(real, imag);
    cout << "| Номер числа |  Алгебраїчна форма |    Показникова форма   |" << endl;
    cout << "|      " << i <<"      |";
    cout << " " << setprecision(5) << fixed << real << " + " << imag << "i |";  
    cout << " " << p_modul << " * e^(" << q_argument << "i) |" << endl;
    cout << " -----------------------------------------------------------" << endl;
}

//перевантажені оператори
ComplexNumber ComplexNumber::operator+(const ComplexNumber& other) { //обчислення суми двох комплексних чисел
    double realPart, imaginaryPart;
    toAlgebraicForm(realPart, imaginaryPart);

    double otherRealPart, otherImaginaryPart;
    other.toAlgebraicForm(otherRealPart, otherImaginaryPart);

    double finalReal = realPart + otherRealPart;
    double finalImaginary = imaginaryPart + otherImaginaryPart;
    ComplexNumber Ksum;
    Ksum.fromAlgebraicForm(finalReal, finalImaginary);
    return Ksum;
}

ComplexNumber& ComplexNumber::operator++() { // префіксний ++ для інкрементування дійсної частини числа
    double realPart, imaginaryPart;
    toAlgebraicForm(realPart, imaginaryPart);
    ++realPart;
    fromAlgebraicForm(realPart, imaginaryPart);
    return *this;
}

ComplexNumber ComplexNumber::operator++(int) { // постфіксний ++ для інкрементування уявної частини числа
    ComplexNumber old(*this); 
    double realPart, imaginaryPart;
    toAlgebraicForm(realPart, imaginaryPart);
    ++imaginaryPart;
    fromAlgebraicForm(realPart, imaginaryPart);
    return old; // повернення початкового значення об'єкта
}

