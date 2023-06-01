#include "Table.h"
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <math.h>

Table::Table()
{
	width = 6;
	height = 5;

	size_of_cells = new unsigned int[width];
	for (unsigned int y = 0; y < width; y++)
	{
		size_of_cells[y] = 10;
	}

	table = new String*[height];
	for (unsigned int y = 0; y < height; y++)
	{
		table[y] = new String[width];
	}
}

Table::Table(String* string, unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;

	unsigned int index = 0;
	table = new String * [height];
	for (unsigned int y = 0; y < height; y++)
	{
		table[y] = new String[width];
		for (unsigned int x = 0; x < width; x++)
		{
			table[y][x] = string[index];
			index++;
		}
	}


	size_of_cells = new unsigned int[width];
	for (unsigned int x = 0; x < width; x++)
	{
		int cell_size = table[0][x].getSize();
		for (unsigned int y = 1; y < height; y++)
		{
			int temp = table[y][x].getSize();
			if (cell_size < temp)
			{
				cell_size = temp;
			}
		}
		cell_size += 2;
		size_of_cells[x] = cell_size;
	}
}

Table::Table(String** string, unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;

	unsigned int index = 0;
	table = string;


	size_of_cells = new unsigned int[width];
	for (unsigned int x = 0; x < width; x++)
	{
		int cell_size = table[0][x].getSize();
		for (unsigned int y = 1; y < height; y++)
		{
			int temp = table[y][x].getSize();
			if (cell_size < temp)
			{
				cell_size = temp;
			}
		}
		cell_size += 2;
		size_of_cells[x] = cell_size;
	}
}

Table::~Table()
{
	for (unsigned int y = 0; y < height; y++)
	{
		delete[] table[y];
	}
	//delete[] size_of_cells;
}

char Table::drawTable()
{
	//set UTF-16
	int res = _setmode(_fileno(stdout), _O_U16TEXT);

	drawTopLine(width, size_of_cells);
	for (unsigned int y = 0; y < height; y++)
	{
		drawCells(width, size_of_cells, y);
		if (y == height - 1) { break; }
		drawMiddleLine(width, size_of_cells);
	}
	drawBottomLine(width, size_of_cells);


	//return standart output mode
	res = _setmode(_fileno(stdout), _O_TEXT);
	return 0;
}


//top line
char Table::drawTopLine(int number_of_cells, unsigned int* size_of_cell)
{
	wprintf(L"%c", angle_right_down);
	for (int x = 0; x < number_of_cells; x++)
	{
		for (unsigned int x1 = 0; x1 < size_of_cell[x]; x1++)
		{
			wprintf(L"%c", horizontal);
		}
		if (x == number_of_cells - 1) { break; }
		wprintf(L"%c", top_middle);
	}
	wprintf(L"%c\n", angle_left_down);
	return 0;
}

//cells line
char Table::drawCells(int number_of_cells, unsigned int* size_of_cell, unsigned int row_index)
{
	wprintf(L"%c", vertical);
	for (int x = 0; x < number_of_cells; x++)
	{
		printUTF8(table[row_index][x]);
		int res = _setmode(_fileno(stdout), _O_U16TEXT);
		for (unsigned int i = 0; i < size_of_cell[x] - table[row_index][x].getSize(); i++) { wprintf(L" "); }

		if (x == number_of_cells - 1) { break; }
		wprintf(L"%c", vertical);
	}
	wprintf(L"%c\n", vertical);
	return 0;
}

//middle line
char Table::drawMiddleLine(int number_of_cells, unsigned int* size_of_cell)
{
	wprintf(L"%c", verticalRight);
	for (int x = 0; x < number_of_cells; x++)
	{
		for (unsigned int i = 0; i < size_of_cell[x]; i++)
		{
			wprintf(L"%c", horizontal);
		}
		if (x == number_of_cells - 1) { break; }
		wprintf(L"%c", middle);
	}
	wprintf(L"%c\n", verticalLeft);
	return 0;
}

//bottom line
char Table::drawBottomLine(int number_of_cells, unsigned int* size_of_cell)
{
	wprintf(L"%c", angle_right_up);
	for (int x = 0; x < number_of_cells; x++)
	{
		for (unsigned int i = 0; i < size_of_cell[x]; i++)
		{
			wprintf(L"%c", horizontal);
		}
		if (x == number_of_cells - 1) { break; }
		wprintf(L"%c", bottom_middle);
	}
	wprintf(L"%c\n", angle_left_up);
	return 0;
}