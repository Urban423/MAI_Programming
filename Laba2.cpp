#include "Laba2.h"
#include <stdlib.h>
#include "String.h"
#include <iostream>
using namespace std;

int laba2()
{
    system("title Matrix");

    char** b = nullptr;
    String s;
    int seter = 0;
    unsigned int size = 0;
    char ret = 0;
    String string;
    int width = 0;
    int height = 0;
    int* buffer = nullptr;
    int* mini_buffer = nullptr;
    int max_summ = 0;
    int min_summ = INT16_MAX;
    unsigned int min_summ_index = 0;
    unsigned int max_summ_index = 0;
    int summ = 0;

    cout << "Mextix's width = ";
    while (1)
    {
        ret = String::writeText(string);
        if (ret == 0) {
            return -1;
        }
        ret = string.toInteger(width);
        if (ret == 0) {
            continue;
        }
        break;
    }

    cout << "Mextix's height = ";
    while (1)
    {
        ret = String::writeText(string);
        if (ret == 0) {
            return -1;
        }
        ret = (unsigned)string.toInteger(height);
        if (ret == 0) {
            continue;
        }
        break;
    }
    cout << "w: " << width << "\n" << "h: " << height << "\n";

    buffer = new int[width * height];

    memset(buffer, 0, width * height * sizeof(int));

    for (int j = 0; j < height; j++)
    {
        ret = String::writeText(string);
        if (ret == 0) {
            return -1;
        }

        string.split(b, size, ' ');
        for (unsigned int i = 0; i < width; i++)
        {
            seter = 0;
            if (i < size)
            {
                s = b[i];
                ret = s.toInteger(seter);
            }
            buffer[j * width + i] = seter;
        }
    }

    cout << "\n";
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            cout << buffer[j * width + i] << " ";
        }
        cout << "\n";
    }
    cout << "\n";

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

    for (int j = 0; j < height; j++)
    {
        int temp = buffer[j * width + max_summ_index];
        buffer[j * width + max_summ_index] = buffer[j * width + min_summ_index];
        buffer[j * width + min_summ_index] = temp;
    }
    
    for (int j = 0; j < height; j++)
    {
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
