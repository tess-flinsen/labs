#include "lab2.h"

void print_file(const string& filename) { //друк вмісту бінарного файла
    ifstream fin(filename, ios::binary);
    if (!fin.is_open()) {
        cerr << "Помилка відкриття файлу.\n";
        return;
    }
    cout << "Вміст файлу: " << endl;
    Break b;
    while (fin.read((char*)&b, sizeof(Break))) {
        int start_hours = (int)b.start_time / 60; // обраховуємо кількість годин у записі початку перерви
        int start_minutes = b.start_time % 60; // остача - кількість хвилин у записі початку перерви
        int end_hours = (int)b.end_time / 60; // обраховуємо кількість годин у записі кінця перерви
        int end_minutes = b.end_time % 60; // остача - кількість хвилин у записі кінця перерви

        //вивід вмісту у форматі ГГ:ХХ - ГГ:ХХ
        cout <<  setfill('0') << setw(2) <<  start_hours <<  ":" <<  setfill('0') << setw(2) << start_minutes;
        cout << " - " <<  setfill('0') << setw(2) <<  end_hours <<  ":" <<  setfill('0') << setw(2) << end_minutes << endl;
    }
    
    cout << endl << endl;
    fin.close();
}

int get_time() { //введення та валідація введеного часу
    int total_minutes = 0;
    string input;
    bool valid_input = false;
    int hours, minutes;
    while (!valid_input) {
        cout << "Введіть час y форматі ГГ:XX (наприклад, 15:10 або 03:56) ";
        cin >> input;
        if (input.length() != 5) { //перевірка формату введення
            cout << "Некоректний ввід! Введіть час y форматі ГГ:XX." << endl;
            continue;
        }
        if (input[2] != ':') { //перевірка формату введення
            cout << "Некоректний ввід! Введіть час y форматі ГГ:XX." << endl;
            continue;
        }
        hours = stoi(input.substr(0, 2)); //виділення годин із загального введення
        minutes = stoi(input.substr(3, 2)); //виділення хвилин із загального введення
        if (hours < 0 || hours >= 24) { //перевірка коректності значення годин
            cout << "Некоректний ввід! Кількість годин має належати проміжку [0;23]." << endl;
            continue;
        }
        if (minutes < 0 || minutes >= 60) { //перевірка коректності значення хвилин
            cout << "Некоректний ввід! Кількість хвилин має належати проміжку [0;59]." << endl;
            continue;
        }
        valid_input = true;
    }
    total_minutes = hours * 60 + minutes; // обрахунок загального часу (у хвилинах від початку доби)
    return total_minutes;
}

void check_availability(const string& filename ) { //перевірка, чи може касир обслужити N клієнтів, які стоять у черзі
    ifstream infile(filename, ios::binary);
    if (!infile) {
        cerr << "Помилка відкриття файлу";
        return;
    }
    cin.ignore();
    cout << endl << "Введіть N (кількість клієнтів): ";
    int N;
    cin >> N;

    int total_break_time = 0;
    Break b;
    while (infile.read((char *)&b, sizeof(b))) {
        total_break_time += b.end_time - b.start_time; //додаємо до загального часу перерви різницю між кінцем і початком кожної перерви
    }
    infile.close();
    int total_time = 24 * 60; //нехай каса цілодобова, тоді загальний робочий час без перерв - 24 год * 60 хв у годині
    int total_service_time = N * 15; //загальний час обслуговування клієнта (кількість клієнтів * 15 хвилин на кожного клієнта)
    if (total_service_time <= total_time - total_break_time) //повертає True, якщо час обслуговування кілєнтів менший або рівний часу роботи каси без перерв
    {
        cout << "Касир встигне обслужити "<< N << " клієнтів." << endl;
    }
    else  cout << "Касир НЕ встигне обслужити " << N << " клієнтів." << endl;
}

void add_break(fstream& file) { //додавання одного запису
    cout << endl << "1- Час початку перерви" << endl;
    int start_time = get_time(); // отримання та валідація введеного користувачем часу початку перерви
    cout << "2- Час кінця перерви" << endl;
    int end_time = get_time();  // отримання та валідація введеного користувачем часу кінця перерви

    if (start_time >= end_time)
    {
        cout << "Помилка: початок введеної перерви повинен статися раніше її кінця!" << endl;
        cout << "Цей запис НЕ буде додано у файл." << endl << endl;
    }
    else
    {
        Break new_break = { start_time, end_time }; // створюємо новий запис

        Break existing_break;

        bool overlap = false;
        file.seekg(0); //повертаємося до початку файлу
 
        while (file.read((char*)&existing_break, sizeof(Break))) {
            if ((new_break.start_time <= existing_break.end_time) && (new_break.end_time >= existing_break.start_time)){
                cout << "Помилка: ця перерва накладається на іншу перерву." << endl;
                cout << "Цей запис НЕ буде додано у файл." << endl;
                overlap = true;
                break;
            }
        }
        if (!overlap) {
            file.clear(); //очищуємо прапори помилок та прапор кінця файлу
            file.seekp(0, ios::end); //встановлюємо позицію запису в кінець файлу
            file.write((char*)&new_break, sizeof(Break)); //додаємо новий запис у файл
            cout << "Перерва успішно додана до файлу." << endl << endl;
        }
    }
}

void append_records(const string& filename) //додавання записів
 {
    fstream file(filename, ios::binary | ios::in | ios::out | ios::app);
    int choice;
    do {
        add_break(file); //додавання нового запису
        cout << endl << "Бажаєте додати ще один запис?" << endl;
        cout << "1 - так, 2 - ні: ";
        cin >> choice;
    } while (choice == 1);
    cout << endl << endl;
    file.close();
 }

string get_filename() //отримання імені файлу
{
    cin.ignore();
    cout << "Введіть ім'я файлу без розширення: ";
    string filename;
    getline(cin,filename);
    filename += ".bin"; //додавання розширення до імені файлу
    return filename;
}

int get_choice()
{
    cout << "Файл для запису технічних перерв у роботі каси" << endl;
    cout << "1 - створити файл, 2 - працювати з існуючим файлом: ";
    int choice;
    cin >> choice;
    return choice;
}