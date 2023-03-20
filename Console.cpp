#include "Console.h"
#include <stdio.h>
#include <stdlib.h>
#include "Laba1.h"
#include "Laba2.h"

const unsigned int commands_size = 12;
const char* const commands[]
{
     "help",
    "0",
     "exit",
    "1",
     "brute force",
    "2",
     "make laba1",
    "3",
     "make laba2",
    "4", 
    "permutations",
    "5",
};

char commandLine()
{
    String command;
    while (1)
    {
        system("title Console");
        printf("write command: ");
        if (!String::writeText(command)) {
            return -1;
        }
        if (command == commands[0] || command == commands[1]) {
            printf("commands:\n");
            for (int i = 0; i < commands_size; i+=2)
            {
                printf("    %s: %s\n", commands[i + 1], commands[i]);
            }
        }
        else if (command == commands[2] || command == commands[3]) {
            return 0;
        }
        else if (command == commands[4] || command == commands[5]) {
            printf("    write alphabet: ");
            if (!String::writeText(command)) {
                return -1;
            }
            String::bruteForce(command);
        }
        else if (command == commands[6] || command == commands[7]) {
            laba1();
        }
        else if (command == commands[8] || command == commands[9]) {
            laba2();
        }
        else if (command == commands[10] || command == commands[11]) {
            printf("    write alphabet: ");
            if (!String::writeText(command)) {
                return -1;
            }
            String::permutations(command);
        }
        else
        {
            printf("command '%s' unknown, please try again.\n", command.c_str());
        }
        printf("\n");
    }
    return 1;
}