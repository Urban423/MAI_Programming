#include "Laba2.h"
#include <stdlib.h>
#include "String.h"
#include <iostream>
using namespace std;

char ReadMatrixFromFile(int& width, int& height, int*& buffer)
{
    char ret = 1;
    String string;
    String filename;
    char** b = nullptr;
    unsigned int size = 0;
    char** line = nullptr;
    unsigned int line_size = 0;
    FILE* file;

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
    return 1;
}

int laba2()
{
    system("title Matrix");

    char ret = 0;
    int width = 0;
    int height = 0;
    int* buffer = nullptr;
    int max_summ = 0;
    int min_summ = INT16_MAX;
    unsigned int min_summ_index = 0;
    unsigned int max_summ_index = 0;
    int summ = 0;
    String command;

    while (1)
    {
        cout << "   select buffer('file' or 'console'): ";
        ret = String::writeText(command);
        if (ret == 0) {
            return 0;
        }
        if (command == "file")
        {
            ret = ReadMatrixFromFile(width, height, buffer); 
            if (ret == 0) {
                return -1;
            }
            break;
        }
        else if (command == "console")
        {
            ret = ReadMatrixFromConsole(width, height, buffer);
            if (ret == 0)
            {
                return - 1;
            }
            break;
        }
        cout << "   command unknown please try again\n";
    }
   

    cout << "   w: " << width << ", " << "h: " << height << "\n   Matrix:\n";
    for (int j = 0; j < height; j++)
    {
        cout << "   ";
        for (int i = 0; i < width; i++)
        {
            cout << buffer[j * width + i] << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    cout << "   ";
    for (int i = 0; i < width; i++)
    {
        summ = 0;
        for (int j = 0; j < height; j++)
        {
            int num = buffer[j * width + i];
            if (num < 0 && abs(num) % 2 == 1)
            {
                summ -= num;
            }
        }
        cout << summ << " ";
        if (summ > max_summ)
        {
            max_summ_index = i;
            max_summ = summ;
        }
        if (summ < min_summ)
        {
            min_summ_index = i;
            min_summ = summ;
        }
    }
    cout << "\n";
    cout << "\n";
    for (int j = 0; j < height; j++)
    {
        int temp = buffer[j * width + max_summ_index];
        buffer[j * width + max_summ_index] = buffer[j * width + min_summ_index];
        buffer[j * width + min_summ_index] = temp;
    }
    
    for (int j = 0; j < height; j++)
    {
        cout << "   ";
        for (int i = 0; i < width; i++)
        {
            cout << buffer[j * width + i] << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    if (buffer != nullptr)
    {
        delete[] buffer;
    }

    return 0;
}
