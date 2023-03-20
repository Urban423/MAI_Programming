#include "Math.h"

unsigned int factorial(unsigned int a)
{
    unsigned int ret = 1;
    for (int i = 2; i < a + 1; i++)
    {
        ret *= i;
    }
    return ret;
}

unsigned int pow(unsigned int a, unsigned int b)
{
    unsigned int ret = 1;
    for (int i = 0; i < b; i++)
    {
        ret *= a;
    }
    return ret;
}

unsigned int pow(int a, int b)
{
    int ret = 1;
    for (int i = 0; i < b; i++)
    {
        ret *= a;
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