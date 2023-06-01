#pragma once
#include "String.h"

class Table
{
public:
	Table();
	Table(String* string, unsigned int width, unsigned int height);
	Table(String** string, unsigned int width, unsigned int height);
	~Table();

	char drawTable();
private:
	char drawTopLine(int number_of_cells, unsigned int* size_of_cell);
	char drawCells(int number_of_cells, unsigned int* size_of_cell, unsigned int row_index);
	char drawMiddleLine(int number_of_cells, unsigned int* size_of_cell);
	char drawBottomLine(int number_of_cells, unsigned int* size_of_cell);
private:
	unsigned int width;
	unsigned int height;
	unsigned int* size_of_cells;
	String** table;



	int vertical = 0x2503;
	int verticalLeft = 0x252B;
	int verticalRight = 0x2523;

	int angle_right_down = 0x250F;
	int angle_left_down = 0x2513;
	int angle_right_up = 0x2517;
	int angle_left_up = 0x251B;

	int horizontal = 0x2501;
	int middle = 0x254B;
	int top_middle = 0x2533;
	int bottom_middle = 0x253B;
};