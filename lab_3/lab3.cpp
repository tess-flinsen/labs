#include "lab3.h"

void ArithmeticProgression::set(int a1, int d1, int n1)
{
    a = a1, d = d1, n = n1;
}

int ArithmeticProgression::getA(){return a;};
int ArithmeticProgression::getD(){return d;};
int ArithmeticProgression::getN(){return n;};
int ArithmeticProgression::get_sum()
{
    return (2*a + d*(n-1)) / 2 * n; // формула суми членів арифметичної прогресії
}

double input_d() //введення і валідація d
{ 
    double d;  
    int error = 0;
    do
    {
        error = 0;
        cout << "Введіть різницю (d): ";
        cin >> d;
        if (d == 0)
        {
            cout << "Некоректний ввід! Різниця не може дорівнювати 0." << endl;
            error = 1;
        }
    } while (error == 1);
    return d;
}

int input_n() //введення і валідація n
{   
    int n;
    int error = 0;
    do
    {
        error = 0;
        cout << "Введіть кількість членів (n): ";
        cin >> n;
        if (n <= 1)
        {
            cout << "Некоректний ввід! Кількість членів повинна бути більше 1." << endl;
            error = 1;
        }
    } while (error == 1);
    return n;
}

void read_progressions(ArithmeticProgression* progressions, int &num_progressions) { //отримання прогресій від користувача
    int i = 0;
    cout << endl << "Введнння геометричних прогресій:" << endl;
    while (true) {
        double a, d;
        int n;
        if (i != 0) 
        {
            cout << endl << "Бажаєте додати ще одну прогресію?" << endl;
            cout << "Enter - так; Esc - ні: ";
            char c = getchar(); 
            if (c == 27) 
            break;
        }
        cout << endl << "Введіть перший член (a): ";
        cin >> a;
        d = input_d();
        n = input_n();
        progressions[i].set(a, d, n);
        i++;
        num_progressions = i; //визначення кількості прогресій (в залежності від вводу користувача)
        cin.ignore();
    }
}

void print_progressions(ArithmeticProgression* progressions, int num_progressions) { //друк прогресій
    
    cout << endl << endl << endl << "Арифметичні прогресії:" << endl;
    for (int i = 0; i < num_progressions; i++) {
        cout << i+1 << endl << "Перший член прогресії: " << progressions[i].getA() << endl;
        cout << "Різниця прогресії: " << progressions[i].getD() << endl;
        cout << "Кількість членів прогресії: " << progressions[i].getN() << endl << endl << endl;
    }
}

void find_max_sum(ArithmeticProgression* progressions, int num_progressions) //пошук найбільшої суми елементів
{
    int max_sum = -1;
    int max_index = -1;
    int indices[num_progressions]; // масив для зберігання індексів прогресій з максимальною сумою елементів
    int count = 0; // лічильник кількості прогресій з максимальною сумою елементів

    for (int i = 0; i < num_progressions; i++) {  // Пошук прогресії з максимальною сумою елементів

        int sum = progressions[i].get_sum();
        if (sum > max_sum) {
            max_sum = sum;
            max_index = i;
        }
    } 
    for (int i = 0; i < num_progressions; i++) {  // Пошук інших прогресій з максимальною сумою елементів
        int sum = progressions[i].get_sum();
        if (sum == max_sum) {
            indices[count] = i;
            count++;
        }
    }

    // Виведення індексів прогресій з максимальною сумою елементів
    if (count > 1)  cout << "Номери прогресій, які мають найбільшу суму (" << max_sum << ") елементів: ";
    else cout <<  "Номер прогресії, яка має найбільшу суму (" << max_sum << ") елементів: ";
    for (int i = 0; i < count; i++) {
        cout << indices[i] + 1;
        if (i != count-1) cout << ", ";
        else cout << "." << endl;
    }
}