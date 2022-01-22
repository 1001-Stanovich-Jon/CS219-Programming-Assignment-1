// CS219:  Programming Assignment 1
// File: main.cpp
// Author: Jon Stanovich-Rubalcava
// Date Created: 19 January 2022

/*
Sources

Converting string to Numeric Values >> https://docs.microsoft.com/en-us/cpp/c-runtime-library/string-to-numeric-value-functions?view=msvc-170
File Handling Reference >> https://www.cplusplus.com/reference/cstdio/fscanf/
Usage for strtoul >> https://www.cplusplus.com/reference/cstdlib/strtoul/
Output Formatting Help for Padding >> https://stackoverflow.com/questions/293438/left-pad-printf-with-spaces

The rest is from memory, old class notes, or "Problem Solving and Program Design in C" by Jeri R. Hanly & Elliot B. Koffman (ISBN: 9780134014890)
*/

//Fixed bad pointer usage in strtoul
//Fixed other pointer usage
//Changed main to accept file input via terminal

#define MAX_OPSIZE 25 //Maximum size of OPERATION specifier and OPERANDs
#define MAX_OPERAND_SIZE 50

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void RUN_ADDITION(FILE *, _Bool);

int main(int argc, char *argv[])
{
    /*
    Reads from an input file with the following format(s):

        General Form:
            OPERATION OPERANDS

    Then the OPERATION is performed on the operands.
    Operations and Output will be dependent on the assignment guidelines.

        Project 1's Form:
            Expected Input: ADD HEX_NUMBER_1 HEX_NUMBER_2
            Output: Display the sum (in HEX) in a readable way.
    */

    //Check for correct input and if file can be opened
    if (argc != 2)
        {
            printf("Correct usage: ./main <filename>\n");
            return 1;
        }

    FILE * input_file = NULL;
    input_file = fopen(argv[1], "r");

    if (input_file == NULL)
        {
            printf("Could not open %s \n",argv[1]);
            return 1;
        }

    char OPERATION[MAX_OPSIZE];
    unsigned int run_count = 0;
    _Bool print_hex = 1; //0 for decimal

    //Main Loop - Reads operation, calls appropriate function to run operation
    while (fscanf(input_file, "%s", OPERATION) != EOF && run_count < 100)
        {
            printf("\nRUN %d\n", run_count);

            if (strcmp(OPERATION, "ADD")==0)
                {

                    RUN_ADDITION(input_file, print_hex);
                    run_count++;
                }

            //ADD MORE OPERATION HERE IN THE FUTURE
        }

    fclose(input_file);

    return (0);
}



void RUN_ADDITION(FILE * input_file, _Bool print_hex)
{
    //The main while loop has already checked to make sure we have a valid line, so we will not do any checking here.
    //We should be guaranteed TWO operands for addition.
    //First we read in the two operands, and then add them toget, and display the output.

    char STR_OPERAND1[MAX_OPERAND_SIZE], STR_OPERAND2[MAX_OPERAND_SIZE];
    unsigned long long int OPERAND1 = 0, OPERAND2 = 0; 

    fscanf(input_file, "%s %s", STR_OPERAND1, STR_OPERAND2);

    OPERAND1 = strtoul(STR_OPERAND1, NULL, 16);
    OPERAND2 = strtoul(STR_OPERAND2, NULL, 16);

    int message_space = 20; //Padding
    int message_length = 500;

    char * output_format = "%*s: 0x%010lX\n%*s: 0x%010lX\n%*s: %12s\n%*s: 0x%010lX\n\n";
    char output_message[message_length];

    if (!print_hex)
        output_format = "%*s: %12lu\n%*s: %12lu\n%*s: %12s\n%*s: %12lu\n\n";

    snprintf(output_message, (message_length-1), output_format,
    message_space, "Operand 1 ", OPERAND1,
    message_space, "Operand 2 ", OPERAND2,
    message_space, "Operation ", "ADD",
    message_space, "Result ", OPERAND1 + OPERAND2);

    printf("%s", output_message);

    return;
}