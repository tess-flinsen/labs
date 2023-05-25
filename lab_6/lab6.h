#include <iostream>
#include <string>

using namespace std;

void print_menu();
int take_input(int min, int max);

template <typename T>
class SetElement {
public:
    T data; 
    SetElement<T>* next; 

    SetElement(const T& value) : data(value), next(nullptr) {}
};

#include <iostream>

template <typename T>
class HashSet {
private:
    static const int TABLE_SIZE = 100;
    SetElement<T>* table[TABLE_SIZE];

public:
    HashSet();
    int hashFunction(const T& value);
    void clear();
    bool contains(const T& value);
    void insert(const T& value);
    HashSet<T> unionSet(const HashSet<T>& otherSet);
    class Iterator;

    Iterator begin() const {
        return Iterator(*this);
    }
};

template <typename T>
class HashSet<T>::Iterator {
private:
    const HashSet<T>& set;
    int currentIndex;
    SetElement<T>* currentElement;

public:
    Iterator(const HashSet<T>& s);

    bool isEnd() const;
    T getValue() const;
    void next();

private:
    void findNextElement();
};

template <typename T>
HashSet<T>::HashSet() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        table[i] = nullptr;
    }
}

template <typename T>
int HashSet<T>::hashFunction(const T& value) {
    const size_t size = sizeof(value);
    const char* data = reinterpret_cast<const char*>(&value);
    int hash = 0;
    for (size_t i = 0; i < size; ++i) {
        hash = hash * 31 + static_cast<int>(data[i]);
    }
    return hash % TABLE_SIZE;
}

template <typename T>
void HashSet<T>::clear() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        SetElement<T>* current = table[i];
        while (current != nullptr) {
            SetElement<T>* next = current->next;
            delete current;
            current = next;
        }
        table[i] = nullptr;
    }
}

template <typename T>
bool HashSet<T>::contains(const T& value) {
    int index = hashFunction(value);
    SetElement<T>* current = table[index];
    while (current != nullptr) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

template <typename T>
void HashSet<T>::insert(const T& value) {
    if (contains(value)) {
        return;
    }
    int index = hashFunction(value);
    SetElement<T>* newElement = new SetElement<T>(value);
    newElement->next = table[index];
    table[index] = newElement;
}

template <typename T>
HashSet<T> HashSet<T>::unionSet(const HashSet<T>& otherSet) {
    HashSet<T> resultSet;
    for (int i = 0; i < TABLE_SIZE; ++i) {
        SetElement<T>* current = table[i];
        while (current != nullptr) {
            if (!resultSet.contains(current->data)) {
                resultSet.insert(current->data);
            }
            current = current->next;
        }
    }
    for (int i = 0; i < TABLE_SIZE; ++i) {
        SetElement<T>* current = otherSet.table[i];
        while (current != nullptr) {
            if (!resultSet.contains(current->data)) {
                resultSet.insert(current->data);
            }
            current = current->next;
        }
    }
    return resultSet;
}

template <typename T>
HashSet<T>::Iterator::Iterator(const HashSet<T>& s) : set(s), currentIndex(0), currentElement(nullptr) {
    findNextElement();
}

template <typename T>
bool HashSet<T>::Iterator::isEnd() const {
    return currentElement == nullptr;
}

template <typename T>
T HashSet<T>::Iterator::getValue() const {
    return currentElement->data;
}

template <typename T>
void HashSet<T>::Iterator::next() {
    currentElement = currentElement->next;
    if (currentElement == nullptr) {
        ++currentIndex;
        findNextElement();
    }
}

template <typename T>
void HashSet<T>::Iterator::findNextElement() {
    while (currentIndex < TABLE_SIZE) {
        if (set.table[currentIndex] != nullptr) {
            currentElement = set.table[currentIndex];
            return;
        }
        ++currentIndex;
    }
}

template<typename T>
void handle_menu(HashSet<T> &set) {
    
    int choice, choice2;
    T element;

    int n;
    cout << endl << "Введіть кількість елементів, які хочете додати в початкову множину:\n";
    n = take_input(1, 50);
    for (int i = 0; i < n; i++) {
        cout << "Введіть елемент" << " : ";
        while (true) {
            cin >> element;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Некоректний ввід. Спробуйте ще раз. \n";
            } else {
                set.insert(element);
                break;
            }
        }
    }

    cout << endl << endl << "Початкова множина: ";
    for (typename HashSet<T>::Iterator it = set.begin(); !it.isEnd(); it.next()) {
        cout << it.getValue() << " ";
    }
    cout << endl << endl;

    do {
        print_menu();
        choice = take_input(0, 8);
        HashSet<T> otherSet;
        HashSet<T> unionSet;
        typename HashSet<T>::Iterator it = set.begin();

        switch (choice) {
            case 1:
                set.clear();
                cout << "Множина очищена. Її вміст: \n";
                for (typename HashSet<T>::Iterator it = set.begin(); !it.isEnd(); it.next()) {
                    cout << it.getValue() << " ";
                }
                break;
            case 2:
                cout << "Введіть значення для перевірки: ";
                cin >> element;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Помилка вводу.\n";
                } else { 
                    if (set.contains(element)) {
                        cout << "Елемент " << element << " належить множині.\n";
                    } else {
                        cout << "Елемент " << element << " не належить множині.\n";
                    }
                }
                break;

            case 3:
                cout << "Введіть новий елемент: ";
                cin >> element;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Помилка вводу.\n";
                } else {
                    set.insert(element);
                    cout << "Елемент " << element << " додано до множини.\n";
                    cout << "Оновлений вміст множини:\n";
                    for (typename HashSet<T>::Iterator it = set.begin(); !it.isEnd(); it.next()) {
                        cout << it.getValue() << " ";
                    }
                }
                break;

            case 4: {
                cout << "Введіть кількість елементів, які хочете додати в додаткову множину:\n";
                int num;
                num = take_input(1, 50);
                for (int i = 0; i < num; i++) {
                    cout << "Введіть елемент" << " : ";
                    while (true) {
                        cin >> element;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Некоректний ввід. Спробуйте ще раз. \n";
                        } else {
                            otherSet.insert(element);
                            break;
                        }
                    }
                }
                cout << "Вміст другої множини:\n";
                for (typename HashSet<T>::Iterator it = otherSet.begin(); !it.isEnd(); it.next()) {
                    cout << it.getValue() << " ";
                }
                unionSet = set.unionSet(otherSet);
                cout << "\nОб'єднання множин:\n";
                for (typename HashSet<T>::Iterator it = unionSet.begin(); !it.isEnd(); it.next()) {
                    cout << it.getValue() << " ";
                }
                cout << endl;
                break;
            }
            case 5:
                {
                    typename HashSet<T>::Iterator it = set.begin();
                    cout << "Ітератор встановлено на початок множини.\n";
                    cout << "Поточний елемент: " << it.getValue() << endl;
                    break;
                }
            case 6:
                {
                    if (it.isEnd()) cout << "Кінець множини.\n";
                    else cout << "Кінець множини не досягнуто.\n";
                    break;
                }
            case 7:
            {
                if (!it.isEnd()) {
                    cout << "Поточний елемент: " << it.getValue() << endl;
                } else {
                    cout << "Досягнуто кінця множини." << endl;
                }
                break;
            }

            case 8:
            {
                cout << "Поточний елемент: " << it.getValue() << endl;
                it.next();
                cout << "Здійснено перехід до наступного елемента. Поточний елемент: " << it.getValue() << endl;
                do {
                    cout << "Бажаєте перейти до наступного елемента (1 - так, 2 - ні)" << endl;
                    cin >> choice2;
                    if (choice2 == 1) {
                        if (!it.isEnd()) {
                            cout << endl << "Поточний елемент: " << it.getValue() << endl;
                            it.next();
                            cout << "Здійснено перехід до наступного елемента. Поточний елемент: " << it.getValue() << endl;
                        } else {
                            cout << "Досягнуто кінця множини." << endl;
                        }
                    }
                } while (choice2 != 2);
                break;
            }
            case 0:
                cout << "Роботу завершено!";
                break;

            default:
                cout << "Неправильний вибір. Спробуйте ще раз (0 - 8).\n";
                break;
        }
        cin.ignore();
    } while (choice != 0);
}
