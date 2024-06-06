#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>

typedef bool(__stdcall* CheckCharactersFunc)(const char*, const char*);
using namespace std;
int main() {
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");/*Перевод на русский язык*/


    // Запрос строки и символов у пользователя
    std::string inputString, characters;
    std::cout << "Введите строку: ";
    std::getline(std::cin, inputString);
    std::cout << "Введите что нужно найти: ";
    std::getline(std::cin, characters);

    // Проверка ввода
    std::cout << "Вводимая строка: " << inputString << std::endl;
    std::cout << "Что нужно найти: " << characters << std::endl;

    // Загрузка библиотеки
    HMODULE hLib = LoadLibrary(TEXT("Dynlib.dll"));
    if (hLib == NULL) {
        std::cerr << "Не грузит DLL" << std::endl;
        return 1;
    }
    std::cout << "DLL Загружено." << std::endl;

    // Получение адреса функции
    CheckCharactersFunc checkCharacters = (CheckCharactersFunc)GetProcAddress(hLib, "Found");
    if (!checkCharacters) {
        std::cerr << "невозможно найти функции" << std::endl;
        FreeLibrary(hLib);
        return 1;
    }
    std::cout << "Адрес функций найден" << std::endl;

    // Вызов функции
    bool result = checkCharacters(inputString.c_str(), characters.c_str());

    // Вывод результата
    if (result) {
        std::cout << "Всё найдено в водимом" << std::endl;
    }
    else {
        std::cout << "Ничего не найдено." << std::endl;
    }

    // Освобождение библиотеки
    FreeLibrary(hLib);

    // Ожидание нажатия Ctrl + B перед завершением
    std::cout << "Press Ctrl + C to exit..." << std::endl;
    while (true) {
        if (_kbhit()) {
            int ch = _getch();
            if (ch == 3) { // Ctrl + 
                break;
            }
        }
    }

    return 0;
}