/****************************************************************
*                     КАФЕДРА № 304 1 КУРС                      *
*---------------------------------------------------------------*
* Project Type  : Win32 Console Application                     *
* Project Name  : Laba2                                         *
* File Name     : Laba2.cpp                                     *
* Language      : C/C++                                         *
* Programmer(s) : Закусилов Л.З., Роньжин Д.А.                  *
* Modifyed By   :                                               *
* Lit source    :                                               *
* Created       : 18/03/23                                      *
* Last Revision : 20/03/23                                      *
* Comment(s)    :работа с матрицей                              *
****************************************************************/
#include "Laba2.h"
#include <stdlib.h>
#include "String.h"
#include <iostream>
using namespace std;

//Функция чтения матрицы из файла
char ReadMatrixFromFile(int& width, int& height, int*& buffer)
{
    char ret = 1;
    String string;
    String filename;
    char** b = nullptr;
    unsigned int size = 0;
    char** line = nullptr;
    int line_size = 0;
    FILE* file = nullptr;

    cout << "       file name = ";
    ret = String::writeText(filename);
    if (ret == 0) {
        return 0;
    }
    ret = String::readFromFile(string, filename.c_str(), false);
    if (ret == 0) {
        return 0;
    }

    int index = 0;
    string.split(b, size, '\n');
    height = size;
    for (int i = 0; i < size; i++)
    {
        String str(b[i]);
        str.split(line, line_size, ' ');
        if (width < line_size)
        {
            width = line_size;
        }
        if (line_size == 0)
        {
            height--;
        }
    }
    buffer = new int[width * height];
    for (int i = 0; i < size; i++)
    {
        String(b[i]).split(line, line_size, ' ');
        if (line_size == 0)
        {
            continue;
        }
        int s = 0;
        for (int j = 0; j < width; j++)
        {
            s = 0;
            if (j < line_size)
            {
                String stre(line[j]);
                ret = stre.toInteger(s);
                if (ret == 0) {
                    return 0;
                }
            }
            buffer[index] = s;
            index++;
        }

    }

    return 1;
}
//Конец функции

//Функция чтения матрицы из консоли
char ReadMatrixFromConsole(int& width, int& height, int*& buffer)
{
    String string;
    int seter = 0;
    char ret = 0;
    char** b = nullptr;
    unsigned int size = 0;

    cout << "       Matrix's width = ";
    while (1)
    {
        ret = String::writeText(string);
        if (ret == 0) {
            return 0;
        }
        ret = string.toInteger(width);
        if (ret == 0) {
            continue;
        }
        break;
    }

    cout << "       Matrix's height = ";
    while (1)
    {
        ret = String::writeText(string);
        if (ret == 0) {
            return 0;
        }
        ret = (unsigned)string.toInteger(height);
        if (ret == 0) {
            continue;
        }
        break;
    }

    buffer = new int[width * height];

    memset(buffer, 0, width * height * sizeof(int));

    for (int j = 0; j < height; j++)
    {
        cout << "       ";
        ret = String::writeText(string);
        if (ret == 0) {
            return 0;
        }

        string.split(b, size, ' ');
        for (unsigned int i = 0; i < width; i++)
        {
            seter = 0;
            if (i < size)
            {
                string = b[i];
                ret = string.toInteger(seter);
            }
            buffer[j * width + i] = seter;
        }
    }
    cout << '\n';
    return 1;
}
//Конец функции

//начало алгоритма
int laba2()
{
    system("title Matrix");

    //иницилизация переменных
    char ret = 0;                           //переменная для опознования ошибок
    int width = 0;                          //ширина матрицы
    int height = 0;                         //высота матрицы
    int* buffer = nullptr;                  //динамический масив храняци информацию о матрице
    int max_summ = 0;                       //максимальныя сумма столбца
    int min_summ = INT16_MAX;               //минимальная сумма столбца 
    unsigned int min_summ_index = 0;        //номер минимальной суммы столбца 
    unsigned int max_summ_index = 0;        //номер максимальной суммы столбца 
    int summ = 0;                           //сумма столбцов 
    String command;                         //строка комманды для определния потока входных данных
    //конец иницилизации переменных



    //начало цикла для заполнения матрицы(буфера) начальными значениями
    while (1)
    {
        //спрашиваем источник входных данных (файл или ввод вручню)
        cout << "   select buffer('file' or 'console'): ";
        ret = String::writeText(command);
        //проверка на ошибки
        if (ret == 0) {
            return 0;
        }
        //конец если

        //если источник входных данных файл
        if (command == "file")
        {
            // читаем матрицу их файла
            ret = ReadMatrixFromFile(width, height, buffer);

            //проверка на ошибки
            if (ret == 0) {
                return -1;
            }
            //конец если

            //выходим из цикла
            break;
        }
        //конец если
        //начало если источник входных данных ввод вручную
        else if (command == "console")
        {

            //ввод матрицы через консоль
            ret = ReadMatrixFromConsole(width, height, buffer);
            //проверка на ошибки
            if (ret == 0) {
                return -1;
            }
            //конец если
            
            //выходим из цикла
            break;
        }
        //конец если
        //буффер не определен повторяем вопрос ползователю
        cout << "   command unknown please try again\n";
    }
    //конец цикла
   


    //Эхо печать
    //вывод ширины и высоты
    cout << "   w: " << width << ", " << "h: " << height << "\n   Matrix:\n";
    //цикл для ввывода матрицы
    for (int j = 0; j < height; j++)
    {
        cout << "   ";
        for (int i = 0; i < width; i++)
        {
            //ввывод элемениа на координате (i, j)
            cout << buffer[j * width + i] << " ";
        }
        cout << "\n";
    }
    //конец цикла
    cout << "\n   ";
    //конец эхо печати


    //начао цыкла для определения сумм 'отрицательных и нечётных' во всех столбцах
    for (int i = 0; i < width; i++)
    {
        //сброс суммы
        summ = 0;
        for (int j = 0; j < height; j++)
        {
            int num = buffer[j * width + i];
            // проверка что число на координата(i, j) удовлетворяет условиям 'отрицательное и нечётное'
            if (num < 0 && abs(num) % 2 == 1)
            {
                //добавление элемента в сумму
                summ -= num;
            }
            //конец если
        }
        //ввывод суммы
        cout << summ << " ";


        //проверка что сумма больше максимальной суммы
        if (summ > max_summ)
        {
            max_summ_index = i;
            max_summ = summ;
        }
        //конец если


        //проверка что сумма меньше минимальной суммы
        if (summ < min_summ)
        {
            min_summ_index = i;
            min_summ = summ;
        }
        //конец если
    }
    //конец цикла


    cout << "\n\n";
    //начало цикла для того чтобы поменять столбец с максимальной и минимальной суммой
    for (int j = 0; j < height; j++)
    {
        int temp = buffer[j * width + max_summ_index];
        buffer[j * width + max_summ_index] = buffer[j * width + min_summ_index];
        buffer[j * width + min_summ_index] = temp;
    }
    //конец цикла

    //цикл для вывода матрицы после преобразовний  
    for (int j = 0; j < height; j++)
    {
        cout << "   ";
        for (int i = 0; i < width; i++)
        {
            //ввывод элемента на координате (i, j)
            cout << buffer[j * width + i] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    //конец цикла



    //чистка мусора
    if (buffer != nullptr)
    {
        delete[] buffer;
    }
    //конец чистки мусора

    return 0;
}//конец программы

/*********************** End of main.cpp file ******************************/