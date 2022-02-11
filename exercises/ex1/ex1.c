// Copyright 2022 <Melody Zhang> [legal/copyright]
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// update pi by adding together terms 1 through value (inclusively),
// in the Nilakantha series. 
// The valueth term is: (-1)^(n+1)*(4/2n*(2n+1)*(2n+2)))
// param: double pi is the term 0 in Nilakantha series, which is 3.
//        int value is the value we need to add from term 1 through 
//        term value. 
// return: a pi that is updated in Nilakantha series.
double updatePi(double, int);


int main(int argc, char* argv[]) {
    int value; // the value we get from user input
    double pi =3.0; // the starting pi is term 0 in Nilakantha series.
    double test; // an intermediate double to test whether
                 // value has decimal that is not zero, e.g. 5.123
    if (argc>2) { // if user input more than 2 arguments, then do nothing
                  // and leave a message.
        printf("You may have entered more than one number.\n");
        printf("Please enter just one number.\n");
    } else if (argc < 2) { // if user did not enter any number, then
                           // there are less than 2 arguments, then
                           // leave a message.
        printf("You may have not entered any number.\n");
        printf(" Please enter one number.\n");
    } else { // means that there are 2 arguments.
        if (1 == sscanf(argv[1], "%lf", &test)) { // if converting string to 
                                                  // number successfully
            value = (int)test;
            if (value == test) { // if that number is what we want (no 
                                 // non-zero decimal, e.g. 5.0 is okay
                                 // but 5.1 is not okay.)
                pi = updatePi(pi, value);
                printf("Our estimate of Pi is %0.20f\n", pi);
            } else { // if the number has non-zero decimal, e.g. 5.1
                printf("You may have entered ");
                printf("a number with decimals.\n");
                printf("PLease enter a natural number.\n");
            }
        } else { // if converting string to number is not successful
            printf("What you have entered may ");
	        printf("not be a valid number.\n");
            printf("Please enter a valid natural number.\n");
        }
    }
}
double updatePi(double pi, int value) {
    double inter;
    for (int i = 1 ; i <= value; i++) {
        inter = (4.0/(2.0*(double)i * (2.0*(double)i+1.0)
                *(2.0*(double) i+2.0)));
        if (i%2 != 1) {
            pi = pi- inter;
        } else {
            pi = pi+ inter;
        }
    }
    return pi;
}
