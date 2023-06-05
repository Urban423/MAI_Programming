/****************************************************************
*                     КАФЕДРА № 304 1 КУРС                      *
*---------------------------------------------------------------*
* Project Type  : Win32 Console Application                     *
* Project Name  : Laba3                                         *
* File Name     : Laba3.cpp                                     *
* Language      : C/C++                                         *
* Programmer(s) : Закусилов Л.З.                                *
* Modifyed By   :                                               *
* Lit source    :                                               *
* Created       : 29/03/23                                      *
* Last Revision : 30/03/23                                      *
* Comment(s)    : сортировка собсвенныхз структур               *
****************************************************************/
#include "Laba3.h"
#include "String.h"
#include "Table.h"
#include <vector>
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
	String::IntegerToString(result[0], plane.flight);
	while (result[0].getSize() < 3)
	{
		result[0].add(0, '0');
	}

	result[1] = plane.LA_mark;

	String::IntegerToString(result[2], plane.side_number);
	result[2].add(0, 1041);
	result[2].add(1, '-');

	String::IntegerToString(result[3], plane.enter_way);
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
char readPlanesFromFile(String**& planes, int& size, int*& cells_size)
{
	int ret = 0;
	String file_name = "laba3.txt";

	/*
	//input file name
	printf("   write file name: ");
	ret = writeText(file_name);
	if (ret) {
		return 1;
	}*/

	//read data from file and echo print
	String buffer;
	ret = readFromFile(buffer, file_name.c_str());
	if (ret) {
		return 1;
	}

	//prepare data
	String* lines = nullptr;
	ret = buffer.split(lines, size, '\n');
	planes = new String*[size];
	cells_size = new int[size];

	//calculate every line
	for (int i = 0; i < size; i++)
	{
		//split line
		String str(lines[i]);
		ret = str.split(planes[i], cells_size[i], ' ');
	}
	return 0;
}
//Конец функции



char errorHandler(Plane*& planes, int& real_size, String** planesStr, int size, int* cell_size)
{
	int res = _setmode(_fileno(stdout), _O_U16TEXT);
	int ret = 0;
	real_size = 0;
	int index = 0;
	for (int i = 0; i < size; i++)
	{
		real_size++;

		//check for number of componetnts
		if (cell_size[i] < 4)
		{
			wprintf(L"Слишком мало аргументов в строке номер: '%d'\n", i + 1);
			real_size--;
			continue;
		}
		if (cell_size[i] > 4)
		{
			wprintf(L"Слишком много аргументов в строке номер: '%d'\n", i + 1);
			real_size--;
			continue;
		}

		//check flight
		int temp;
		ret = String(planesStr[i][0]).toInteger(temp);
		if (ret || temp > 999) {
			wprintf(L"'Номер рейса' не верный на строке '%d'\n", i + 1);
			real_size--;
			continue;
		}

		//check side_number
		String sideNumber = planesStr[i][2];
		if (planesStr[i][2][0] != 1041 || planesStr[i][2][1] != '-')
		{
			wprintf(L"'Бортовой номер' повреждён на строке '%d'\n", i + 1);
			real_size--;
			continue;
		}
		else {
			sideNumber.remove(0);
			sideNumber.remove(0);
			ret = sideNumber.toInteger(temp);
			if (ret) {
				wprintf(L"'Бортовой номер' повреждён на строке '%d'\n", i + 1);
				real_size--;
				continue;
			}
		}

		//check enter_way
		ret = String(planesStr[i][3]).toInteger(temp);
		if (ret || temp > 99) {
			wprintf(L"'Пункт прибытия' повреждён на строке '%d'\n", i + 1);
			real_size--;
			continue;
		}
	}
	res = _setmode(_fileno(stdout), _O_TEXT);

	planes = new Plane[real_size];
	for (int i = 0; i < size; i++)
	{
		//check for number of componetnts
		if (cell_size[i] < 4 || cell_size[i] > 4)
		{
			continue;
		}

		//check flight
		int temp;
		ret = planesStr[i][0].toInteger(temp);
		planes[index].flight = temp;
		if (ret || temp > 999) {
			continue;
		}

		//check LA_mark
		planes[index].LA_mark = planesStr[i][1];

		//check side_number
		String sideNumber = planesStr[i][2];
		if (planesStr[i][2][0] != 1041 || planesStr[i][2][1] != '-')
		{
			continue;
		}
		else {
			sideNumber.remove(0);
			sideNumber.remove(0);
			ret = sideNumber.toInteger(temp);
			planes[index].side_number = temp;
			if (ret) {
				continue;
			}
		}

		//check enter_way
		ret = planesStr[i][3].toInteger(temp);
		planes[index].enter_way = temp;
		if (ret || temp > 99) {
			continue;
		}
		index++;
	}
	return 0;
}


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
	if (end < 1)
	{
		return 0;
	}
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
	String** string_table;				    //массив массивов строк для таблицы
	int* cells_size;				    //массив массивов строк для таблицы

	Plane* planeVector;            //динамичесуий массив структур
	int planeVectorSize = 0;
	//конец иницилизации переменных


	//чтнение дыннх из файла
	ret = readPlanesFromFile(string_table, size, cells_size);
	if (ret) {
		return -1;
	}

	for (int i = 0; i < size; i++)
	{
		printf("%d) ", i + 1);
		for (int j = 0; j < cells_size[i]; j++)
		{
			printUTF8(string_table[i][j]);
			printf(" ");
		}
		printf("\n");
	}

	ret = errorHandler(planeVector, planeVectorSize, string_table, size, cells_size);

	String** t = new String*[planeVectorSize + 1]; 
	t[0] = new String[4];
	t[0][0] = L"Номер рейса";
	t[0][1] = L"Марка ЛА";
	t[0][2] = L"Бортовой номер";
	t[0][3] = L"Пункт прибытия";
	//эчо печать
	for (int i = 0; i < planeVectorSize; i++)
	{
		t[i + 1] = PlaneToString(planeVector[i]);
	}
	//конец эхо печати
	Table a(t, 4, planeVectorSize + 1);
	a.drawTable();

	//вызов функции сортирвоки
	ret = bubbleSort(planeVector, 0, planeVectorSize);
	if (ret) {
		return -1;
	}

	String text;
	text = L"\nОтсортированная таблица:\n";
	printUTF8(text);
	//печать отсортированых структур
	for (int i = 0; i < planeVectorSize; i++)
	{
		t[i + 1] = PlaneToString(planeVector[i]);
	}
	a.drawTable();
	//конец печати

	return 0;
}//конец программы

/*********************** End of main.cpp file ******************************/