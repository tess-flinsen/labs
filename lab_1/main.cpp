#include "lab1.h"
using namespace std;

int main(int argc, char *argv[]) {
        if (string(argv[2]) == "FilePointer")
        {
            cout << "Enter the file name without extension: ";
            char inputFilename[70];
            fgets(inputFilename, 70, stdin);
            inputFilename[strcspn(inputFilename, "\n")] = '\0'; // видалення символу нового рядка зі строки

            char outputFilename[85];
            sprintf(outputFilename, "%s_upd.txt", inputFilename); // створюємо ім'я нового файлу

            strcat(inputFilename, ".txt"); // додаємо .txt розширення до inputFilename

            processFile(inputFilename);

            cout << "\n\nStarting file:\n\n";
            printFile(inputFilename);

            encryptFile(inputFilename);
            printFile(inputFilename);

            modifyFile(inputFilename, outputFilename);
            printFile(outputFilename);
        }
        else if (string(argv[2]) == "FileStream")
        {
            cout << "Enter the file name without extention: ";
            string inputFilename;
            getline(cin,inputFilename);
            string outputFilename = inputFilename + "_upd.txt"; //створюємо ім'я нового файлу
            inputFilename += ".txt"; //додаємо розширення до імені файлу
            
            processFile(inputFilename);

            cout << "\n\nStarting file:\n\n";
            printFile(inputFilename);
        
            encryptFile(inputFilename);
            printFile(inputFilename);

            modifyFile(inputFilename, outputFilename);
            printFile(outputFilename);
        }
        else cout << "Command line argument not found." << endl;
    return 0;
}