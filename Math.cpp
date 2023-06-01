#include "Math.h"
#include "String.h"
#include <math.h>
#include <stdio.h>

unsigned int factorial(unsigned int a)
{
    unsigned int ret = 1;
    for (int i = 2; i < a + 1; i++)
    {
        ret *= i;
    }
    return ret;
}

bool is_letter(unsigned char letter)
{
    if (letter > 64 && letter < 91)
    {
        return true;
    }
    if (letter > 96 && letter < 123)
    {
        return true;
    }
    return false;
}

bool is_number(unsigned char letter)
{
    if (letter > 47 && letter < 58)
    {
        return true;
    }
    return false;
}

char boolean(String& string)
{
    String helper;
    char* helper_string = nullptr;
    size_t helper_size = 0;
    size_t counter = 0;
    size_t boolean_size = pow(2, string.getSize() - 1);
    unsigned char* boolean = new unsigned char[boolean_size];
    for (unsigned int i = 1; i < boolean_size; i++)
    {
        helper_size = 0;
        for (unsigned int j = 0; j < string.getSize(); j++)
        {
            if ((i >> j) & 1)
            {
                helper_size++;
            }
        }
        if (helper_string != nullptr)
        {
            delete[] helper_string;
        }
        counter = 0;
        helper_string = new char[helper_size + 1];
        helper_string[helper_size] = 0;
        for (unsigned int j = 0; j < string.getSize(); j++)
        {
            if ((i >> j) & 1)
            {
                helper_string[counter] = string[j];
                counter++;
            }
        }
        helper = helper_string;
        printf("%s\n", helper.c_str());
    }
    printf("\n");
    return 0;
}

char permutations(String& string, bool repeat)
{
    size_t max_number = 0;
    size_t max_number_index = 0;
    size_t min_el_index = string.getSize() - 1;
    size_t fa = factorial(string.getSize() - 1);
    if (repeat)
    {
        char dictionary[256] = { 0 };
        for (unsigned int i = 0; i < string.getSize() - 1; i++)
        {
            dictionary[string[i]]++;
        }
        for (int i = 0; i < 256; i++)
        {
            fa /= factorial(dictionary[i]);
        }
    }
    char* massive = new char[string.getSize() - 1];

    for (unsigned int i = 0; i < string.getSize() - 1; i++)
    {
        massive[i] = string[i];
    }

    for (unsigned int j = 0; j < string.getSize() - 1; j++)
    {
        printf("%c", massive[j]);
    }
    printf("\n");

    for (unsigned int i = 0; i < fa - 1; i++)
    {
        for (unsigned int j = 0; j < string.getSize() - 2; j++)
        {
            if (max_number >= massive[j + 1] && massive[min_el_index] < massive[j + 1])
            {
                max_number_index = j + 1;
                max_number = massive[j + 1];
            }
            if (massive[j] < massive[j + 1])
            {
                max_number_index = j + 1;
                max_number = massive[j + 1];
                min_el_index = j;
            }
        }

        char temp = massive[max_number_index];
        massive[max_number_index] = massive[min_el_index];
        massive[min_el_index] = temp;

        for (int i1 = min_el_index + 1, j = string.getSize() - 2; i1 < j; ++i1, --j)
        {
            temp = massive[j];
            massive[j] = massive[i1];
            massive[i1] = temp;
        }

        for (unsigned int j = 0; j < string.getSize() - 1; j++)
        {
            printf("%c", massive[j]);
        }
        printf("\n");
    }
    //printf("\n");
    return 1;
}

char bruteForce(String& string)
{
    int min_size = 0;
    int mini_summ = 0;
    int size = string.getSize() - 1;
    char* summ = new char[size];
    for (int i = 0; i < size; i++)
    {
        summ[i] = 0;
    }
    unsigned int n = pow(string.getSize(), size) - 1;

    for (unsigned int i = 0; i < n; i++)
    {
        summ[0]++;
        for (int j = 0; j < size; j++)
        {
            if (summ[j] < string.getSize())
            {
                if (min_size < j + 1)
                {
                    min_size = j + 1;
                }
                break;
            }
            summ[j] = 0;
            if (j + 1 < size)
            {
                summ[j + 1]++;
            }
        }
        mini_summ = 0;
        for (int j = 0; j < size; j++)
        {
            if (summ[j] != 0)
            {
                mini_summ++;
            }
        }
        if (mini_summ < min_size)
        {
            continue;
        }
        for (int j = size - 1; j > -1; j--)
        {
            if (summ[j] == 0)
            {
                continue;
            }
            printf("%c", string[summ[j] - 1]);
        }
        printf("\n");
    }
    printf("\n");
    return 1;
}