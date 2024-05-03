#include <stdio.h>
#include <stdlib.h>

int main()
{
    char string1[30], string2[30];
    char newString[50];
    
    //counter
    int i = 0;

    //counter for newString
    int j = 0;

    //bool finished
    int string1Done = 0, string2Done = 0;


    //input strings
    printf("enter string1: ");
    scanf("%s", &string1);
   

    printf("enter string2: ");
    scanf("\n%s", &string2);

    //traverse string1
    //convert all to lowercase
    //delete cr and lf
    while(string1[i])
    {
        if(string1[i] < 97)
            string1[i] += 32;

        if(string1[i] == 10)
            string1[i] = 0;

        if(string1[i] == 13)
            string1[i] = 0;

        i++;
       
    }

    //reset counter
    i = 0;

    //traverse string2
    //convert all to lowercase
    //delete cr and lf
    while(string2[i])
    {
        
        if(string2[i] < 97)
            string2[i] += 32;

        if(string2[i] == 10)
            string2[i] = 0;

        if(string2[i] == 13)
            string2[i] = 0;

        i++;
    }

    i = 0;

    //stay in loop until both strings are flagged done
    while(string1Done == 0 && string2Done == 0)
    {
        
        
        //check if either are done
        if(string1[i] == 0)
            string1Done = 1;
        
        if(string2[i] == 0)
            string2Done = 1;



        //if string1 is not done, add to end of new string
        if(string1Done == 0)
        {
            newString[j] = string1[i];
            j++;
        }

        

        //if string2 is not done, add to end of new string
        if(string2Done == 0)
        {
            newString[j] = string2[i];
            j++;
        }

        
        //increment i
        i++;
    }

    //add 0 to end of newString
    newString[j] = 0;

    printf("newstring: %s", newString);
   
    return 0;
}