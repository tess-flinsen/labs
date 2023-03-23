#include "lab1.h"

bool isFileExisting(const string& fileName) { //перевірка, чи файл існує
    ifstream file(fileName);
    return file.good();
}
bool isFileEmpty(const string& fileName) { //перевірка, чи файл порожній
    ifstream file(fileName);
    return file.peek() == ifstream::traits_type::eof();
}

void processFile(const string& fileName){ //обробка файлу (ствоення/відкриття, друк вмісту, додавання рядків)
    
    bool fileExists = true;
    if (!isFileExisting(fileName) || isFileEmpty(fileName)) { //перевірка, чи існує файл та чи має вміст
        fileExists = false;
    }

    if (fileExists) { 
        ifstream infile(fileName);
        if (!infile) {
            cerr << "Error opening a file!" << endl;
            return;
        }
        cout << "\nFile contents:" << endl;
        cout << infile.rdbuf(); //друк вмісту файлу
        infile.close();
    }
    
    ofstream outfile(fileName, ios::app);
    if (!outfile){
        cerr << "Error opening a file!" << endl;
        return;
    }
    if (!fileExists) {
        cout << "File was created.\n\n";
    }
    string choice;
    string line;
    cout << endl; 
    while (true) { //додавання рядків до файлу
        cout << "Enter line? (yes - Enter, no -  1): ";
        getline(cin,choice);
        if (choice == "1") break; //якщо користувач обирає "1", то відбувається вихід із циклу й запис припиняється
        cout << "Line: ";
        getline(cin,line);
        outfile << line << endl;
    }
    
    outfile.close();
}
void processFile(const char* fileName) {  //обробка файлу (ствоення/відкриття, друк вмісту, додавання рядків)
    bool fileExists = true;
    FILE *file = fopen(fileName, "r");
    if (file == NULL) { //перевірка, чи файл існує
        fileExists = false;
    } else {
        fseek(file, 0, SEEK_END); 
        if (ftell(file) == 0) { //перевірка, чи файл має вміст
            fileExists = false;
        }
        rewind(file);
    }
    if (fileExists) {
        cout << "\nFile contents:\n";
        char c;
        while ((c = fgetc(file)) != EOF) { //друк вмісту файлу
            putchar(c);
        }
        fclose(file);
    }
    file = fopen(fileName, "a"); //відкриття файлу в append mode
    if (file == NULL) {
        cout << "Error opening a file!\n";
        return;
    }
    if (!fileExists) //якщо файл не існував, то його було створено
    {
        cout << "File was created.\n\n";
    }

    char choice[3];
    char line[4192];
    cout << endl;
    while (true) 
    {
        cout << "Enter line? (yes - Enter, no - 1): ";
        fflush(stdin); // очищення буферу вводу
        fgets(choice, 2, stdin);
        if (strcmp(choice, "\n") == 0) {
            cout << "Line: ";
            fflush(stdin); // очищення буферу вводу
            fgets(line, 4192, stdin); //отримання нового рядку від користувача
            //strcat(line, "\n");
            fputs(line, file); //додавання рядку у файл
        } else if (strcmp(choice, "1") == 0) { //якщо користувач обирає "1", то відбувається вихід із циклу й запис припиняється
            break;
        } else {
            cout << "Invalid choice." << endl;
        }
    }
    fclose(file);
}

void printFile(const string& filename) //друк вмісту файлу 
{
    ifstream myfile(filename);

    if (!myfile.is_open()) { 
        cerr << "Error opening the file!" << endl;
        return;
    }
    string line;
    while(getline(myfile, line))
    {
        cout << line << endl;
    }
    
    myfile.close();
}
void printFile(const char* filename) { //вивід вмісту файлу
    FILE *myfile;
    myfile = fopen(filename, "r");

    if (myfile == NULL) {
        cerr << "Error opening the file!" << endl;
        exit(1);
    }
    else {
        rewind(myfile);
        int c;
        while ((c = fgetc(myfile)) != EOF) { //посимвольне зчитування
            putchar(c); //виведення символу
        }

        cout << endl << endl;
        fclose(myfile);
    }
}

string shiftString(string s, int k) //шифрування рядку
{
        string result = "";
        for (int i = 0; i < s.length(); i++) {
            char c = s[i];
            if (isalpha(c)) {  // перевіряємо, чи символ є буквою
                int base = isupper(c) ? 'A' : 'a'; // визначаємо базову букву (велику або малу)
                c = ((c - base + k) % 26) + base; // зміщуємо букву на k позицій вправо
            }
            result += c; // додаємо змінений символ до нового рядку
        }
        return result;
}
char* shiftString(const char* s, int k) {
    int len = strlen(s);
    char* result = new char[len + 1]; // виділяємо пам'ять для нової строки (видаляється в основній програмі)
    for (int i = 0; i < len; i++) {
        char c = s[i];
        if (isalpha(c)) { // перевіряємо, чи символ є буквою
            int base = isupper(c) ? 'A' : 'a'; // визначаємо базову букву (велику або малу)
            c = ((c - base + k) % 26) + base; // зміщуємо букву на k позицій вправо
        }
        result[i] = c; // додаємо змінений символ до нового рядку
    }
    result[len] = '\0'; // додаємо нуль-термінатор
    return result;
}

void encryptFile(const string& fileName) //шифрування файлу
{   ifstream inputFile(fileName);
    if (!inputFile.is_open()) { 
        cerr << "Error opening the file!" << endl;
        return;
    }
    int k;
    cout << "\nEnter k: ";
    cin >> k;

    string outputFileName;
    size_t lastDotPos = fileName.find_last_of("."); //пошук останньої крапки для відділення назви файлу від його розширення
    if (lastDotPos != string::npos) {
        outputFileName = fileName.substr(0, lastDotPos) + "_enc" + fileName.substr(lastDotPos); //створюємо ім'я нового файла
    }

    ofstream outputFile(outputFileName); //відкриваємо новий файл
    if (!outputFile.is_open()) { 
        cerr << "Error opening the file!" << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        string encryptedLine = shiftString(line, k); //шифруємо рядок
        outputFile << encryptedLine << endl; //записуємо змінений рядок у новий файл
    }
    inputFile.close();
    outputFile.close();
    remove(fileName.c_str()); //видаляємо старий файл
    rename(outputFileName.c_str(), fileName.c_str()); //змінюємо ім'я  нового файлу на ім'я старого файлу
    cout << "\n\nEncrypted file:\n\n"; 
}
void encryptFile(const char* fileName) {  
    FILE* inputFile = fopen(fileName, "r"); 
    if (!inputFile) { 
        cerr << "Error opening a file!" << endl;
        return;
    }
    else
    {   
        int k = 0;
        cout << "\nEnter k: ";
        cin >> k;

        char* outputFileName = new char[strlen(fileName) + 5]; //створюємо ім'я нового файлу (додаємо _enc)
        if (!outputFileName) {
            cerr << "Unable to allocate memory for output file name" << endl;
            return;
        }
        strcpy(outputFileName, fileName);
        strcat(outputFileName, "_enc");
        FILE* outputFile = fopen(outputFileName, "w");
        if (!outputFile) {
            cerr << "Unable to open file: " << outputFileName << endl; 
            return;
        }

        int len = 4192;
        char* line = new char[len]; //створюємо буфер для зберігання рядків
        if (!line) {
            cerr << "Unable to allocate memory for line" << endl;
            return;
        }
        
        while ((line = fgets(line, len, inputFile)) != NULL) { // читаємо кожен рядок
            char* encryptedLine = shiftString(line, k); // шифруємо рядок
            if (!encryptedLine) {
                cerr << "Unable to allocate memory for encrypted line" << endl;
                exit(1);
            }
            fputs(encryptedLine, outputFile); // записуємо змінений рядок у вихідний файл
            delete[] encryptedLine; // звільняємо пам'ять
        }

        if (line == NULL && !feof(inputFile)) {
            cerr << "Error reading from input file" << endl;
            return;
        }
        if (feof(inputFile)) { //якщо кінець файлу успішно досягнуто

            fclose(inputFile); //закриваємо обидва файли
            fclose(outputFile);
            remove(fileName);   //видаляємо старий файл
            rename(outputFileName, fileName); //змінюємо ім'я  нового файлу на ім'я старого файлу
            if (outputFileName) { //перевіряємо, чи вказує вказівник outputFileName на дійсну область пам'яті
                delete[] outputFileName;
            }
        } else {
            //помилка зчитування файлу
            cerr << "Error reading from input file" << endl;
            return;
        }
        delete[] line; // звільнити пам'ять, виділену для рядка
    }
    cout << "\n\nEncrypted file:\n";
}

int countWords(const string& str, const char* delimiters) { //підрахунок слів
    char* cstr = new char[str.size() + 1]; // виділення пам'яті для масиву символів
    strcpy(cstr, str.c_str());  // копіювання рядка у масив символів
    char* word = strtok(cstr, delimiters); //розділення рядка на токени (слова) за допомогою роздільників delimiters
    int wordCount = 0;
    while (word != nullptr) { //цикл, який перебирає токени (слова)
        wordCount++; // збільшення лічильника слів на 1
        word = strtok(nullptr, delimiters); //отримуємо наступний токен
    }
    delete[] cstr; //звільняємо пам'ять
    return wordCount;
}
int countWords(const char* str, const char* delimiters) { //підрахунок слів
    char* srtCopy = new char[strlen(str) + 1]; // виділяємо пам'ять для копії вхідного рядка
    strcpy(srtCopy, str); 
    // оголошуємо змінні для збереження токенів та кількості слів
    char* word = strtok(srtCopy, delimiters);
    int wordCount = 0;

    // перебираємо всі токени та рахуємо їх кількість
    while (word != nullptr) {
        wordCount++;
        word = strtok(nullptr, delimiters);
    }
    // звільняємо пам'ять, виділену під копію рядка
    delete[] srtCopy;
    return wordCount;
}

string findSecondToLastWord(const string& str, const char* delimiters) { //пошук передостаннього слова
    char* cstr = new char[str.length() + 1]; //виділяємо пам'ять для масиву символів
    strcpy(cstr, str.c_str()); //копіюємо вміст рядка str в масив символів
    char* token = strtok(cstr, delimiters); //розділяємо рядок на токени (слова) за допомогою роздільників (delimiters)
    string lastWord;
    string secondLastWord;
    while (token != NULL) { //цикл, який перебирає токени (слова)
        if (!lastWord.empty()) {
            secondLastWord = move(lastWord); //якщо останнє слово не порожнє, то записуємо його у змінну для попереднього за останнім слова
        }
        lastWord = token; //зберігаємо поточний токен (слово) у змінну для останнього слова
        token = strtok(NULL, delimiters); //отримуємо наступний токен
    }
    delete[] cstr; //звільняємо пам'ять
    return secondLastWord;
}
char* findSecondToLastWord(const char* str, const char* delimiters) { //пошук передостаннього слова
    char* srtCopy = new char[strlen(str) + 1]; // виділяємо пам'ять для копії вхідного рядка
    strcpy(srtCopy, str);

    char* secondLastWord = nullptr; // ініціалізуємо вказівники на попереднє та передпопереднє слово значеннями nullptr
    char* lastWord = nullptr;

    char* token = strtok(srtCopy, delimiters); // розбиваємо рядок на токени (слова) за заданими роздільниками
    while (token != nullptr) {
        if (lastWord != nullptr) { // якщо lastWord не рівне nullptr, то вже було знайдено щонайменше два слова, тому можемо присвоїти значення змінної lastWord змінній secondLastWord
            if (secondLastWord != nullptr) {
                delete[] secondLastWord;
            }
            secondLastWord = new char[strlen(lastWord) + 1]; // виділяємо пам'ять для secondLastWord
            strcpy(secondLastWord, lastWord); //присвоюємо значення змінної lastWord змінній secondLastWord
        }
        // зберігаємо поточний токен як lastWord 
        lastWord = new char[strlen(token) + 1];
        strcpy(lastWord, token);
        token = strtok(nullptr, delimiters);
    }

    // звільняємо пам'ять, виділену під копію рядка та lastWord
    delete[] srtCopy;
    delete[] lastWord;
    return secondLastWord;
}

string findSecondWord(const string& str, const char* delimiters) { //пошук другого слова
    char* cstr = new char[str.size() + 1]; //виділяємо пам'ять для масиву символів
    strcpy(cstr, str.c_str()); //копіюємо вміст рядка str в масив символів
    int wordCount = 0; 
    string secondWord;
    char* token = strtok(cstr, delimiters); //розділяємо рядок на токени (слова) за допомогою роздільників (delimiters)
    while (token != nullptr) { //цикл, який перебирає токени (слова)
        wordCount++; //збільшуємо лічильник слів
        if (wordCount == 2) { //якщо це друге слово
            secondWord = token; //зберігаємо це слово у змінну secondWord
            break;
        }
        token = strtok(NULL, delimiters);
    }
    delete[] cstr; //звільняємо пам'ять
    return secondWord;
}
char* findSecondWord(const char* str, const char* delimiters) { //пошук другого слова
    char* strCopy = new char[strlen(str) + 1]; // виділяємо пам'ять під копію вхідного рядка
    strcpy(strCopy, str);
    char* secondWord = nullptr; // ініціалізуємо вказівник на друге слово значенням nullptr
    int wordCount = 0; // лічильник слів

    char* token = strtok(strCopy, delimiters); // розбиваємо рядок на токени (слова) за заданими роздільниками
    while (token != nullptr) {
        wordCount++;
        if (wordCount == 2) { // якщо слово є другим у рядку, то зберігаємо його значення та виходимо з циклу
            secondWord = new char[strlen(token) + 1]; // виділяємо пам'ять під друге слово
            strcpy(secondWord, token); // копіюємо значення слова до другого слова
            break; 
        }
        token = strtok(nullptr, delimiters); // продовжуємо розбивати рядок на токени
    }

    delete[] strCopy; // звільняємо пам'ять, виділену під копію рядка
    return secondWord; 
}

int findIndex(const string& str, const string& word) { //пошук індексу першої літери слова
    int length = word.length(); //довжина шуканого слова
    int pos = str.find(word); //пошук першого входження слова у рядок

    // Перевіряємо, чи знайдено слово та воно не є частиною іншого слова
    if (pos != string::npos && (pos == 0 || str[pos-1] == ' ' || str[pos-1] == ',' || str[pos-1] == '.')) {
        // Проходимо з кінця слова назад, щоб знайти індекс першої літери шуканого слова
        for (int i = pos - 1; i >= 0; i--) {
            if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
                return i + 1;
            }
        }
    }
    return -1; // Якщо слово не знайдено, повертаємо -1
}
int findIndex(char* str, char* word) {
    int length = strlen(word); // зберігаємо довжину слова
    char* ptr = strstr(str, word); // знаходимо перше входження слова у рядок

    //перевіряємо, чи знайдено слово і чи воно не є частиною іншого слова
    if (ptr != NULL && (ptr == str || *(ptr-1) == ' ' || *(ptr-1) == ',' || *(ptr-1) == '.')) {
        int index = ptr - str; 
        // проходимо назад від кінця слова, щоб знайти індекс його першої літери
        for (int i = index - 1; i >= 0; i--) {
            if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
                return i + 1;
            }
        }
    }
    return -1; // Якщо слово не знайдено, повертаємо -1
}

void modifyFile(const string& inputFileName, const string& outputFileName) { //модифікація початкового файлу та запис результату в новий файл
    ifstream inputFile(inputFileName);
    if (!inputFile) {
        cerr << "Error opening a file!"  << endl;
        return;
    }
    ofstream outputFile(outputFileName);
    if (!outputFile) {
        cerr << "Error opening a file!"  << endl;
        return;
    }
    string line;
    string lastLine; 

    int countLines, currentLine = 0;

    inputFile.clear(); // очистка будь-яких прапорців помилок
    inputFile.seekg(0); // встановлення позиції потоку на початок файлу
    countLines = 0; // скидання лічильника рядків

    while (getline(inputFile, line)) { // підрахунок кількості непорожніх рядків у файлі
        if (!line.empty()) {
            countLines++;
        }
    }
    
    inputFile.clear(); // очистка будь-яких прапорців помилок
    inputFile.seekg(0); // встановлення позиції потоку на початок файлу
 
    char delimiters[] = " ,."; //роздільники слів у файлі

    while (getline(inputFile, line)) {
        currentLine++;
        if ((currentLine % 2) == 1){ // модифікація кожного непарного рядка
            int words = countWords(line, delimiters); //підрахунок слів у рядку
            string finalLine;
            if (words > 2){ //якщо в рядку більше двох слів
                string secondToLastWord = findSecondToLastWord(line, delimiters); //пошук передостаннього слова в рядку
                finalLine = secondToLastWord; //запис передостаннього слова в перероблений рядок

                int secondToLastWordIndex = findIndex(line, secondToLastWord); //пошук індекса першої літери передостаннього слова
                int secondToLastWordLength = secondToLastWord.length(); //довжина передостаннього слова
                int secondToLastWordLastIndex = secondToLastWordIndex + secondToLastWordLength; //пошук індекса останньої  літери передостаннього слова
                
                int index = secondToLastWordLastIndex;

                char ch = line[index];
                while(ch == ' ' || ch == ',' || ch == '.') // додавання всіх роздільників після передостаннього слова в перероблений рядок
                {
                    finalLine += ch;
                    index++;
                    ch = line[index];
                }

                for(int i = 0; i < secondToLastWordIndex; i++) //додаваня всіх символів від першого слова до передостаннього (не включно) в перероблений рядок
                {
                    finalLine += line[i];
                }
                for(int i = index; i < line.length(); i++) //додавання всіх символів, починаючи з першої літери останнього слова в перероблений рядок
                {
                    finalLine += line[i];
                }

                if (currentLine != countLines)  outputFile << finalLine << endl; //запис переробленого рядку у файл, якщо поточна лінія не є останньою
                lastLine = finalLine;
            } 
            else //інакше (якщо в рядку два слова або менше)
            {   lastLine = line;
                if (currentLine != countLines)  outputFile << line << endl; //запис рядку у файл, якщо поточна лінія не є останньою
            }
        }
        else //інакше (якщо рядок непарний)
        {   lastLine = line;
            if (currentLine != countLines)  outputFile << line << endl; //запис рядку у файл, якщо поточна лінія не є останньою
        }
        
    }

    int finalWords = countWords(lastLine, delimiters); //підрахунок слів в останньому рядку
        if (finalWords > 1) //якщо кількість слів більше 1
        {
            string secondWord = findSecondWord(lastLine, delimiters); //пошук другого слова
            int secondWordIndex = findIndex(lastLine, secondWord);  //пошук індекса першої літери другого слова
            //int secondWordIndex = lastLine.find(secondWord);
            int secondWordLastIndex = secondWordIndex + secondWord.length()-1; //пошук індекса останньої літери другого слова
            lastLine += ':';
            char c = lastLine[secondWordLastIndex-1];
            int code = static_cast<int>(c); // отримання ASCII коду передостанньої літери другого слова 
            lastLine += to_string(code); //переведення int коду в рядок та дописування його до переробленого рядку
        }
        outputFile << lastLine << endl; //запис останнього рядку в новий файл

    inputFile.close();
    outputFile.close();
    cout << "\n\nModified file:\n\n";
    
}
void modifyFile(const char* inputFileName, const char* outputFileName)
{
    FILE* inputFile = fopen(inputFileName, "r");
    if (!inputFile) {
        cerr<< "Error opening input file" << endl;
        return;
    }
    FILE* outputFile = fopen(outputFileName, "w");
    if (!outputFile) {
        cerr<< "Error opening output file" << endl;
        fclose(inputFile);
        return;
    }
    char line[4192];
    char lastLine[4192];

    int countLines, currentLine = 0;
    fseek(inputFile, 0, SEEK_SET); // встановлюємо позицію читання в початок файлу

    while (fgets(line, 1024, inputFile)) // підрахунок кількості рядків у файлі
    {
        countLines++;
    }
    fseek(inputFile, 0, SEEK_SET); 

    char delimiters[] = " ,."; //роздільники слів у файлі
    while (fgets(line, 4192, inputFile))
    {
        currentLine++;
        if ((currentLine % 2) == 1){ // модифікація кожного непарного рядка
            int words = countWords(line, delimiters); //рахуємо кількість слів у рядку 
            
            char finalLine[4192] = {0};
            if (words > 2) //якщо в рядку більше двох слів
            {
                char* token = strtok(line, "\n"); // видаляємо \n з кінця рядку
                char* secondToLastWord = findSecondToLastWord(token, delimiters); // знаходимо передостаннє слово
                strncpy(finalLine, secondToLastWord, strlen(secondToLastWord)); //записуємо його на початок вихідного рядка (фін рядок "передостаннє_слово")


                int secondToLastWordFirstIndex = findIndex(line, secondToLastWord);  //пошук індекса першої літери передостаннього слова
                int secondToLastWordLength = strlen(secondToLastWord); //довжина передостаннього слова
                int secondToLastWordLastIndex = secondToLastWordFirstIndex + secondToLastWordLength - 1; //пошук індекса останньої  літери передостаннього слова

                int index = secondToLastWordLastIndex + 1;
                char ch = line[index];
                while(ch == ' ' || ch == ',' || ch == '.')// записуємо всі роздільники після передостаннього слова в перероблений рядок
                {
                    strncat(finalLine, &ch, 1);
                    index++;
                    ch = line[index];
                }

                for(int i = 0; i < secondToLastWordFirstIndex; i++) //додаваня всіх символів від першого слова до передостаннього (не включно) в перероблений рядок
                {
                    strncat(finalLine, &line[i], 1);
                }

                for(int i = index; i < strlen(line); i++)  //додавання всіх символів, починаючи з першої літери останнього слова в перероблений рядок
                {
                    strncat(finalLine, &line[i], 1);
                }

                if (currentLine != countLines) //запис переробленого рядку у файл, якщо поточна лінія не є останньою
                {
                    
                    fputs(finalLine, outputFile);
                    fputs("\n", outputFile);
                } 
                strcpy(lastLine, finalLine);
            }
            else //інакше (якщо в рядку два слова або менше)
            { 
                strcpy(lastLine, line);
                if (currentLine != countLines) 
                {
                    fputs(line, outputFile);
                } 
            }
        }else //інакше (якщо рядок непарний)
        { 
            strcpy(lastLine, line);
            if (currentLine != countLines) 
            {
                fputs(line, outputFile);
            } 
        }
    }

    int finalWords = countWords(lastLine, delimiters); //рахуємо кількість слів у рядку 
    if (finalWords > 1) { //якщо в рядку більше одного слова
        char* token = strtok(lastLine, "\n"); // видаляємо \n з кінця рядку
        char* secondWord = findSecondWord(token, delimiters); //щнаходимо друге слово в рядку

        int secondWordIndex = findIndex(lastLine, secondWord); //пошук індекса першої літери другого слова
        int secondWordLength = strlen(secondWord); //довжина передостаннього слова
        int secondWordLastIndex = secondWordIndex + secondWordLength - 1; //пошук індекса останньої  літери другого слова
        strcat(lastLine, ":");

        char c = lastLine[secondWordLastIndex-1];
        int code = static_cast<int>(c); // отримання ASCII коду передостанньої літери другого слова 
        char codeStr[6]; 
        sprintf(codeStr, "%d", code); // формуємо рядок із ASCII-коду
        strcat(lastLine, codeStr);  // додаємо отриманий рядок до рядку lastLine
    }
    fputs(lastLine, outputFile);

    cout << "Modified file: " << endl;

    fclose(inputFile);
    fclose(outputFile);
}
