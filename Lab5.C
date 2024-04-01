#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 15

int INPUTSIZE;

void decToBinary(int ra[], int decNum);

int main()
{
    int *ptr;
    int* binaryArray = (int*)malloc(32 * sizeof(int));
    char *names[15] = {"Alfred", "Ben", "Catherine", "Dana",
                    "Ether", "Frank", "Gab", "Harry", "Ian",
                    "Johnny", "Kerry", "Leo", "Mike", "Nathan", "Olivia"};

    //import file
    FILE *inputfile;
    inputfile = fopen("Lab5integers.txt", "r");

    //populate binaryArray with 0s
    for(int i = 0; i < 32; i++)
        binaryArray[i] = 0;

    //scan array size from first value of file
    fscanf(inputfile, "%d", &INPUTSIZE);

    //declare array with DMA
    ptr = (int*)malloc(INPUTSIZE * sizeof(int));

    //check if array is null
    if(ptr == NULL)
    {
        printf("Memory not allocated.\n");
        exit(0);
    }

    //populate array with value from files
    for(int i = 0; i < INPUTSIZE; i++)
        fscanf(inputfile, "%d", &ptr[i]);


    //print out info for entire array
    for(int i = 0; i < INPUTSIZE; i++)
    {
        //convert decimal to binary and store in binaryArray
        decToBinary(binaryArray, ptr[i]);

        printf("DEC: %7d| HEX: 0x%010X| BIN:", ptr[i], ptr[i]);

        //print binaryArray backwards and reset array contents to 0
        for(int j = 31; j >= 0; j--)
        {
            printf("%d", binaryArray[j]);
            binaryArray[j] = 0;
        }

        printf("\n");
    }

    //invoke printNames
    printNames(names, ARRAY_SIZE);

    //invoke dice game
    dice_game(names, ARRAY_SIZE);

    //free memory
    free(binaryArray);
    free(ptr);

    return 0;
}


void decToBinary(int ra[], int decNum)
{
    int i = 0;
    int isNegative = 0;

    //set flag to true if decimal value is negative
    if(decNum < 0)
        isNegative = 1;

    //find absolute value of decNum
    decNum = abs(decNum);

    //convert to binary
    while(decNum != 0)
    {
        ra[i] = decNum % 2;
        decNum /= 2;
        i++;
    }

    //if decimal is a negative value, flip all the bits
    if(isNegative)
    {
        for(int j = 0; j < 32; j++)
        {
            if(ra[j] == 1)
                ra[j] = 0;

            else
                ra[j] = 1;
        }
    }
}

void printNames(char **ra, int size)
{
    printf("\nName List\n");
    printf("------------\n");

    for(int i = 0; i < size; i++)
    {
        printf("%15s", ra[i]);

        if((i + 1) % 4 == 0)
            printf("\n");
    }

    printf("\n\n");
}

void dice_game(char **ra, int size)
{
    srand(time(NULL));

    int rolls [size];
    int dice1, dice2, min;
    int winCtr = 1;

    printf("Dice Game Results:\n");
    printf("------------\n\n");

    //roll player 1 to initialize min
    dice1 = rand() % 10 + 1;
    dice2 = rand() % 10 + 1;
    rolls[0] = abs(dice1 - dice2);
    min = rolls[0];

    //roll for rest of players and compare to min
    //update min if necessary
    for(int i = 1; i < size; i++)
    {
        //roll die
        dice1 = rand() % 10 + 1;
        dice2 = rand() % 10 + 1;

        //find difference
        rolls[i] = abs(dice1 - dice2);

        //print out die information
        printf("%-10s die1: %3d, die2: %3d, difference is: %3d\n",ra[i], dice1, dice2, rolls[i]);

        //if there is a new min, set winCtr to 1
        if(rolls[i] < min)
        {
            min = rolls[i];
            winCtr = 1;
        }

        //if current roll is same as min, increment winCtr
        else if(rolls[i] == min)
            winCtr++;
    }


    //print results dependent on number
    if(winCtr > 1)
        printf("\nTie game!...and the winners are...\n");

    else
        printf("\nand the winner is...");


    //loop prints out names of winner/s
    for(int i = 0; i < size; i++)
    {
        if(rolls[i] == min)
            printf("%s\n",ra[i]);
    }

}
