﻿/****************************************************************
*                     КАФЕДРА № 304 1 КУРС                      *
*---------------------------------------------------------------*
* Project Type  : Win32 Console Application                     *
* Project Name  : Laba3                                         *
* File Name     : Laba3.cpp                                     *
* Language      : C/C++                                         *
* Programmer(s) : Закусилов Л.З., Роньжин Д.А.                  *
* Modifyed By   :                                               *
* Lit source    :                                               *
* Created       : 29/03/23                                      *
* Last Revision : 30/03/23                                      *
* Comment(s)    : сортировка собсвенныхз структур               *
****************************************************************/
#include "Laba3.h"
#include "String.h"
#include <stdio.h>

//структура самолёта
struct Plane
{
	int flight = 0;				//номер рейса
	String LA_mark = "";		//марка ЛА
	String side_number = "";	//бортовой номер
	int enter_way = 0;			//пункт прибытия
};
//конец стурктуры

//Функция для печати структуры
char printPlane(Plane& plane)
{
	printf("%d %s %s %d", plane.flight, plane.LA_mark.c_str(), plane.side_number.c_str(), plane.enter_way);
	return 0;
}
//конец функции

//Функция чтения данных из файла
char readPlanesFromFile(Plane*& planes, int& size)
{
	int ret = 0;
	String file_name = "laba3.txt";

	printf("   write file name: ");
	ret = String::writeText(file_name);
	if (ret == 0)
	{
		return 1;
	}

	String buffer;
	ret = String::readFromFile(buffer, file_name.c_str(), 0);
	if (ret == 0)
	{
		return 1;
	}
	char** lines = nullptr;
	ret = buffer.split(lines, size, '\n');

	if (planes != nullptr)
	{
		delete[] planes;
	}
	planes = new Plane[size];
	char** line = nullptr;
	int number_of_components = 0;
	for (int i = 0; i < size; i++)
	{
		String str(lines[i]);
		ret = str.split(line, number_of_components, ' ');

		if (number_of_components < 4)
		{
			return 1;
		}
		int temp;
		ret = String(line[0]).toInteger(temp);
		planes[i].flight = temp;
		if (ret == 0)
		{
			return 1;
		}

		planes[i].LA_mark = line[1];
		planes[i].side_number = line[2];

		ret = String(line[3]).toInteger(temp);
		planes[i].enter_way = temp;
		if (ret == 0)
		{
			return 1;
		}
	}

	return 0;
}
//Конец функции




//сортировка выбором
char selectionSort(Plane* planes, unsigned int start, unsigned int end)
{
	unsigned int min_index = 0;
	for (unsigned int i = start; i < end - 1; i++)
	{
		min_index = i;
		for (unsigned int j = i + 1; j < end; j++)
		{
			if (planes[j].flight < planes[min_index].flight)
			{
				min_index = j;
			}
		}

		if (min_index != i)
		{
			Plane temp = planes[min_index];
			planes[min_index] = planes[i];
			planes[i] = temp;
		}
	}
	return 0;
}
//Конец сортировки выбором

//сортировка пузыркём
char bubbleSort(Plane* planes, unsigned int start, unsigned int end)
{
	char flag = 1;
	for (unsigned int i = start; i < end - 1; i++)
	{
		flag = 1;
		for (unsigned int j = start; j < end - i - 1; j++)
		{
			if (planes[j].flight > planes[j + 1].flight)
			{
				Plane temp = planes[j + 1];
				planes[j + 1] = planes[j];
				planes[j] = temp;

				flag = 0;
			}
		}
		if (flag)
		{
			break;
		}
	}
	return 0;
}
//Конец сортировки пузыркём

//сортировка вставками
char insertionSort(Plane* planes, unsigned int start, unsigned int end)
{
	Plane temp;
	if (planes[start].flight > planes[start + 1].flight)
	{
		temp = planes[start];
		planes[start] = planes[start + 1];
		planes[start + 1] = temp;
	}

	for (int i = start + 2; i < end; i++)
	{
		temp = planes[i];
		int j = i - 1;
		while (j >= 0 && temp.flight < planes[j].flight)
		{
			planes[j + 1] = planes[j];
			j--;
		}
		planes[j + 1] = temp;
	}
	return 0;
}
//Конец сортировки вставками

//сортировка слиянием
char merge(Plane* planes, unsigned int start, unsigned int end)
{
	unsigned int size = end - start;
	if (size == 1 || size == start)
	{
		return 0;
	}
	if (size == 2)
	{
		if (planes[start].flight > planes[start + 1].flight)
		{
			Plane temp = planes[start];
			planes[start] = planes[start + 1];
			planes[start + 1] = temp;
		}
		return 0;
	}
	merge(planes, start, end / 2 + 1);
	merge(planes, end / 2 + 1, end);

	Plane* temp_planes = new Plane[size];
	if (temp_planes == NULL)
	{
		return 1;
	}
	unsigned int second_start = end / 2 + 1;
	unsigned int a = start;
	unsigned int b = second_start;
	for (unsigned int i = 0; i < size; i++)
	{
		if (b > end - 1 || (a < second_start && planes[a].flight < planes[b].flight))
		{
			temp_planes[i] = planes[a];
			a++;
		}
		else {
			temp_planes[i] = planes[b];
			b++;
		}
	}

	for (unsigned int i = 0; i < size; i++)
	{
		planes[start + i] = temp_planes[i];
	}

	if (temp_planes != nullptr)
	{
		delete[] temp_planes;
	}
	return 0;
}
//конец сортирови слиянием




//начало алгоритма
int laba3()
{ 
	//иницилизация переменных
	char ret = 0;                           //переменная для опознования ошибок
	int size = 0;							//переменнная хранящие колисечтво структур в файле
	Plane* planes = nullptr;				//динамичесуий массив структур
	//конец иницилизации переменных

	//чтнение дыннх из файла
	ret = readPlanesFromFile(planes, size);
	if (ret) {
		return -1;
	}

	//эчо печать
	for (int i = 0; i < size; i++)
	{
		printf("   %d) ", i);
		printPlane(planes[i]);
		printf("\n");
	}
	printf("\n");
	//конец эхо печати

	//вызов функции сортирвоки
	ret = insertionSort(planes, 0, size);
	if (ret) {
		return -1;
	}

	//печать отсортированых структур
	for (int i = 0; i < size; i++)
	{
		printf("   %d) ", i);
		printPlane(planes[i]);
		printf("\n");
	}
	//конец печати

	//чистка мусора
	if (planes != nullptr)
	{
		delete[] planes;
	}
	//конец чистки мусора

	return 0;
}//конец программы

/*********************** End of main.cpp file ******************************/