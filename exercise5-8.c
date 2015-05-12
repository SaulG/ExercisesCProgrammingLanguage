#include <stdio.h>

/**
   The valid values are the following:
   Year between 1990 and 2015
   Day between 1 and 31
   Month between 1 and 12
 **/

static char daytab[2][13] = {
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
  int i, leap;
  
  if ((day < 1 && day > 31) &&
      (month < 1 && month > 12))
    return -1; //not a valida month or day

  leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
  for (i = 1; i < month; i++)
    day += daytab[leap][i];
  return day;
}


/* month_day: set month, day from day of year */
int month_day(int year, int yearday, int *pmonth, int *pday)
{
  int i, leap;

  if ((year < 1990 && year > 2015) &&
      (yearday < 1 && yearday > 365))
    return -1; // not a valid day or year
      
  leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
  for (i = 1; yearday > daytab[leap][i]; i++)
    yearday -= daytab[leap][i];
  *pmonth = i;
  *pday = yearday;
  return 1; // anything it's okay
}


int main()
{
  int *pmonth;
  int *pday;
  int month_day_value = 0;
  int day_of_year_value = 0;

  for (int year = 1890; year <= 2015; year++) {
    for (int month = 1; month <= 12; month++) {
      for (int day = 1; day <= 31; day++) {
	printf("day: %d month: %d year: %d\n", day, month, year);
	month_day_value = month_day(year, (day*month % 365), &pmonth, &pday);
	if (month_day_value) 
	  printf("month_day: month: %d day: %d\n", pmonth, pday);
	else
	  printf("Something got wrong with month day function\n");

	day_of_year_value = day_of_year(year, month, day);
	if (day_of_year_value != -1)
	  printf("day_of_year: %d\n", day_of_year_value);
	else 
	  printf("Something got wrong with day of year function\n");
	  
      }
    }
  }
  return 1;
}
