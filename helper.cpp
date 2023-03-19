#include "helper.h"
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include "Math.h"

char bruteForce(char*& string, size_t& size)
{
    char* helper_string = nullptr;
    size_t helper_size = 0;
    size_t counter = 0;
    size_t boolean_size = pow(2, size);
    unsigned char* boolean = new unsigned char[boolean_size];
    for (int i = 1; i < boolean_size; i++)
    {
        helper_size = 0;
        for (int j = 0; j < size; j++)
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
        helper_string = new char[helper_size];
        for (int j = 0; j < size; j++)
        {
            if ((i >> j) & 1)
            {
                helper_string[counter] = string[j];
                counter++;
            }
        }
        permutations(helper_string, helper_size);
    }
    printf("\n");
    return 0;
}

char permutations(char*& string, size_t& size)
{
    size_t max_number = 0;
    size_t max_number_index = 0;
    size_t min_el_index = size;
    size_t fa = factorial(size);
    size_t* massive = new size_t[size];
    for (int i = 0; i < size; i++)
    {
        massive[i] = i;
    }
    for (int i = 0; i < fa; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if (max_number > massive[j + 1])
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
        std::cout << massive[max_number_index] << " " << massive[min_el_index] << "\n";
        size_t temp = massive[max_number_index];
        massive[max_number_index] = massive[min_el_index];
        massive[min_el_index] = temp;
        for (int i = size - 1; i > 2; i++)

            for (int j = 0; j < size; j++)
            {
                std::cout << massive[j];
            }
        printf("\n");
    }
    printf("\n");
    return 0;
}
