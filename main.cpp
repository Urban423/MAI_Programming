/****************************************************************
*                     КАФЕДРА № 304 1 КУРС                      *
*---------------------------------------------------------------*
* Project Type  : Win32 Console Application                     *
* Project Name  : MAI_Programming                               *
* File Name     : main.cpp                                      *
* Language      : C/C++                                         *
* Programmer(s) : Закусилов Л.З., Роньжин Д.А.                  *
* Modifyed By   :                                               *
* Lit source    :                                               *
* Created       : 02/03/23                                      *
* Last Revision : 19/03/23                                      *
* Comment(s)    :                                               *
****************************************************************/
#include <stdlib.h>
#include "Console.h"
using namespace std;

//начало алгоритма
int main()
{
    system("title Console");

    if (commandLine() != 1)
    {
        return -1;
    }
    system("pause");

    return 0;
}//конец программы

/*********************** End of main.cpp file ******************************/