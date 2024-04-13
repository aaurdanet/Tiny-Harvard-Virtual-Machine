#include <string.h>
#include <stdio.h>
#include <stdlib.h>


// Defining constants opCodes and specifying array sizes for the Instruction Set Architecture cyclesint PC = 0;
#define LOAD 1
#define ADD 2
#define STORE 3
#define SUB 4
#define IN 5
#define OUT 6
#define END 7
#define JMP 8
#define SKIPZ 9
#define MAXSIZE 100
#define DM_ARRAY_SIZE 10


typedef struct {
    int opcode, address;
} Instruction;

// Global variables that represent the registers and components of 
// Tiny Harvard Architecture ISA
int MAR1 = 0;
int MAR2 = 0;
int PC = 0;
Instruction MDR1;
int MDR2 = 0;
int A = 0;
int DM[DM_ARRAY_SIZE];
Instruction IM[MAXSIZE];// IM stands for Instruction Memory (program memory)
Instruction IR;


int main(int argc, char** argv)
{
    // Opening and reading input file
    char* input_file = argv[1];
    FILE* source_file = fopen("input_file", "r");
    int i = 0;

    // Check if the input file pointer is NULL,
    // indicating failure to open the file.
    if (source_file == NULL)
    {
        printf("Please open file from terminal/command line.\n");
        return 1;
    }
    // If the input file was opened successfully,
    // read data from the file until reaching the end of the file EOF.
    else
    {
        while (fscanf(source_file, "%d%d", &IM[i].opcode, &IM[i].address) != EOF)
        {
            i++;
        }
        fclose(source_file);
    }

    printf("\nAssembling Program...\n");
    printf("Program Assembled.\n");
    printf("\nRunning\n\n");

    int halt = 1;

    while (halt == 1) {
        // FETCH Instruction
        MAR1 = PC;
        IR = IM[MAR1];

        // Execute instruction based on opcode
        switch (IR.opcode)
        {
            // LOAD instruction
        case LOAD:
            printf("Loading value at memory location %d to A:\n", IR.address);
            MAR2 = IR.address;
            MDR2 = DM[MAR2];
            A = MDR2;
            break;
            // ADD instruction
        case ADD:
            printf("Adding value from memory location %d to the accumulator\n", IR.address);
            MAR2 = IR.address;
            MDR2 = DM[MAR2];
            A += MDR2;
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
            A -= MDR2;
            break;
            // IN instruction
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
            halt = 0;
            continue;
            // JUMP instruction
        case JMP:
            printf("Jumping to memory address %d\n", IR.address);
            PC = IR.address - 2;
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
            {
                printf("False; executing the next instruction\n");
            }
            break;
            // No execution for default case
        default:
            printf("Invalid instruction\n");
        }

        // Printing the PC, A, and the DM to user after every instruction
        printf("PC = %d | A = %d | DM = [", PC, A);
        for (int j = 0; j < DM_ARRAY_SIZE; j++)
        {
            if (j < DM_ARRAY_SIZE - 1)
                printf("%d, ", DM[j]);
            else
                printf("%d]\n\n", DM[j]);
        }
        PC += 2;
    }

    printf("Program Completed\n");
    return 0;
}
