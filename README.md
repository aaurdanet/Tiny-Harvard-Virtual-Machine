Tiny Harvard Virtual Machine 

Overview:
This program simulates the execution of instructions in the Tiny Harvard Virtual Machine architecture. It reads instructions from a file named "elf.txt", executes them, and prints the state of the program after each instruction.

Compilation:
To compile the program, use any C compiler such as gcc:
gcc -o tinyMachine tinyMachine.c

Execution:
To execute the program, run the compiled executable:
./tinyMachine

Instructions File:
The program expects an input file named "elf.txt" containing instructions for the virtual machine. Ensure the input file is in the correct format, with each instruction consisting of two integers representing the opcode and address, respectively.
