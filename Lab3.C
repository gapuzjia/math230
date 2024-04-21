#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    #define conv 2.54

    int rad1, rad2, rad3, rad4, rad5, maxRad, sumRad = 0;
    double rad1cm, rad2cm, rad3cm, rad4cm, rad5cm;
    double area1, area2, area3, area4, area5;
    double circ1, circ2, circ3, circ4, circ5;

    //ask user to input all 5 radii
    //update maxRad if latest input is greater than current maxRad
    //add latest input to sumRad
    printf("Please enter an integer radius measurement (in inches): ");
    scanf("%d", &rad1);
    sumRad += rad1;
    maxRad = rad1;

    printf("\nPlease enter an integer radius measurement (in inches): ");
    scanf("%d", &rad2);
    sumRad += rad2;
    if(rad2 > maxRad)
        maxRad = rad2;

    printf("\nPlease enter an integer radius measurement (in inches): ");
    scanf("%d", &rad3);
    sumRad += rad3;
    if(rad3 > maxRad)
        maxRad = rad3;

    printf("\nPlease enter an integer radius measurement (in inches): ");
    scanf("%d", &rad4);
    sumRad += rad4;
    if(rad4 > maxRad)
        maxRad = rad4;

    printf("\nPlease enter an integer radius measurement (in inches): ");
    scanf("%d", &rad5);
    sumRad += rad5;
    if(rad5 > maxRad)
        maxRad = rad5;

    //convert radii to centimeters
    rad1cm = rad1 * conv;
    rad2cm = rad2 * conv;
    rad3cm = rad3 * conv;
    rad4cm = rad4 * conv;
    rad5cm = rad5 * conv;

    //calculate circumferences
    circ1 = 2 * M_PI * rad1cm;
    circ2 = 2 * M_PI * rad2cm;
    circ3 = 2 * M_PI * rad3cm;
    circ4 = 2 * M_PI * rad4cm;
    circ5 = 2 * M_PI * rad5cm;

    //calculate area
    area1 = M_PI * pow(rad1cm, 2);
    area2 = M_PI * pow(rad2cm, 2);
    area3 = M_PI * pow(rad3cm, 2);
    area4 = M_PI * pow(rad4cm, 2);
    area5 = M_PI * pow(rad5cm, 2);

    //print out header for table
    printf("\n\nRadius (in.)    Radius (cm.)     Area (sq. cm.)     Circumference (cm.)\n");
    printf("*****************************************************************************\n\n");

    //print out radius, radius in cm, area, and circumference for all circles
    printf("%6d%16.1f%17.1f%20.1f\n", rad1, rad1cm, area1, circ1);
    printf("%6d%16.1f%17.1f%20.1f\n", rad2, rad2cm, area2, circ2);
    printf("%6d%16.1f%17.1f%20.1f\n", rad3, rad3cm, area3, circ3);
    printf("%6d%16.1f%17.1f%20.1f\n", rad4, rad4cm, area4, circ4);
    printf("%6d%16.1f%17.1f%20.1f\n", rad5, rad5cm, area5, circ5);

    //calculate and print average of radii
    //print maximum radius
    printf("\n\n");
    printf("The average of all the radii is:%8.1f inches\n", sumRad / 5.0);
    printf("          The maximum radius is:%8d inches\n", maxRad);

    return 0;
}