#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Break {
    int start_time; //час початку технічної перерви (кількість хвилин від початку доби)
    int end_time; //час кінця технічної перерви (кількість годин від початку доби)
};

void print_file(const string& filename) { //друк вмісту бінарного файла
    ifstream fin(filename, ios::binary);
    if (!fin.is_open()) {
        cerr << "Помилка відкриття файлу.\n";
        return;
    }

    Break b;
    while (fin.read((char*)&b, sizeof(Break))) {
        int start_hours = (int)b.start_time / 60; // обраховуємо кількість годин у записі початку перерви
        int start_minutes = b.start_time % 60; // остача - кількість хвилин у записі початку перерви
        int end_hours = (int)b.end_time / 60; // обраховуємо кількість годин у записі кінця перерви
        int end_minutes = b.end_time % 60; // остача - кількість хвилин у записі кінця перерви

        cout << "Початок перерви: " << start_hours << ":" <<  start_minutes << ", Кінець перерви: " << end_hours << ":" <<  end_minutes << endl;
    }
    
    fin.close();
}

bool are_breaks_overlaping(Break old_break, Break new_break) { //перевірка, чи накладається чи накладається нова перерва на вже наявну
    return (new_break.start_time <= old_break.end_time);
}

bool check_availability(int N,const string& filename ) { //перевірка, чи може касир обслужити всіх N клієнтів, які стоять у черзі
    ifstream infile(filename, ios::binary); //відкриваємо бінарний файл
    if (!infile) {
        cerr << "Помилка відкриття файлу";
        return false;
    }
    int total_break_time = 0;
    Break b;
    while (infile.read((char *)&b, sizeof(b))) {
        total_break_time += b.end_time - b.start_time; //додаємо до загального часу перерви різницю між кінцем і початком кожної перерви
    }
    infile.close();
    int total_time = 24 * 60; //нехай каса цілодобова, тоді загальний робочий час без перерв - 24 год * 60 хв у годині
    int total_service_time = N * 15; //загальний час обслуговування клієнта (кількість клієнтів * 15 хвилин на кожного клієнта)
    return total_service_time <= total_time - total_break_time; //повертає True, якщо час обслуговування кілєнтів менший або рівний часу роботи каси без перерв
}

int get_time(int total_minutes) {
    string input;
    bool valid_input = false;
    int hours, minutes;
    while (!valid_input) {
        cout << "Введіть час y форматі ГГ:XX (наприклад, 15:10 або 03:56) ";
        cin >> input;
        if (input.length() != 5) {
            cout << "Некоректний ввід! Введіть час y форматі ГГ:XX." << endl;
            continue;
        }
        if (input[2] != ':') {
            cout << "Некоректний ввід! Введіть час y форматі ГГ:XX." << endl;
            continue;
        }
        hours = stoi(input.substr(0, 2));
        minutes = stoi(input.substr(3, 2));
        if (hours < 0 || hours >= 24) {
            cout << "Некоректний ввід! Кількість годин має належати проміжку [0;23]." << endl;
            continue;
        }
        if (minutes < 0 || minutes >= 60) {
            cout << "Некоректний ввід! Кількість хвилин має належати проміжку [0;59]." << endl;
            continue;
        }
        valid_input = true;
    }
    total_minutes = hours * 60 + minutes;
    return total_minutes;
}

void append_records(const string& filename) {
    fstream file(filename, ios::binary | ios::app); // відкриваємо файл у режимі додавання даних (binary append mode)
    if (!file) {
        cerr << "Помилка відкриття файлу" << endl;
        return;
    }

    string choice;
    do{
        // запитуємо дані про перерву
        cout << "1- Час початку перерви" << endl;
        int start_time = get_time(start_time); //отримуємо від користувача час початку перерви (валідуємо за допомогою функції get_time())
        cout << "2- Час кінця перерви" << endl;
        int end_time = get_time(end_time); //отримуємо від користувача час кінця перерви (валідуємо за допомогою функції get_time())


        //  Перевіряємо, чи дійсно кінець введеної перерви стається після початку 
        if (start_time >= end_time)
        {
            cout << "Помилка: початок введеної перерви повинен статися раніше її кінця!" << endl;
            cout << "Цей запис НЕ буде додано у файл." << endl;
        }
        else
        {
            Break new_break = { start_time, end_time }; // створюємо новий запис
            // Перевіряємо, чи не накладається нова перерва на вже наявну
            Break existing_break;
            bool is_overlap = false;
            file.seekg(0);
            while (!file.eof()) {
                file.read((char*)&existing_break, sizeof(existing_break));
                if (!file.eof() && are_breaks_overlaping(existing_break, new_break)) {
                    is_overlap = true;
                    break;
                }
            }
            
            // Якщо накладається, виводимо повідомлення про помилку
            if (is_overlap) {
                cout << "Помилка: введена перерва накладається на вже існуючу!" << endl;
                cout << "Цей запис НЕ буде додано у файл." << endl;
                //return;
            }
            else
            {
                // Додаємо нову перерву до файлу
                file.write((char*)&new_break, sizeof(new_break));
            }
        }

        cout << "Бажаєте додати ще один запис?" << endl;
        cout << "Enter - так, 1 - ні: " << endl;
        //getline(cin,choice);
        cin >> choice;
    }while (choice != "1");
    
    file.close();
}

int main() {
    cout << "Введіть ім'я файлу без розширення: ";
    string filename;
    getline(cin,filename);
    filename += ".bin"; //додаємо розширення до імені файлу

    append_records(filename);
    cout << endl;
    print_file(filename);
    cout << endl;
    cout << "Введіть N (кількість клієнтів): ";
    int N;
    cin >> N;
    if (check_availability(N, filename)) cout << "Касир встигне обслужити "<< N << " клієнтів." << endl;
    else  cout << "Касир НЕ встигне обслужити " << N << " клієнтів." << endl;

    return 0;
}

void append_records(const string& filename) {
    fstream file(filename, ios::binary | ios::app); // відкриваємо файл у режимі додавання даних (binary append mode)
    if (!file) {
        cerr << "Помилка відкриття файлу" << endl;
        return;
    }

    string choice;
    do{
        // запитуємо дані про перерву
        cout << "1- Час початку перерви" << endl;
        int start_time = get_time(start_time); //отримуємо від користувача час початку перерви (валідуємо за допомогою функції get_time())
        cout << "2- Час кінця перерви" << endl;
        int end_time = get_time(end_time); //отримуємо від користувача час кінця перерви (валідуємо за допомогою функції get_time())

        // Додаємо нову перерву до файлу
        file.write((char*)&new_break, sizeof(new_break));

        cout << "Бажаєте додати ще один запис?" << endl;
        cout << "Enter - так, 1 - ні: " << endl;
        //getline(cin,choice);
        cin >> choice;
    }while (choice != "1");
     
    file.close();
}