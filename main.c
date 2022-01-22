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
    Reads from an input file with the following format(s):

        General Form:
            OPERATION OPERANDS

    Then the OPERATION is performed on the operands.
    Operations and Output will be dependent on the assignment guidelines.

        Project 1's Form:
            Expected Input: ADD HEX_NUMBER_1 HEX_NUMBER_2
            Output: Display the sum (in HEX) in a readable way.



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
    unsigned int run_count = 0; //Displayed for each run, also used to prevent infinite while

    //Read from input file and perform operation
    while (fscanf(input_file, "%s %s %s", OPERATION, STR_OPERAND1, STR_OPERAND2) != EOF && run_count < 100)
    {
        printf("\nRUN %d\n", run_count);

        char **junk; //junk pointer, needed for stroul(), no real functionality for its particular use in this program

        OPERAND1 = strtoul(STR_OPERAND1, junk, 16);
        OPERAND2 = strtoul(STR_OPERAND2, junk, 16);

        if (strcmp(OPERATION, "ADD") == 0)
            {
                int message_space = 20;
                int message_length = 250;

                char * output_format = "%*s: 0x%010lX\n%*s: 0x%010lX\n%*s: %12s\n%*s: 0x%010lX\n\n";
                char output_message[message_length];
                _Bool print_hex = 1; //Change to 0 to output decimal

                if (!print_hex)
                    output_format = "%*s: %12lu\n%*s: %12lu\n%*s: %12s\n%*s: %12lu\n\n";

                snprintf(output_message, (message_length-1), output_format,
                message_space, "Operand 1 ", OPERAND1,
                message_space, "Operand 2 ", OPERAND2,
                message_space, "Operation ", OPERATION,
                message_space, "Result ", OPERAND1 + OPERAND2);

                printf("%s", output_message);

            }
        run_count++;

    }
    
    fclose(input_file);

    return (0);
}