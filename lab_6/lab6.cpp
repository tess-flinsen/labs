#include "lab6.h"

void print_menu()
{
    cout << endl << endl << "Meню:\n";
        cout << "1. Очистка множини\n";
        cout << "2. Перевірка приналежності елемента множині\n";
        cout << "3. Включення нового елемента в множину\n";
        cout << "4. Oб'єднання двох множин\n";
        cout << "5. Встановлення ітератора на початок множини\n";
        cout << "6. Перевірка кінця множини\n";
        cout << "7. Доступ до значенння поточного елемента множини\n";
        cout << "8. Перехід до наступного елемента множини\n";
        cout << "0. Вихід\n\n";
}
int take_input(int min, int max)
{
    int choice;
    while (true) {
        cout << "Введіть свій вибір: ";
        cin >> choice;
        cin.ignore();
        if (cin.fail() || choice < min || choice > max) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Некоректний ввід! Введіть значення від 1 до 3\n";
        } else break;
    }
    return choice;
}