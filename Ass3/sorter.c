/*
 * CS 11 C track, Winter 2019
 * Shubh Agrawal, Class of 2022
 * Assignment 3
 * 
 * sorter.c
 */


#define CAPACITY 32

#include <stdlib.h>
#include <stdio.h>
#include <string.h> /* For comparing strings */
#include <assert.h>

/* Prints the usage message.
 * 
 * Passed Arguments: 
 * name: string representing the program name.
 */
void usage(char *name);

/* Sorts integers in passed array using bubble
 * sort algorithm  in ascending order. 
 *
 * Passed Arguments: 
 * arr: array of integers to be worked upon.
 * len: number of elements in the array.
 */
void bubble_sort(int arr[], int len);

/* Sorts integers in passed array, using minimum
 * element sort algorithm, in ascending order. 
 *
 * Passed Arguments: 
 * arr: array of integers to be worked upon.
 * len: number of elements in the array.
 */
void min_elem_sort(int arr[], int len);

/* Prints the elements of the passed array,
 * each in a new line.
 * 
 * Passed Arguments: 
 * arr: array of integers to be worked upon.
 * len: number of elements in the array.
 */
void print_arr(int arr[], int len);


void usage(char *name)
{
  fprintf(stderr, \
    "usage: %s [-b] [-q] number1 [number2 ... ] (maximum 32 numbers)\n", name);
  exit(EXIT_FAILURE);
}


/* Starting point of program. */
int main(int argc, char *argv[])
{
  int bubble = 0, output = 1;
  int i, pos = 0;
  int nums[CAPACITY];

  /* Checks for correct number of arguments. */
  if (argc == 0)
    {
      usage(argv[0]);
    }
  
  for (i = 1; i < argc; i++)
    {

      /* Checks for optional arguments. */
      if (strcmp(argv[i], "-b") == 0)
        {
          bubble = 1;
          continue;
        }
      if (strcmp(argv[i], "-q") == 0)
        {
          output = 0;
          continue;
        }

      /* Checks for correct number of arguments. */
      if (pos == 32)
        {
          usage(argv[0]);
        }

      nums[pos++] = atoi(argv[i]);
      
    }

  if (pos == 0)
    {
      usage(argv[0]);
    }

  if (bubble)
    {
      bubble_sort(nums, pos);
    }
  else
    {
      min_elem_sort(nums, pos);
    }

  if (output)
    {
      print_arr(nums, pos);
    }
  
  return EXIT_SUCCESS;
}

void bubble_sort(int arr[], int len)
{
  int i, j, temp;
  for (i = 0; i < (len - 1); i++)
    {
      /* Repeatedly steps through the list, compares
       * adjacent pairs and swaps them if 
       * they are in the wrong order.
       */
      for (j = 0; j < (len - 1 - i); j++)
        {
          if (arr[j] > arr[j + 1])
            {
              temp = arr[j];
              arr[j] = arr[j + 1];
              arr[j + 1] = temp;
            }
        }
    }

  /* Asserts that array is in ascending order. */
  for (i = 1; i < len; i++)
    {
        assert(arr[i] >= arr[i - 1]);
    }
}

void min_elem_sort(int arr[], int len)
{
  int i, start, smallest, temp;

  for (start = 0; start < len; start++)
    {
      /* At each iteration, removes one element, 
       * finds its location in sorted sublist, 
       * and inserts it there. Repeats for all elements.
       */
      smallest = start;
      for (i = start; i < len; i++)
        {
          if (arr[i] < arr[smallest])
            {
              smallest = i;
            }
        }
      temp = arr[start];
      arr[start] = arr[smallest];
      arr[smallest] = temp;
    }

  /* Asserts that array is in ascending order. */
  for (i = 1; i < len; i++)
    {
        assert(arr[i] >= arr[i - 1]);
    }
}

void print_arr(int arr[], int len)
{
  int i;

  for(i = 0; i < len; i++)
    {
      printf("%d\n", arr[i]);
    }
}
