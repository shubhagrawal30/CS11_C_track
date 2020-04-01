/*
 * CS 11 C track, Winter 2019
 * Shubh Agrawal, Class of 2022
 * Assignment 1
 * 
 * hello2.c
 */


#include <stdio.h>

/* Scans a single-word name from the terminal,
 * and prints a "hello, <name>!" message.
 */
int main(void)
{
        char name[100];
        printf("Enter your name: ");
        scanf("%99s", name);
        printf("hello, %s!\n", name);
        return 0;
}
