/**
//  pi.c
//  Pi
//  A program to find pi to a specified accuracy using
//   the Gregory-Leibniz converging series.
//  Created by Jeremy Schmidt on 4/5/13.
//  Copyright (c) 2013 Jeremy Schmidt. Some rights reserved.
*/


#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define MAX_ITERATIONS 2428702234
/* From the formula */
#define NUMERATOR 4.0

long unsigned int iterations = 0;

long unsigned int denominator = 3;

long unsigned int noSuccess = 0;

double pi = 4;

int placeToCompare = 0;


// Primary function to carry out the converging formula

double findPi (long unsigned iterations, double pi,
       long unsigned int denominator)
{
    double newPi = 0;

    // The series alternates adding and subtracting
    if (!(iterations % 2) || iterations == 0) {
        newPi = pi - (NUMERATOR / (double)denominator);
    }
    else {
        newPi = pi + (NUMERATOR / (double)denominator);
    }
    return newPi;
}


/*
 * Reducing the numbers is nessesary for determining if I have true pi.  Because the convergance
 *  fluctuates back and forth around pi with the fluctuation becoming smaller, if two consective
 *  results are the same to a given decemal place, then up to that point is true pi.
 *  Reducing it allows me to limit the number to just the part I want to compare.
*/
double reduceTo (double number, int place)
{
    while (place--) {
        number *= 10;
    }
    return floor(number);
}


// Determines if what I have is pi and returns the determined digits of pi.

double getSolid(double old, double new, int place)
{
    if (old == new) {
        if (place != 0) {
            new /= pow(10,place);
        }
        return new;
    }
    return 0;
}


int main ()
{
    // So I can time the program
    clock_t successTime;
    successTime = clock();
    while (iterations < MAX_ITERATIONS) {
        double newPi = findPi (iterations, pi, denominator);
        double reducedPi = reduceTo (pi, placeToCompare);
        double reducedNewPi = reduceTo (newPi, placeToCompare);
        double solid = getSolid(reducedPi, reducedNewPi, placeToCompare);
        if (solid) {
            successTime = clock() - successTime;
            printf("%.14f found in %li iterations    (%f seconds.)\n", solid, iterations,
                    ((float)successTime) / CLOCKS_PER_SEC);
            placeToCompare++;
            noSuccess = 0;
        }
        else {
            noSuccess++;
            // Every one trillion failed iterations, print a status report.
            if (! (noSuccess % 1000000000)) {
                printf("%li iterations without success.    currently %.14f\n", noSuccess, pi);
            }
        }
        pi = newPi;
        iterations += 1;
        denominator += (int) 2;
    }
}
