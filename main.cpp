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
* Comment(s)    :                                               *
****************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "String.h"
#include "Console.h"
using namespace std;

//начало алгоритма
int main()
{
    system("title Console");

    String str = "aapple apple";
    char** b = nullptr;
    unsigned int size = 0;
    str.split(b, size, 'a');
    for (int i = 0; i < size; i++)
    {
        String s = b[i];
        printf("%s\n", s.c_str());
    }
    String buffer;
    if (commandLine(buffer) != 1)
    {
        return -1;
    }
    system("pause");

    return 0;
}//конец программы

/*********************** End of main.cpp file ******************************/