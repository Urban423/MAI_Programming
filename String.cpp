#include "String.h"
#include "List.h"
#include "Math.h"
#include <conio.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>

String::String()
{
    str = new int[1];
    str[0] = '\0';
    size = 0;
}

String::String(const char* string)
{
    size = 0;
    unsigned int i = 0;
    while (1)
    {
        if (string[i] == '\0')
        {
            break;
        }
        this->size++;
        i++;
    }
    str = new int[size + 1];
    str[size] = 0;
    for (unsigned int i = 0; i < size ; i++)
    {
        str[i] = string[i];
    }
}

String::String(const int* string)
{
    size = 0;
    unsigned int i = 0;
    while (1)
    {
        if (string[i] == '\0')
        {
            break;
        }
        this->size++;
        i++;
    }
    str = new int[size + 1];
    str[size] = 0;
    for (unsigned int i = 0; i < size; i++)
    {
        str[i] = string[i];
    }
}

String::String(const String& string)
{
    size = string.size;
    str = new int[size + 1];
    for (unsigned int i = 0; i < size; i++)
    {
        str[i] = string.str[i];
    }
    str[size] = 0;
}

String::~String()
{
    if (str != nullptr)
    {
        //delete[] str;
    }
}

const char* String::c_str()
{
    char* text = new char[size + 1];
    text[size] = 0;
    for (unsigned int i = 0; i < size; i++)
    {
        text[i] = str[i];
    }
    return (const char*)text;
}

int*& String::getText()
{
    return str;
}

unsigned int& String::getSize()
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
    for (; i < size; i++)
    {
        if (is_number(str[i]) == 1)
        {
            number *= 10;
            number += str[i] - 48;
        }
        else
        {
            return 1;
        }
    }
    if (flag)
    {
        number *= -1;
    }

    return 0;
}

char String::toFloat(float& number)
{
    number = 0;
    float helper = 0.1f;
    unsigned char flag = 0;
    unsigned char flag_points = 0;
    for (unsigned int i = 0; i < size - 1; i++)
    {
        if (str[i] == '.' || str[i] == ',')
        {
            flag = 1;
            flag_points++;
            continue;
        }

        if (is_number(str[i]) == 1 && flag_points < 2)
        {
            if (flag == 0)
            {
                number *= 10;
                number += str[i] - 48;
            }
            else
            {
                number += (str[i] - 48) * helper;
                helper /= 10;
            }
        }
        else 
        {
            printf("couldn't convert from string to Integer!\n");
            return 0;
        }
    }
    return 1;
}

char String::split(String*& buffer, int& buffer_size, unsigned char split_letter)
{
    buffer_size = 0;
    bool flag = 0;
    unsigned int first_index = 0;
    unsigned int index = 0;
    for (unsigned int i = 0; i < size + 1; i++)
    {
        if (str[i] == '\0')
        {
            if (flag)
            {
                buffer_size++;
            }
        }

        if (str[i] == split_letter || str[i] == 13)
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

    buffer = new String[buffer_size];
    for (unsigned int i = 0; i < size + 1; i++)
    {
        if (str[i] == split_letter || str[i] == '\0' || str[i] == 13)
        {
            int sizer = i - first_index;
            if (sizer == 0)
            {
                first_index = i + 1;
                continue;
            }

            buffer[index].str = new int[sizer + 1];
            buffer[index].size = sizer;
            buffer[index].str[sizer] = '\0';
            unsigned int j = first_index;
            unsigned int index_inside = 0;
            while (j < i)
            {
                buffer[index].str[index_inside] = str[j];
                index_inside++;
                j++;
            }
            index++;
            first_index = i + 1;
        }
    }
    return 1;
}

char String::replaceSymbol(String& buffer, char SymbolToReplace, char replacement)
{
    for (unsigned int i = 0; i < buffer.getSize(); i++)
    {
        if (buffer[i] == SymbolToReplace)
        {
            buffer[i] = replacement;
        }
    }
    return 0;
}

char String::removeSymbol(int SymbolToRemove)
{
    unsigned int new_size = 0;
    for (unsigned int i = 0; i < size; i++)
    {
        if (str[i] != SymbolToRemove)
        {
            new_size++;
        }
    }
    int* new_str = new int[new_size + 1];
    unsigned int index = 0;
    
    for (unsigned int i = 0; i < size; i++)
    {
        if (str[i] != SymbolToRemove)
        {
            new_str[index] = str[i];
            index++;
        }
    }
    new_str[new_size] = '\0';
    str = new_str;
    size = new_size;

    return 0;
}

char String::add(unsigned int index, int Symbol)
{
    int new_index = 0;
    int* new_str = new int[size + 2];
    for (unsigned int i = 0; i < size; i++)
    {
        if (new_index == index) {
            new_str[new_index] = Symbol;
            new_index++;
        }
        new_str[new_index] = str[i];
        new_index++;
    }
    new_str[size + 1] = 0;

    delete[] str;
    str = new_str;
    size++;
    return 0;
}

char String::remove(unsigned int index)
{
    int new_index = 0;
    int* new_str = new int[size];
    for (unsigned int i = 0; i < size; i++)
    {
        if (index == i) { continue; }
        new_str[new_index] = str[i];
        new_index++;
    }
    new_str[size - 1] = 0;

    delete[] str;
    str = new_str;
    size--;
    return 0;
}

char String::IntegerToString(String& buffer, int number, int showError)
{
    int temp = number;
    int size = 0;
    while (temp > 0)
    {
        temp /= 10;
        size++;
    }
    int* text = new int[size + 1];
    text[size] = '\0';
    for (int i = 0; i < size; i++)
    {
        text[i] = number % 10 + 48;
        number /= 10;
    }
    for (int i = 0, j = size - 1; i < j; i++, j--)
    {
        int t = text[i];
        text[i] = text[j];
        text[j] = t;
    }
    buffer.str = text;
    buffer.size = size;
    return 0;
}

int& String::operator[](unsigned int index)
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
        if (str[i] == '\0')
        {
            break;
        }
        size_str2++;
        i++;
    }
    if (size != size_str2)
    {
        return 0;
    }
    for (unsigned int i = 0; i < size; i++)
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
        if (string[i] == '\0')
        {
            break;
        }
        this->size++;
        i++;
    }
    str = new int[size + 1];
    str[size] = '\0';
    for (unsigned int i = 0; i < size; i++)
    {
        str[i] = string[i];
    }
}

void String::operator=(const wchar_t* string)
{
    size = 0;
    unsigned int i = 0;
    while (1)
    {
        if (string[i] == '\0')
        {
            break;
        }
        this->size++;
        i++;
    }
    str = new int[size + 1];
    str[size] = '\0';
    for (unsigned int i = 0; i < size; i++)
    {
        str[i] = string[i];
    }
}



void String::operator=(String& string)
{
    

    size = string.size;
    str = new int[size + 1];
    for (unsigned int i = 0; i < size; i++)
    {
        str[i] = string.str[i];
    }
    str[size] = 0;
}

char printUTF8(String& str)
{
    int res = _setmode(_fileno(stdout), _O_U16TEXT);
    for (unsigned int i = 0; i < str.getSize(); i++)
    {
        wprintf(L"%c", str.getText()[i]);
    }
    res = _setmode(_fileno(stdout), _O_TEXT);
    return 0;
}

char writeText(String& string)
{
    if (string.getText() != nullptr)
    {
        delete[] string.getText();
    }
    string.getSize() = 0;
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
                string.getSize()--;
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
        string.getSize()++;
        printf("%c", ch);
    }
    string.getText() = new int[string.getSize() + 1];
    string.getText()[string.getSize()] = '\0';
    custom_list* first_el = list;
    for (unsigned int i = 0; i < string.getSize(); i++)
    {
        string.getText()[i] = list->get();
        list = list->getNext();
    }
    if (first_el)
    {
        first_el->deleteList();
    }

    return 0;
}

char readFromFile(String& string, const char* fileName)
{
    //init values
    FILE* file;
    int bitsToMove = 0;
    int character = 0;
    int last = 0;
    unsigned int FileSize = 0;
    int index = 0;

    //open file
    fopen_s(&file, fileName, "rb");
    if (!file) {
        return 1;
    }

    //clear string buffer
    string.getSize() = 0;

    //get file size
    while (1)
    {
        //read Byte from file
        character = fgetc(file);
        if (character == -1) {
            if (last != 0) {
                string.getSize()++;
            }
            break;
        }
        FileSize++;

        //check unicode
        if (((character >> 7) & 0x01) == 1 && ((character >> 6) & 0x01) == 1 && ((character >> 5) & 0x01) == 0)
        {
            if (last != 0)
            {
                string.getSize()++;
            }
            last = (unsigned char)(character - 128 - 64);
            bitsToMove = 6;
        }
        else if (((character >> 7) & 0x01) == 1 && ((character >> 6) & 0x01) == 0)
        {
            last <<= bitsToMove;
            last += (unsigned char)(character - 128);
            bitsToMove = 3;
        }
        else {
            if (last != 0) {
                string.getSize()++;
            }
            string.getSize()++;
            last = 0;
        }
    }

    //return to the file begin
    fseek(file, 0, SEEK_SET);
    
    //set string data
    string.getText() = new int[string.getSize() + 1];
    string.getText()[string.getSize()] = '\0';
    
    //read all bytes
    for (unsigned int i = 0; i < FileSize; i++)
    {
        //read byte
        character = fgetc(file);

        //decode byte
        if (((character >> 7) & 0x01) == 1 && ((character >> 6) & 0x01) == 1 && ((character >> 5) & 0x01) == 0)
        {
            if (last != 0) {
                string.getText()[index] = last;
                index++;
            }
            last = (unsigned char)(character - 128 - 64);
            bitsToMove = 6;
        }
        else if (((character >> 7) & 0x01) == 1 && ((character >> 6) & 0x01) == 0)
        {
            last <<= bitsToMove;
            last += (unsigned char)(character - 128);
            bitsToMove = 3;
        }
        else {
            if (last != 0) {
                string.getText()[index] = last;
                index++;
            }
            string.getText()[index] = character;
            index++;
            last = 0;
        }
    }

    //close file
    fclose(file);
    return 0;
}