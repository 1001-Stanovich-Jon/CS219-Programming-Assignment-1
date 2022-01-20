// CS219:  Programming Assignment 1
// File: main.cpp
// Author: Jon Stanovich-Rubalcava
// Date Created: 19 January 2022

/*
Sources

Converting string to Numeric Values >> https://docs.microsoft.com/en-us/cpp/c-runtime-library/string-to-numeric-value-functions?view=msvc-170
File Handling Reference >> https://www.cplusplus.com/reference/cstdio/fscanf/

/*
Reads from an input file with the following format:

    OPERATION OPERAND_1 OPERAND_2

Then OPERATION is performed on OPERAND_1 and OPERAND_2
*/
#define MAX_FILENAME_SIZE 100
#define MAX_OPSIZE 25 //Maximum size of OPERATION specifier and OPERANDs


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Prototypes
unsigned long int ADD_OPERANDS(unsigned long int OP1, unsigned long int OP2);

int main(void)
{

    //Checking Input File
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

    //Reading Input File
    while (fscanf(input_file, "%s %s %s", OPERATION, STR_OPERAND1, STR_OPERAND2) != EOF )
    {

        char **junk;

        OPERAND1 = strtoul(STR_OPERAND1, junk, 16);
        OPERAND2 = strtoul(STR_OPERAND2, junk, 16);

        if (strcmp(OPERATION, "ADD") == 0)
            {
                unsigned long int sum_of_operands = ADD_OPERANDS(OPERAND1, OPERAND2);
                int message_space = 20;
                printf("\n%*s: %15lu\n",message_space, "Operand 1 (Decimal)", OPERAND1);
                printf("%*s: %15lu\n",message_space, "Operand 2 (Decimal)", OPERAND2);
                printf("%*s: %15s\n",message_space, "Operation", OPERATION);
                printf("%*s: %15lu\n\n",message_space, "Result", sum_of_operands);
            }

    }
    
    fclose(input_file);

    return (0);
}



//Functions

unsigned long int ADD_OPERANDS(unsigned long int OP1, unsigned long int OP2)
{
    return (OP1 + OP2);
};