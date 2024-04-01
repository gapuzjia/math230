/*
Jia Gapuz
Math 230
Instructor: Mimi Rasky
Date: 3/7/2024
Lab #4
*/
#include <stdio.h>
#include <stdlib.h>

//function prototypes
char *serchit(char *str, char ref_char);

int main()
{
    //declare variables
    char myString[30];
    char *newString;
    char myChar;
    int length = 0, i = 0;

    //prompt user for inputs
    printf("Please enter a string: ");
    scanf("%[^\n]", &myString);
    printf("Please enter a character to search for: ");
    scanf("\n%c", &myChar);

    //print string to console
    printf("The string is: %s\n", myString);

    //find string length and print to console
    while(myString[length])
        length++;

    printf("The length of the string is: %d\n", length);

    //invoke serchit function and store in newString
    newString = serchit(myString, myChar);

    //print new string if myChar was found in the string
    if(*newString)
    {
        printf("%c was found in the string\n", myChar);
        printf("The string, beginning at %c is: %s\n\n", myChar, newString);
    }

    else
        printf("%c was not found in the string\n\n", myChar);


    //print all info for newString
    printf("Address           Contents     Decimal      ASCII\n");
    while(*(newString + i))
    {
        printf("%010X %8s 0x%2X %11d %9c\n", &newString + i,"",*(newString + i),*(newString + i),*(newString + i));
        i++;
    }

    //print null character info
    printf("%010X %s 0x%02X %11d %9c\n", &newString + i,"",*(newString + i),*(newString + i),*(newString + i));

    return 0;
}


char *serchit(char *str, char ref_char)
{
    //declare and initialize incrementor
    int i = 0;

    //traverse string
    while(str[i])
    {
        //if current char matches ref_char, return its address
        if(str[i] == ref_char)
            return &str[i];

        i++;
    }

    //if ref_char was never found in the string, return null character
    return &str[i];
}
