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
#include "Table.h"
#include <stdio.h>
#include <fcntl.h>
#include <io.h>


//структура самолёта
struct Plane
{
	int flight = 0;				//номер рейса
	String LA_mark = "";		//марка ЛА
	int side_number = 0;		//бортовой номер
	int enter_way = 0;			//пункт прибытия
};
//конец стурктуры


String* PlaneToString(Plane& plane)
{
	String* result = new String[4];
	if (plane.flight == -1) {
		result[0] = "ERR";
	}
	else {
		String::IntegerToString(result[0], plane.flight);
	}
	result[1] = plane.LA_mark;
	if (plane.side_number == -1) {
		result[2] = "ERR";
	}
	else {
		String::IntegerToString(result[2], plane.side_number);
		result[2].add(0, 1041);
		result[2].add(1, '-');
	}
	if (plane.enter_way == -1) {
		result[3] = "ERR";
	}
	else {
		String::IntegerToString(result[3], plane.enter_way);
	}
	return result;
}

//Функция для печати структуры
char printPlane(Plane& plane)
{
	printf("%d ", plane.flight);
	printUTF8(plane.LA_mark);
	int res = _setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(L" Б-%d %d", plane.side_number, plane.enter_way);
	res = _setmode(_fileno(stdout), _O_TEXT);
	return 0;
}
//конец функции

//Функция чтения данных из файла
char readPlanesFromFile(Plane*& planes, int& size)
{
	int ret = 0;
	String file_name = "laba3.txt";

	//clear planes
	if (planes != nullptr) {
		delete[] planes;
	}

	//input file name
	printf("   write file name: ");
	ret = writeText(file_name);
	if (ret) {
		return 1;
	}

	//read data from file and echo print
	String buffer;
	ret = readFromFile(buffer, file_name.c_str());
	if (ret) {
		return 1;
	}

	//prepare data
	String* lines = nullptr;
	ret = buffer.split(lines, size, '\n');
	planes = new Plane[size];
	String* line = nullptr;
	int number_of_components = 0;

	//calculate every line
	for (int i = 0; i < size; i++)
	{
		//split line
		String str(lines[i]);
		ret = str.split(line, number_of_components, ' ');

		//check for number of componetnts
		if (number_of_components < 4)
		{
			printf("too few arguments in line: '%d'\n", i + 1);
		}
		if (number_of_components > 4)
		{
			printf("too many arguments in line: '%d'\n", i + 1);
		}

		//check flight
		int temp;
		ret = String(line[0]).toInteger(temp);
		planes[i].flight = temp;
		if (ret) {
			planes[i].flight = -1;
			printf("'flight' corrupted on line '%d'\n", i + 1);
		}

		//check LA_mark
		planes[i].LA_mark = line[1];

		//check side_number
		String sideNumber = line[2];
		if (line[2][0] != 1041 || line[2][1] != '-')
		{
			planes[i].side_number = -1;
			printf("'side number' corrupted on line '%d'\n", i + 1);
		}
		else {
			sideNumber.remove(0);
			sideNumber.remove(0);
			ret = sideNumber.toInteger(temp);
			planes[i].side_number = temp;
			if (ret) {
				planes[i].side_number = -1;
				printf("'side number' corrupted on line '%d'\n", i + 1);
			}
		}

		//check enter_way
		ret = String(line[3]).toInteger(temp);
		planes[i].enter_way = temp;
		if (ret) {
			planes[i].enter_way = -1;
			printf("'enter way' corrupted on line '%d'\n", i + 1);
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

	for (unsigned int i = start + 2; i < end; i++)
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
	String** t;								//массив массивов строк для таблицы

	//конец иницилизации переменных

	//чтнение дыннх из файла
	ret = readPlanesFromFile(planes, size);
	if (ret) {
		return -1;
	}

	t = new String*[size + 1];
	t[0] = new String[4];
	t[0][0] = L"Номер рейса";
	t[0][1] = L"Марка ЛА";
	t[0][2] = L"Бортовой номер";
	t[0][3] = L"Пункт прибытия";
	//эчо печать
	for (int i = 0; i < size; i++)
	{
		t[i + 1] = PlaneToString(planes[i]);
	}
	//конец эхо печати
	Table a(t, 4, size + 1);
	a.drawTable();

	//вызов функции сортирвоки
	ret = insertionSort(planes, 0, size);
	if (ret) {
		return -1;
	}

	//печать отсортированых структур
	for (int i = 0; i < size; i++)
	{
		t[i + 1] = PlaneToString(planes[i]);
	}
	a.drawTable();
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