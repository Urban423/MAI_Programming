/****************************************************************
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
#include <malloc.h>

struct Plane
{
	int flight = 0;
	String LA_mark = "";
	String side_number = "";
	int enter_way = 0;
};

char printPlane(Plane& plane)
{
	printf("%d %s %s %d", plane.flight, plane.LA_mark.c_str(), plane.side_number.c_str(), plane.enter_way);
	return 0;
}

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


//сортировка слиянием
char merge(Plane* planes, unsigned int start, unsigned int end)
{
	unsigned int size = end - start;
	if (size == 1)
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
	int a = start;
	int b = second_start;
	for (int i = 0; i < size; i++)
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

	for (int i = 0; i < size; i++)
	{
		planes[start + i] = temp_planes[i];
	}

	if (temp_planes != nullptr)
	{
		delete[] temp_planes;
	}
	return 0;
}
//конец ортирови слиянием


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
	ret = merge(planes, 0, size);
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