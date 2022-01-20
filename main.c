// CS219:  Programming Assignment 1
// File: main.cpp
// Author: Jon Stanovich-Rubalcava
// Date Created: 19 January 2022

/*
Sources

Converting string to Numeric Values >> https://docs.microsoft.com/en-us/cpp/c-runtime-library/string-to-numeric-value-functions?view=msvc-170
File Handling Reference >> https://www.cplusplus.com/reference/cstdio/fscanf/
Output Formatting Help for Padding >> https://stackoverflow.com/questions/293438/left-pad-printf-with-spaces

The rest is from memory, old class notes, or "Problem Solving and Program Design in C" by Jeri R. Hanly & Elliot B. Koffman (ISBN: 9780134014890)
*/


#define MAX_FILENAME_SIZE 100
#define MAX_OPSIZE 25 //Maximum size of OPERATION specifier and OPERANDs

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    /*
    Reads from an input file with the following format:

        OPERATION OPERAND_1 OPERAND_2

    Then OPERATION is performed on OPERAND_1 and OPERAND_2
    */

    //Input file details
    FILE * input_file;
    char in_fname[MAX_FILENAME_SIZE] = "Programming-Project-1.txt";
    input_file = fopen(in_fname, "r");

    if (input_file == NULL)
        {
            printf("Could not open %s \n",in_fname);
            return 1;
        }

    char OPERATION[MAX_OPSIZE], STR_OPERAND1[MAX_OPSIZE], STR_OPERAND2[MAX_OPSIZE];
    unsigned long int OPERAND1, OPERAND2;

    //Read from input file and perform operation
    while (fscanf(input_file, "%s %s %s", OPERATION, STR_OPERAND1, STR_OPERAND2) != EOF )
    {

        char **junk; //junk pointer needed for strtoul, no functionality for this program

        OPERAND1 = strtoul(STR_OPERAND1, junk, 16);
        OPERAND2 = strtoul(STR_OPERAND2, junk, 16);

        if (strcmp(OPERATION, "ADD") == 0)
            {
               int message_space = 20;

                char outmessage[200];
                snprintf(outmessage, 199, "\n%*s: %15lu\n%*s: %15lu\n%*s: %15s\n%*s: %15lu\n\n",
                message_space,"Operand 1 (Decimal)", OPERAND1,
                message_space,"Operand 2 (Decimal)",OPERAND2,
                message_space,"Operation",OPERATION,
                message_space,"Result (Decimal)",OPERAND1 + OPERAND2);

                printf("%s", outmessage);

    /* Uncomment to print Hexadecimal numbers instead of decimal
                char outmessageHEX[200];
                snprintf(outmessageHEX, 199, "\n%*s: %15lX\n%*s: %15lX\n%*s: %15s\n%*s: %15lX\n\n",
                message_space, "Operand 1 (Hex)", OPERAND1,
                message_space, "Operand 2 (Hex)", OPERAND2,
                message_space, "Operation", OPERATION,
                message_space, "Result (Hex)", OPERAND1 + OPERAND2);

                printf("%s", outmessageHEX);
    */
            }

    }
    
    fclose(input_file);

    return (0);
}