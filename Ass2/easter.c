/*
 * CS 11 C track, Winter 2019
 * Shubh Agrawal, Class of 2022
 * Assignment 2
 * 
 * easter.c
 */

/* ATTEMPTED EXTRA CREDIT QUESTION, PLEASE CHECK!
 */


/* Computes, and prints to the terminal, the day of the year
 * on which Easter falls using the Knuth's algorithm,
 * after accepting the integral value for the year
 * between MIN_YEAR (1582 C.E.) and MAX_YEAR (39999 C.E.)
 * from the terminal.
 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define MIN_YEAR 1582
#define MAX_YEAR 39999

/* Calculates the date of Easter Sunday for a given year.
 * 
 * Passed Arguments: 
 * year: int value representing the year under analysis.
 *
 * Return Value: int value, the absolute value of which
 *   represents the date of Easter, and the sign represents
 *   the month (positive: April, negative: March)
 *   Value returned is 0 if year is out of range.
 */
int calculate_Easter_date(int year);

/* Checks if passed argument for date represents a Sunday
 * using Zeller's Congruence.
 */
int isSunday(int date, int year);


/* Starting point of program.
 * Accepts a series of integral values from 
 * the <stdin> infile, until end of file, and
 * prints year - date pairs to <stdout> outfile.
 */
int main(void)
{
  int inp_result, year, date;
  char *month; 
  /* Declared as pointer to allow later manipulation. */

  while (1)
    {
      
      inp_result = scanf("%d", &year);

      /* Return value would be EOF when file has ended. */
      if (inp_result == EOF)
        break;
      
      date = calculate_Easter_date(year);

      /* Year out of range error managed. */
      if (date == 0)
        {
          fprintf(stderr, "Year %d not in range.\n", year);
          continue;
        }

      month = (date > 0) ? "April" : "March";
      printf("%d - %s %d\n", year, month, abs(date));
      /* abs() function returns the absolute value of 'date' */
    }
  return 0;
}


int calculate_Easter_date(int year)
{
  int golden_num, century, moon_corr, leap_skip, date, epact, sunday;

  /* If year is out of range, absurd value 0 is returned. */
  if (year < MIN_YEAR || year > MAX_YEAR)
    {
      return 0;
    }
  
  /*
   * GIVEN:   Y: the year for which the date of Easter is to be determined.
   * FIND:    The date (month and day) of Easter
   *
   * STEP E1: Set G to (Y mod 19) + 1.
   *          [G is the "golden year" in the 19 year Metonic cycle.]
   * The number 19 comes from the Metonic Cycle: the moon cycle is 
   * consistent with the calender at intervals of 19 years.
   * 
   * STEP E2: Set C to (Y / 100) + 1. [C is the century]
   *  Note that all divisions are integral; so, C would be an integer
   *  as required.
   * 
   * STEP E3: Set X to (3C / 4) - 12. [X is the skipped leap years.]
   *          Set Z to ((8C + 5) / 25) - 5.
   *          [Z is a correction factor for the moon's orbit.]
   * The gregorian calender (concept of leap years) and the
   * fact that the moon Metonic cycle is slightly offset from
   * the period of 19 years causes the necessity to take these
   * two values into account.
   * 
   * STEP E4: Set D to (5Y / 4) - X - 10.
   *          [March ((-D) mod 7 + 7) is a Sunday.]
   * This gives us a reference value of a Sunday, which is useful
   * as Easter must fall on a Sunday.
   * 
   * STEP E5: Set E to (11G + 20 + Z - X) mod 30.
   *          If E is 25 and G is greater than 11 or if E is 24,
   *          increment E.
   *          [E is the "epact" which specifies when a full moon occurs.]
   * Value of epact gives us a referencable measure of phase of moon.
   * 
   * STEP E6: Set N to 44 - E.  [March N is a "calendar full moon".]
   *          If N is less than 21 then add 30 to N.
   * The value of N represents the date of a full moon close to Easter.
   * 
   * STEP E7: Set N to N + 7 - ((D + N) mod 7).
   *          [N is a Sunday after full moon.]
   * The value represents the days between March 1 and Easter Sunday.
   * 
   * STEP E8: If N > 31 the date is APRIL (N - 31),
   *          otherwise the date is MARCH N.
   */

  golden_num = (year % 19) + 1; /* G in algorithm */
  century = year / 100 + 1; /* C in algorithm */
  leap_skip = (3 * century / 4) - 12; /* X in algorithm */
  moon_corr = (8 * century + 5) / 25 - 5; /* Z in algorithm */
  sunday = (5 * year / 4) - leap_skip - 10; /* D in algorithm */
  
  epact = (11 * golden_num + 20 + moon_corr - leap_skip) % 30;
   /* E in algorithm */
  if ((epact == 25 && golden_num > 11) || epact == 24)
    {
      epact++;
    }

  date = 44 - epact;  /* N in algorithm */
  if (date < 21)
    {
      date += 30;
    }
  date += 7 - ((sunday + date) % 7);

  /* Converts date from algorithm to the form used in this program */
  date = (date > 31) ? (date - 31) : (-date);


  assert(isSunday(date, year));

  return date;
}


int isSunday(int val, int year) {
    int day, date, month, century, yearOfCen;

    century = year / 100;
    yearOfCen = year % 100;
    date = abs(val);
    month = (val > 0)? 4 : 3;

    day = date + 13 * (month + 1) / 5 + yearOfCen
        + yearOfCen / 4 + century / 4 + 5 * century;
    
    day = day % 7;

    return day;
    if (day == 1) {
        return 1;
    }
    else {
        return 0;
    }
}
