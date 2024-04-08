/* Antonio Urdaneta 
CGS3269 04/08/2024 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defining constants opCodes and specifying array sizes for the Instruction Set Architecture cycles
#define LOAD 1
#define ADD 2
#define STORE 3
#define SUB 4
#define IN 5
#define OUT 6
#define END 7
#define JMP 8
#define SKIPZ 9
#define PROGRAM_SIZE 100
#define DM_ARRAY_SIZE 10//DM stands for Data Memory

typedef struct {
    int opCode, address;
} Instruction;

//Global variables that represent the registers and components of 
//Tiny Harvard Architecture ISA
int PC = 0;
int MAR1 = 0;
int MAR2 = 0;
Instruction MDR1;
int MDR2 = 0;
int A = 0;
int DM[DM_ARRAY_SIZE];
Instruction IM[PROGRAM_SIZE];// IM stands for Instruction Memory (program memory)
Instruction IR;

int main(int argc, char** argv)
{
// Openning and reading input1.txt file
    char *name = argv[1];
    FILE *input_file = fopen(name,"r");
    int j = 0;

// Check if the input file pointer is NULL,
// indicating failure to open the file.
    if(input_file == NULL)
    {
        printf("No file found\n");
        return 1;
    }
// If the input file was opened successfully,
// read data from the file until reaching the end of the file EOF.
    else
    {
        while(fscanf(input_file,"%d%d", &IM[j].opCode, &IM[j].address)!= EOF)
        {
            j++;
        }
        fclose(input_file);
    }

    printf("\nAssembling Program...\n");
    printf("Program Assembled.\n");
    printf("Run.\n\n");

    int run = 1;

    while (run == 1)
    {
        
    // FETCH Instruction
        MAR1 = PC;
        PC+=2;
        MDR1 = IM[MAR1];
        IR = MDR1;

        switch(IR.opCode)
        {
    // LOAD instruction 
            case LOAD:
               printf("Loading value from memory location %d into the accumulator\n", IR.address);
                MAR2 = IR.address;
                MDR2 = DM[MAR2];
                A = MDR2;
                break;

    // ADD instruction 
            case ADD:
                printf("Adding value from memory location %d to the accumulator\n", IR.address);
                MAR2 = IR.address;
                MDR2 = DM[MAR2];
                A = A + MDR2;
                break;

    // STORE instruction 
            case STORE:
            printf("Storing the value of the accumulator to memory location %d\n", IR.address);
                MAR2 = IR.address;
                MDR2 = A;
                DM[MAR2] = MDR2;
                break;

    // SUB instruction 
            case SUB:
            printf("Subtracting the value at memory location %d from the accumulator\n", IR.address);
                MAR2 = IR.address;
                MDR2 = DM[MAR2];
                A = A - MDR2;
                break;

    // INPUT instruction 
            case IN:
                printf("Input device number:\n");
                printf("%d\n", IR.address);
                A = IR.address;
                break;

    // OUT instruction 
            case OUT:
                printf("Outputting accumulator to screen\n");
                printf("%d\n", A);
                break;

    // END instruction 
            case END:
                printf("End of execution\n");
                run = 0;
                break;

    // JUMP instruction 
            case JMP:
                printf("Jumping to memory address %d\n", IR.address);
                PC = IR.address;
                break;

    // SKIPZ instruction
            case SKIPZ:
                printf("Checking if the accumulator equals 0\n");
                if (A == 0)
                {
                    printf("Checking if the accumulator equals 0\n");
                    PC += 2;
                }
                else
                    printf("False; executing the next instruction\n");
                break;

    //No execution for default case
            default:
                printf("Invalid instruction\n");
        }

    //Printing the PC, A, and the DM to user after every instruction
        printf("PC = %d | A = %d | DM = [", PC, A);
        for (int i = 0; i < DM_ARRAY_SIZE; i++)
        {
            if (i == DM_ARRAY_SIZE - 1)
                printf("%d]\n\n", DM[i]);
            else 
                printf("%d, ", DM[i]);
        }
    }
    printf("Program Complete\n");
    return 0;
}