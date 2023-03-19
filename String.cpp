#include "String.h"
#include "List.h"
#include "Math.h"
#include <conio.h>
#include <stdio.h>

String::String()
{
    str = nullptr;
    size = 0;
}

String::String(const char* str)
{
    size = 0;
    unsigned int i = 0;
    while (1)
    {
        this->size++;
        if (str[i] == '\0')
        {
            break;
        }
        i++;
    }
    this->str = new char[size];
    for (int i = 0; i < this->size; i++)
    {
        this->str[i] = str[i];
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
}

char String::split(char**& buffer, unsigned int& buffer_size, unsigned char split_letter)
{
    buffer_size = 0;
    bool flag = 0;
    unsigned int first_index = 0;
    unsigned int index = 0;
    for (unsigned int i = 0; i < size; i++)
    {
        if (str[i] == '\0')
        {
            buffer_size++;
        }
        if (str[i] == split_letter && flag)
        {
            flag = 0;
            buffer_size++;
        }else
        {
            flag = 1;
        }
    }
    buffer = new char*[buffer_size];
    for (unsigned int i = 0; i < size; i++)
    {
        if (str[i] == split_letter || str[i] == '\0')
        {
            int sizer = i - first_index;
            if (sizer == 0)
            {
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

char String::readFromFile(String& string, const char* fileName)
{
    string.size = 0;
    custom_list* list = nullptr;

    FILE* file;
    fopen_s(&file, fileName, "rb");
    printf("        file contaiment: '");
    if (file)
    {
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
            printf("%c", ch);
        }
        printf("'\n");

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

        if (string.str == nullptr)
        {
            return 0;
        }
        fclose(file);
        return 1;
    }
    printf("        file dosn't exist;");
    return 0;
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
