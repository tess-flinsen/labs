#include "lab5.h"

int main()
{
    srand(time(0));
    int m, n;
    cout << "Введіть кількість двійкових чисел m (1 - 30): ";
    m = take_input(m);
    cout << "Введіть кількість шістнадцяткових чисел n (1 - 30): ";
    n = take_input(n);

    TIntNumber2 *numbers_2 = new TIntNumber2[m];
    TIntNumber16 *numbers_16 = new TIntNumber16[n];

    PrintBinMatrix(numbers_2, m);
	PrintHexMatrix(numbers_16, n);


    TIntNumber2 sum_2 = numbers_2[0].FindSum(numbers_2, m);
    TIntNumber16 sum_16 = numbers_16[0].FindSum(numbers_16, n);
    cout << endl << endl << "Сума двійкових чисел: ";
    sum_2.print();
    cout << endl << endl <<  "Сума шістнадцяткових чисел: ";
    sum_16.print();

    int decimal = sum_16.getNumber();
    TIntNumber2 sum_16_converted;
    sum_16_converted.setNumber(decimal);
    cout << "Сума шістнадцяткових чисел: ";
    sum_16_converted.print();
    cout << endl << endl;

    if (sum_2 < sum_16_converted)
    {
        cout << "РЕЗУЛЬТАТ: Сума шістнадцяткових більше за суму двійкових.\n\n";
    }
    else cout << "РЕЗУЛЬТАТ: Сума двійкових більше за суму шістнадцяткових.\n\n";

    delete[] numbers_2;
    delete[] numbers_16;

    return 0;
}