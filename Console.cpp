#include "Console.h"
#include <stdio.h>
#include "Laba1.h"
#include "Laba2.h"

const unsigned int commands_size = 14;
const char* const commands[]
{
    "fill buffer from file",
    "0",
     "fill buffer from input",
    "1",
     "help",
    "2",
     "exit",
    "3",
     "brute force",
    "4",
     "make laba1",
    "5",
     "make laba2",
    "6",
};

char commandLine(String& string)
{
    String command;
    while (1)
    {
        printf("write command: ");
        if (!String::writeText(command)) {
            return -1;
        }
        if (command == commands[0] || command == commands[1])
        {
            printf("    write filename: ");
            if (!String::writeText(command)) {
                return -1;
            }
            if (!String::readFromFile(string, command.c_str())) {
                return -1;
            }
        }
        else if (command == commands[2] || command == commands[3]) {
            printf("    write text: ");
            if (!String::writeText(string)) {
                return -1;
            }
        }
        else if (command == commands[4] || command == commands[5]) {
            printf("commands:\n");
            for (int i = 0; i < commands_size; i+=2)
            {
                printf("    %s: %s\n", commands[i + 1], commands[i]);
            }
            //printf("command 0: fill buffer from file\ncommand 1: read from console input\ncommand 2: help\ncommand 3: brute force\ncommand 4: exit\n\n");
        }
        else if (command == commands[6] || command == commands[7]) {
            return 0;
        }
        else if (command == commands[8] || command == commands[9]) {
            printf("    write alphabet: ");
            if (!String::writeText(string)) {
                return -1;
            }
            const char* stri = string.c_str();
            size_t si = string.getSize();
            //bruteForce(stri, si);
        }
        else if (command == commands[10] || command == commands[11]) {
            if (string.c_str() == nullptr)
            {
                printf("the buffer is empty! fill buffer first!\n\n");
                continue;
            }
            laba1(string);
        }
        else if (command == commands[12] || command == commands[13]) {
            laba2();
        }
        else
        {
            printf("command '%s' unknown, please try again.\n", command.c_str());
        }
        printf("\n");
    }
    return 1;
}