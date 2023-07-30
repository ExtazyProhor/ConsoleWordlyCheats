#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <conio.h>
#include <math.h>
using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    ifstream fin;
    string path = "D:\\visual studio\\wordly\\wordly\\russian.txt";
    string word;
    int buttonCode = 0;

    bool rightWord;
    bool presentChar;
    int numberOfWords;

    int numberOfCharacters;
    string masc;
    string missingCharacters;
    string presentCharacters;

    while (buttonCode != 27) {
        numberOfWords = 0;
        cout << "Введите маску слова: ( пример - 'ра*' )\n";
        cin >> masc;
        numberOfCharacters = masc.length();
        cout << "Введите отсутствующие в слове буквы: ( если таких нет - введите '*' )\n";
        cin >> missingCharacters;
        if (missingCharacters == "*") missingCharacters = "";
        cout << "Введите присутствующие в слове буквы: ( если таких нет - введите '*' )\n";
        cin >> presentCharacters;
        if (presentCharacters == "*") presentCharacters = "";
        string* present;
        present = new string[presentCharacters.length()];
        for (int i = 0; i < presentCharacters.length(); ++i) {
            cout << "Где НЕ может стоять буква " << presentCharacters[i] << ": ( пример - '-*-' )\n";
            cin >> present[i];
        }

        cout << "\n\n";
        fin.open(path);
        if (fin.is_open()) {
            while (fin) {
                getline(fin, word);
                rightWord = true;
                if (word.length() == numberOfCharacters) {
                    for (int i = 0; i < numberOfCharacters; ++i) {
                        if (masc[i] == '*') {
                            for (int j = 0; j < missingCharacters.length(); ++j) {
                                if (word[i] == missingCharacters[j]) {
                                    rightWord = false;
                                    break;
                                }
                            }
                        }
                        else {
                            rightWord = (word[i] == masc[i] || abs(word[i] - masc[i]) == 32);
                        }
                        if (!rightWord) break;
                    }
                    for (int i = 0; i < presentCharacters.length(); ++i) {
                        presentChar = false;
                        for (int j = 0; j < present[i].length(); ++j) {
                            if (word[j] == presentCharacters[i]) {
                                presentChar = true;
                                if (present[i][j] == '-') {
                                    rightWord = false;
                                    break;
                                }
                            }
                        }
                        if (!presentChar) {
                            rightWord = false;
                            break;
                        }
                    }
                    if (rightWord) {
                        cout << word << endl;
                        numberOfWords++;
                    }
                }
            }
            cout << "количество подходящих слов: " << numberOfWords << "\n\n";
            fin.close();
        }
        delete[] present;
        buttonCode = _getch();
        cout << "\n\n\n\n\n";
    }
}