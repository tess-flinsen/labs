#include "lab6.h"

int main() 
{
    cout << endl << "Оберіть тип даних, множину яких бажаєте створити:\n";
    cout << "1. Integer\t2. Char\n";
    int choice;
    choice = take_input(1, 2);
    switch (choice) {
        case 1: {
            HashSet<int> set;
            handle_menu(set);
            break;
        }
        case 2: {
            HashSet<char> set;
            handle_menu(set);
            break;
        }
    }
    return 0;
}