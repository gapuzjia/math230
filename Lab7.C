
/*
Jia Gapuz
MATH 230
Instructor: Professor Mimi Rasky
Date: 4/19/2024
Lab #7
*/

#include <stdio.h>
#include <stdlib.h>
int main ()
{
    //declare variables
    unsigned int instr, opcode, funct, rs, rt, rd, shamt;
    int imm;
    char *name;
    int opcodeSum = 0;

    //input file and check if it exists
    FILE *inputfile;
    if((inputfile = fopen("hexInstructions.txt", "r")) == NULL)
    {
        printf("File does not exist!");
        return 0;
    }

    //create output file
    FILE *dfile;
    if((dfile = fopen("JiaGapuzLab7Output.txt", "w")) == NULL)
    {
        printf("Unable to open file to write.\n");
        return 0;
    }

    printf("%s%9s%8s%9s%9s%5s%5s%5s%8s%8s\n","Machine code", "opcode", "funct", "Inst", "format", "rs", "rt", "rd", "shamt", "Imm");
    fprintf(dfile, "%s%9s%8s%9s%9s%5s%5s%5s%8s%8s\n","Machine code", "opcode", "funct", "Inst", "format", "rs", "rt", "rd", "shamt", "Imm");

    while(fscanf(inputfile, "%x", &instr) != EOF)
    {
        //calculate opcode and add to sum
        opcode = instr >> 26;
        opcodeSum += opcode;
        
        //calculate rs and rt
        rs = (instr << 6) >> 27;
        rt = (instr << 11) >> 27;

        //if opcode is not 0, instruction is an I format
        if(opcode != 0)
        {
            //calculate immediate
            imm = ((signed int)instr << 16) >> 16;

            //find instruction name
            if(opcode == 9)
                name = "addiu";
            else if(opcode == 8)
                name = "addi";
            else if(opcode == 4)
                name = "beq";
            else if(opcode == 10)
                name = "slti";
            else
                name = "ori";

            //print all info for MIPS instruction
            printf(" 0x%08x     0x%02x        -      %5s      I   %2d   %2d   -        -    %4d\n", instr, opcode, name, rs, rt, imm);
            fprintf(dfile," 0x%08x 0x%02x - %5s I %2d %2d - - %4d\n", instr, opcode, name, rs, rt, imm);
        }

        //if opcode is 0, instruction is in R format
        else
        {
            //calculate funct
            funct = (instr << 26) >> 26;

            //find instruction name
            if(funct == 32)
                name = "add";
            else if(funct == 36)
                name = "and";
            else if(funct == 42)
                name = "slt";
            else if(funct == 34)
                name = "sub";
            else
                name = "srl";

            //calculate rd
            rd = (instr << 16) >> 27;

            //calculate shamt
            shamt = (instr << 21) >> 27;

            //print all info for MIPS instruction
            printf(" 0x%08x     0x00     0x%2x      %5s      R   %2d   %2d   %2d      %2d       -\n", instr, funct, name, rs, rt, rd, shamt);
            fprintf(dfile," 0x%08x 0x00 0x%2x %5s R %2d %2d %2d %2d -\n", instr, funct, name, rs, rt, rd, shamt);
            }
    }

    //print out sum of opcodes
    printf("\nOpcode sum: %5d", opcodeSum);
    fprintf(dfile,"\nOpcode sum: %5d", opcodeSum);

    //close files
    fclose(inputfile);
    fclose(dfile);
    return 0;
}
