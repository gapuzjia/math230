/*
Jia Gapuz
Math 230
Instructor: Mimi Rasky
Date: 4/11/2024
Lab #6
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//function prototypes
void printArray(int ** array, int rows, int columns);
int* findMinAddr(int ** array, int rows, int columns);
int* findMaxAddr(int ** array, int rows, int columns);
double getClassAvg(int ** array, int rows, int columns);
int getRange(int ** array, int rows, int columns);
double getRowAverage(int ** array, int columns, int fixedRow);
double getColumnAverage(int ** array, int rows, int fixedCol);
int getHighestInRow(int ** array, int columns, int fixedRow);
int getLowestInRow(int ** array, int columns, int fixedRow);
double getStandardDeviation(int** array, int rows, int fixedCol);
void getGrades(int** array, int rows, int columns);

int main()
{
    int rows, cols;
    int **array = NULL;
    int *minPtr = NULL, *maxPtr = NULL;

    //import file
    FILE *inputfile;
    inputfile = fopen("gradeBook.txt", "r");

    //scan array size from first values of file
    fscanf(inputfile, "%d", &rows);
    fscanf(inputfile, "%d", &cols);

    //declare 2-d array with DMA
    array = (int**)malloc(rows * sizeof(int*));

    for(int i = 0; i < rows; i++)
        array[i] = (int*)malloc(cols * sizeof(int));

    //check if array is null
    if(array == NULL)
    {
        printf("Memory not allocated.\n");
        exit(0);
    }

    //populate array with values from file
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
            fscanf(inputfile, "%d", &array[i][j]);
    }

    //close file
    close(inputfile);

    //invoke printArray function
    printArray(array, rows, cols);

    //invoke findMinAddr function and print result
    minPtr = findMinAddr(array, rows, cols);
    printf("The minimum exam score is: %5d\n", *minPtr);

    //invoke findMaxAddr function and print result
    maxPtr = findMaxAddr(array, rows, cols);
    printf("The maximum exam score is: %5d\n", *maxPtr);

    //invoke getClassAvg function and print result
    printf("The class average of all grades is: %.1f\n", getClassAvg(array, rows, cols));

    //invoke getRange function and print result
    printf("The range of all grades is : %3d\n\n", getRange(array, rows, cols));

    //invoke getRowAverage function for each student
    for(int i = 0; i < rows; i++)
        printf("The average for student #%d is: %6.1f\n", i + 1, getRowAverage(array, cols, i));

    printf("\n");

    //invoke getColumnAverage for each exam
    for(int i = 0; i < cols; i++)
        printf("The average for exam #%d is: %6.1f\n", i + 1, getColumnAverage(array, rows, i));

    printf("\n");

    //invoke getHighestInRow function for each student
    for(int i = 0; i < rows; i++)
        printf("The highest exam grade for student #%d is: %d\n", i + 1, getHighestInRow(array, cols, i));

    printf("\n");

    //invoke getLowestInRow function for each student
    for(int i = 0; i < rows; i++)
        printf("The lowest exam grade for student #%d is: %d\n", i + 1, getLowestInRow(array, cols, i));

    printf("\n");

    //calculate and print standard deviation for each exam
    for(int i = 0; i < cols; i++)
        printf("The standard deviation for exam #%d: %6.1f\n", i + 1, getStandardDeviation(array, rows, i));

    printf("\n");

    //invoke getGrades function
    getGrades(array, rows, cols);

    //free memory
    free(array);

    return 0;
}


void printArray(int ** array, int rows, int columns)
{
    //print padding for alignment
    printf("%10s", "");

    //print column headers
    for(int i = 0; i < columns; i++)
        printf("%9s%d", "Exam #", i + 1);

    printf("\n");

    //traverse 2-d array and print contents
    for(int i = 0; i < rows; i++)
    {
        printf("Student #%d", i + 1);

        for(int j = 0; j < columns; j++)
            printf("%9d ", array[i][j]);

        printf("\n");
    }

}

int* findMinAddr(int ** array, int rows, int columns)
{
    //declare pointer
    int* minPtr = NULL;

    //set min to first element in the array
    minPtr = &array[0][0];

    //traverse array and look for min
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            if(*minPtr > array[i][j])
                minPtr = &array[i][j];
        }
    }

    //return pointer to min value
    return minPtr;
}

int * findMaxAddr(int **array, int rows, int columns)
{
    //declare pointer
    int* maxPtr = NULL;

    //set max to first element in the array
    maxPtr = &array[0][0];

    //traverse array and look for max
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            if(*maxPtr < array[i][j])
                maxPtr = &array[i][j];
        }
    }

    //return pointer to max
    return maxPtr;

}

double getClassAvg(int ** array, int rows, int columns)
{
    //declare variables
    int ctr = 0, sum = 0;

    //traverse entire array to calculate sum, update counter
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            sum += array[i][j];
            ctr++;
        }
    }

    //return the sum divided by the number of elements in the 2-d array
    return sum / (double)ctr;
}

int getRange(int ** array, int rows, int columns)
{
    //invoke findMinAddr and findMaxAddr
    int *minPtr = findMinAddr(array, rows, columns);
    int *maxPtr = findMaxAddr(array, rows, columns);

    //return the difference between the max and min value in the 2-d array
    return *maxPtr - *minPtr;

}

double getRowAverage(int ** array, int columns, int fixedRow)
{
    //declare variables
    int sum = 0, ctr = 0;

    //traverse each element in row, add to accumulator and increment counter
    for(int i = 0; i < columns; i++)
    {
        sum += array[fixedRow][i];
        ctr++;
    }

    //return average of all values
    return sum / (double)ctr;
}

double getColumnAverage(int ** array, int rows, int fixedCol)
{
    //declare variables
    int sum = 0, ctr = 0;

    //traverse through all elements in the column, add to accumulator and increment counter
    for(int i = 0; i < rows; i++)
    {
        sum += array[i][fixedCol];
        ctr++;
    }

    //return average
    return sum / (double)ctr;
}

int getHighestInRow(int ** array, int columns, int fixedRow)
{
    //initialize max to first value in row
    int max = array[fixedRow][0];

    //traverse the row and compare to max, update max if needed
    for(int i = 1; i < columns; i++)
    {
        if(max < array[fixedRow][i])
            max = array[fixedRow][i];
    }

    //return max value
    return max;
}

int getLowestInRow(int ** array, int rows, int fixedRow)
{
    //initialize min to first value in row
    int min = array[fixedRow][0];

    //traverse the row and compare to min, update min if needed
    for(int i = 1; i < rows; i++)
    {
        if(min > array[fixedRow][i])
            min = array[fixedRow][i];
    }

    //return min
    return min;
}

double getStandardDeviation(int ** array, int rows, int fixedCol)
{
    //declare and initialize variables
    double avg = getColumnAverage(array, rows, fixedCol);
    double sum = 0;
    int ctr = 0;

    //traverse through all elements of the column, update counter
    //accumulate the squared value of the difference of the average and the current element
    for(int i = 0; i < rows; i++)
    {
        sum += pow(avg - array[i][fixedCol], 2);
        ctr++;
    }

    //return the square root of the sum
    return sqrt(sum / ctr);
}

void getGrades(int ** array, int rows, int columns)
{
    //initialize variables
    int sum = 0;
    double avg;

    //traverse all rows
    for(int i = 0; i < rows; i++)
    {
        //calculate the sum of all elements in current row
        for(int j = 0; j < columns; j++)
            sum += array[i][j];

        //subtract the lowest score from the sum
        sum -= getLowestInRow(array, columns, i);

        //calculate average after dropping lowest score and print result
        avg = sum / (double)(columns - 1);

        printf("Student #%d had an average of %.1f (after dropping lowest score).\n", i + 1, avg);

        //display equivalent letter grade
        if(avg >= 90)
            printf("This student received a grade of A in the class.\n\n");
        else if(avg >= 80)
            printf("This student received a grade of B in the class.\n\n");
        else if(avg >= 70)
            printf("This student received a grade of C in the class.\n\n");
        else if(avg >= 60)
            printf("This student received a grade of D in the class.\n\n");
        else
            printf("This student received a grade of F in the class.\n\n");

        //reset sum
        sum = 0;
    }

}

