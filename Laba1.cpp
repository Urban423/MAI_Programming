/****************************************************************
*                     КАФЕДРА № 304 1 КУРС                      *
*---------------------------------------------------------------*
* Project Type  : Win32 Console Application                     *
* Project Name  : Laba1                                         *
* File Name     : main.cpp                                      *
* Language      : C/C++                                         *
* Programmer(s) : Закусилов Л.З., Роньжин Д.А.                  *
* Modifyed By   :                                               *
* Lit source    :                                               *
* Created       : 02/03/23                                      *
* Last Revision : 03/03/23                                      *
* Comment(s)    : поиск модного символа.                        *
****************************************************************/

#include <iostream>
#include "Laba1.h"
#include "String.h"
#include "Math.h"
using namespace std;

//начало алгоритма
int laba1()
{
    system("title Moda");

    //иницилизация переменных
    char ret = 0;                           //переменная для опознования ошибок
    String string;                      //строка с взодными данными
    String filename;                      //строка с именем файла
    int counter1 = 0;
    size_t max_number = 0;              //число самого модного символа в строке
    char num = 0;                       //самое модный символ
    unsigned char dictionary[256] = { 0 };      //массив хранящий количество раз которое каждый символ встертился в строке
    size_t number_of_first_byte = 0;    //указатель наиндекс начала слова в строке
    size_t counter = 0;                 //счетчик для счета самого модного числа в каждом слове
    //конец иницилизации переменных

    //заполняем массив нулями
    memset(dictionary, 0, 256);



    //начало цикла для заполнения матрицы(буфера) начальными значениями
    while (1)
    {
        //спрашиваем источник входных данных (файл или ввод вручню)
        cout << "   select buffer('file' or 'console'): ";
        ret = String::writeText(string);
        //проверка на ошибки
        if (ret == 0) {
            return 0;
        }
        //конец если

        //если источник входных данных файл
        if (string == "file")
        {
            printf("   write filename: ");
            if (!String::writeText(filename)) {
                return -1;
            }
            if (!String::readFromFile(string, filename.c_str())) {
                return -1;
            }

            //выходим из цикла
            break;
        }
        //конец если
        //начало если источник входных данных ввод вручную
        else if (string == "console")
        {
            printf("   write text: ");
            if (!String::writeText(string)) {
                return -1;
            }

            //выходим из цикла
            break;
        }
        //конец если
        //буффер не определен повторяем вопрос ползователю
        cout << "   command unknown please try again\n";
    }
    //конец цикла



    //начало цикла для поиска символа который встречается чаще всего
    for (int i = 0; i < string.getSize(); i++)
    {
        if (is_letter(string[i]) == 0) {
            continue;
        }
        //добавляем единицу к моде символа в строке
        dictionary[string[i]]++;
        //проверка на самый модный символ
        if (dictionary[string[i]] > max_number)
        {
            num = string[i];
            max_number = dictionary[string[i]];
        }
        //конец если
    }
    //конец цикла

    //ввыводим самый символ и количество раз которое он встречается
    cout << "\n   Output:\n   '" << num << "': " << max_number << "\n";

    //начало цикла для ввывода слов в которых символ встречаестя минимум 2 раза
    for (int i = 0; i < string.getSize(); i++) {
        //если встретился пробел то обнуляем переменные
        if (is_letter(string[i]) == 0) {
            number_of_first_byte = i + 1;
            counter = 0;
        }
        //конец если

        //если встретили самый модный элемент
        if (string[i] == num)
        {
            counter++; //увеличиваем счетчик

            //если встретили самый модный элемент 2 раза
            if (counter == 2)
            {
                counter1++;
                cout << "   " << counter1 << ": ";
                //возращаемся к началу слова
                i = number_of_first_byte;
                //начало цикла для печати слова с как минимум 2-мя модными символами (по символьно)
                while (1)
                {
                    //проверка что слово закончилось
                    if (is_letter(string[i]) == 0 || i == string.getSize())
                    {
                        i--;
                        break;
                    }
                    //конец если
                    cout << string[i];
                    i++;
                }
                //конец цикла
                cout << "\n";
            }
            //конец если
        }
        //конец если
    }
    //конец цикла


    cout << '\n';
    //system("pause");

    return 0;
}//конец программы

/*********************** End of main.cpp file ******************************/