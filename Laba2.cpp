#include "Laba2.h"
#include <stdlib.h>
#include "String.h"
#include <iostream>
using namespace std;

int laba2()
{
    system("title Matrix");

    char ret = 0;
    String string;
    unsigned int width = 0;
    unsigned int height = 0;
    int* buffer = nullptr;
    int* mini_buffer = nullptr;

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
        ret = string.toInteger(height);
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

    }



    if (buffer != nullptr)
    {
        delete[] buffer;
    }

    return 0;
}
