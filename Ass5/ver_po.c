/*
 * CS 11 C track, Winter 2019
 * Shubh Agrawal, Class of 2022
 * Assignment 5
 * 
 * ver_po.c
 * Version which updates using pointer operations.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "memcheck.h"

/* Initiates the passed array 'arr' of length 'len' to random 
 * binary values (0 and 1)
 */
void initiate(int arr[], int len);

/* Simulates and displays the updated versions of the array 'curr'
  * of length 'cell_no' for 'gen_no' generations.
  */
void simulate(int curr[], int next[], int cell_no, int gen_no);

/* Updates the array 'curr' and stores it in 'next'.
  */
void update(int curr[], int next[], int len);

/* Displays the array 'arr' of length 'len' in given format.
  */
void display(int arr[], int len);


/* Starting point of the program; allocates memory dynamically.
  */
int main(int argc, char *argv[]) {

    int cellNo = atoi(argv[1]), genNo = atoi(argv[2]);
    
    int *curr = (int *) calloc(cellNo, sizeof(int));
    int *next = (int *) calloc(cellNo, sizeof(int));

    /* Check that the calloc call succeeded. */
    if (curr == NULL || next == NULL) {

    fprintf(stderr, "Error! Memory allocation failed!\n");
    exit(1);  /* abort the program */
    }

    initiate(curr, cellNo);
    display(curr, cellNo);
    simulate(curr, next, cellNo, genNo);

    free(curr);
    free(next);

    print_memory_leaks();

    return EXIT_SUCCESS;
}

void initiate(int arr[], int len) {

    int i;
    srand(time(0));
    for (i = 1; i < len - 1; i++) {
        arr[i] = rand() % 2;
    }
    arr[0] = 0;
    arr[i] = 0;
}

void simulate(int curr[], int next[], int cell_no, int gen_no) {
    int gen;
    int *temp;
    for (gen = 1; gen <= gen_no; gen++) {

        update(curr, next, cell_no);
        temp = curr;
        curr = next;
        next = temp;
        display(curr, cell_no);
    }
}

void update(int curr[], int next[], int len) {

    int i;
    int* pre = curr, *elem = pre, *post = pre, *val = next;
    val++;
    elem++;
    post+=2; 

    for (i = 1; i < len - 1; i++, pre++, post++, val++, elem++) {
        *val = 0;
        if (*elem == 0) {
            if ((*pre + *post) == 1) {
                *val = 1;
            }
        }    
    }

}


void display(int arr[], int len) {

    int i;
    for (i = 0; i < len; i++) {
        if (arr[i] == 1) {
            printf("*");
        }
        else {
            printf(".");
        } 
    }
    printf("\n");
    
}
