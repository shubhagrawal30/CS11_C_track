/*
 * CS 11 C track, Winter 2019
 * Shubh Agrawal, Class of 2022
 * Assignment 1
 * 
 * hello3.c
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/* Prints a greeting to the terminal <n> times,
 * where <n> is a random integer between 1 and 10 (inclusive).
 * The content of the message is determined by parity of n.
 */


/* Returns a random integer between <min> and <max>.
 *
 * Passed Arguments: min, max: values of datatype int
 *  which represnt the lower and upper bounds of the 
 *  random integer.
 */
int get_n(int min, int max)
{
        srand(time(0));
        return (rand() % (max - min)) + min;
}


int main(void)
{
        char name[100], *msg;
        /* <msg> is defined as a pointer for later manipulation. */
 
        int i, n = get_n(1, 10);
        
        printf("Enter your name: ");
        scanf("%99s", name);
        if (n % 2 == 0)
          {
            msg = "hello";
          }
        else
          {
            msg = "hi there";
          }
        for (i = 0; i < n; i++)
          {
            printf("%d: %s, %s!\n", n, msg, name);
          }
        return 0;
}

