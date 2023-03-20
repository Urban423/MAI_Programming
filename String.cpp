#include "String.h"
#include "List.h"
#include "Math.h"
#include <conio.h>
#include <stdio.h>

String::String()
{
    str = new char[1];
    str[0] = '\0';
    size = 1;
}

String::String(const char* string)
{
    size = 0;
    unsigned int i = 0;
    while (1)
    {
        this->size++;
        if (string[i] == '\0')
        {
            break;
        }
        i++;
    }
    str = new char[size];
    for (int i = 0; i < size ; i++)
    {
        str[i] = string[i];
    }
}

String::String(const String& string)
{
    size = string.size;
    if (str != nullptr)
    {
        delete[] str;
    }
    str = new char[size];
    for (unsigned int i = 0; i < size; i++)
    {
        str[i] = string.str[i];
    }
}

String::~String()
{
    if (str)
    {
        delete[] str;
    }
}

const char* String::c_str()
{
    return (const char*)str;
}

unsigned int String::getSize()
{
    return size;
}


char String::toInteger(int& number)
{
    number = 0;
    bool flag = 0; 
    unsigned int i = 0;
    if (str[0] == '-')
    {
        i++;
        flag = 1;
    }
    for (; i < size - 1; i++)
    {
        if (is_number(str[i]) == 1)
        {
            number *= 10;
            number += str[i] - 48;
        }
        else
        {
            printf("couldn't convert '%s' from string to Integer!\n", (const char*)str);
            return 0;
        }
    }
    if (flag)
    {
        number *= -1;
    }

    return 1;
}

/*
char String::toInteger(unsigned int& number)
{
    number = 0;
    for (unsigned int i = 0; i < size - 1; i++)
    {
        if (is_number(str[i]) == 1)
        {
            number *= 10;
            number += str[i] - 48;
        }
        else 
        {
            printf("couldn't convert from string to Integer!\n");
            return 0;
        }
    }
    return 1;
}*/

char String::split(char**& buffer, int& buffer_size, unsigned char split_letter)
{
    if (buffer != nullptr)
    {
        for (int i = 0; i < buffer_size; i++)
        {
            delete[] buffer[i];
        }
        delete[] buffer;
    }
    buffer_size = 0;
    bool flag = 0;
    unsigned int first_index = 0;
    unsigned int index = 0;
    for (unsigned int i = 0; i < size; i++)
    {
        if (str[i] == 13)
        {
            continue;
        }
        if (str[i] == '\0')
        {
            if (flag)
            {
                buffer_size++;
            }
        }

        if (str[i] == split_letter)
        {
            if (flag)
            {
                flag = 0;
                buffer_size++;
            }
        }
        else
        {
            flag = 1;
        }
    }
    buffer = new char*[buffer_size];
    for (unsigned int i = 0; i < size; i++)
    {
        if (str[i] == split_letter || str[i] == '\0' || str[i] == 13)
        {
            int sizer = i - first_index;
            if (sizer == 0)
            {
                first_index = i + 1;
                continue;
            }
            buffer[index] = new char[sizer + 1];
            buffer[index][sizer] = '\0';
            int j = first_index;
            unsigned int index_inside = 0;
            while (j < i)
            {
                buffer[index][index_inside] = str[j];
                index_inside++;
                j++;
            }
            index++;
            first_index = i + 1;
        }
    }
    return 1;
}

char String::writeText(String& string)
{
    if (string.str != nullptr)
    {
        delete[] string.str;
        string.str = nullptr;
    }
    string.size = 0;
    custom_list* list = nullptr;
    char ch;
    while (1)
    {
        ch = _getch();
        if (ch == 13)
        {
            printf("\n");
            break;
        }
        else if (ch == '\b')
        {
            if (list != nullptr)
            {
                if (list->getNext() != nullptr)
                {
                    list->removeLast();
                }
                else {
                    delete list;
                    list = nullptr;
                }
                printf("\b \b");
                string.size--;
            }
            continue;
        }

        if (list == nullptr)
        {
            list = new custom_list(ch);
        }
        else {
            list->add(ch);
        }
        string.size++;
        printf("%c", ch);
    }
    string.str = new char[string.size + 1];
    string.str[string.size] = '\0';
    custom_list* first_el = list;
    for (int i = 0; i < string.size; i++)
    {
        string.str[i] = list->get();
        list = list->getNext();
    }
    if (first_el)
    {
        first_el->deleteList();
    }
    string.size++;

    if (string.str == nullptr)
    {
        return 0;
    }
    return 1;
}

char String::readFromFile(String& string, const char* fileName, char show_content)
{
    custom_list* list = nullptr;

    FILE* file;
    fopen_s(&file, fileName, "rb");
    if (show_content)
    {
        printf("        file contaiment: \n'");
    }
    if (file)
    {
        string.size = 0;
        if (string.str != nullptr)
        {
            delete[] string.str;
        }

        char ch = ' ';
        while (1)
        {
            ch = fgetc(file);
            if (ch == -1)
            {
                break;
            }
            if (list == nullptr)
            {
                list = new custom_list(ch);
            }
            else {
                list->add(ch);
            }
            string.size++;

            if (show_content)
            {
                printf("%c", ch);
            }
        }
        if (show_content)
        {
            printf("'\n");
        }

        string.str = new char[string.size + 1];
        string.str[string.size] = '\0';
        custom_list* first_el = list;
        for (int i = 0; i < string.size; i++)
        {
            string.str[i] = list->get();
            list = list->getNext();
        }
        if (first_el)
        {
            first_el->deleteList();
        }
        string.size++;

        if (string.str == nullptr)
        {
            return 0;
        }
        fclose(file);
        return 1;
    }
    printf("        file dosn't exist;\n");
    return 0;
}

char String::boolean(String& string)
{
    String helper;
    char* helper_string = nullptr;
    size_t helper_size = 0;
    size_t counter = 0;
    size_t boolean_size = pow(2, string.size - 1);
    unsigned char* boolean = new unsigned char[boolean_size];
    for (int i = 1; i < boolean_size; i++)
    {
        helper_size = 0;
        for (int j = 0; j < string.size; j++)
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
        for (int j = 0; j < string.size; j++)
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

char String::permutations(String& string, bool repeat)
{
    size_t max_number = 0;
    size_t max_number_index = 0;
    size_t min_el_index = string.size - 1;
    size_t fa = factorial(string.size - 1);
    if (repeat)
    {
        char dictionary[256] = { 0 };
        for (int i = 0; i < string.size - 1; i++)
        {
            dictionary[string[i]]++;
        }
        for (int i = 0; i < 256; i++)
        {
            fa /= factorial(dictionary[i]);
        }
    }
    char* massive = new char[string.size - 1];

    for (int i = 0; i < string.size - 1; i++)
    {
        massive[i] = string[i];
    }

    for (int j = 0; j < string.size - 1; j++)
    {
        printf("%c", massive[j]);
    }
    printf("\n");

    for (int i = 0; i < fa - 1; i++)
    {
        for (int j = 0; j < string.size - 2; j++)
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

        size_t temp = massive[max_number_index];
        massive[max_number_index] = massive[min_el_index];
        massive[min_el_index] = temp;

        for (int i1 = min_el_index + 1, j = string.size - 2; i1 < j; ++i1, --j)
        {
            temp = massive[j];
            massive[j] = massive[i1];
            massive[i1] = temp;
        }

        for (int j = 0; j < string.size - 1; j++)
        {
            printf("%c", massive[j]);
        }
        printf("\n");
    }
    //printf("\n");
    return 1;
}

char String::bruteForce(String& string)
{
    int min_size = 0;
    int mini_summ = 0;
    int size = string.size - 1;
    char* summ = new char[size];
    for (int i = 0; i < size; i++)
    {
        summ[i] = 0;
    }
    unsigned int n = pow(string.size , size) - 1;

    for (unsigned int i = 0; i < n; i++)
    {
        summ[0]++;
        for (int j = 0; j < size; j++)
        {
            if (summ[j] < string.size)
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

char& String::operator[](unsigned int index)
{
    if (index >= size - 1)
    {
        return str[index - 2];
    }
    return str[index];
}

bool String::operator==(const char* str2)
{
    unsigned int size_str2 = 0;
    unsigned int i = 0;
    while (1)
    {
        size_str2++;
        if (str[i] == '\0')
        {
            break;
        }
        i++;
    }
    if (size != size_str2)
    {
        return 0;
    }
    for (int i = 0; i < size; i++)
    {
        if (str[i] != str2[i])
        {
            return 0;
        }
    }
    return 1;
}

void String::operator=(const char* string)
{
    if (str != nullptr)
    {
        delete[] str;
    }
    size = 0;
    unsigned int i = 0;
    while (1)
    {
        this->size++;
        if (string[i] == '\0')
        {
            break;
        }
        i++;
    }
    str = new char[size];
    for (int i = 0; i < size; i++)
    {
        str[i] = string[i];
    }
}