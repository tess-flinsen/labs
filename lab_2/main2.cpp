#include "lab2.h"

int main() {
    
    int choice = get_choice();
    string filename = get_filename();

    if (choice == 2) 
    {
        print_file(filename);
        cout << "Бажаєте додати записи до файлу?\n"  << "1 - так, 2 - ні: ";
        cin >> choice;
        if (choice == 1) 
        {   append_records(filename);
            print_file(filename);}
    }
    else 
    {   append_records(filename);
        print_file(filename);}

    check_availability(filename);
    return 0;
}