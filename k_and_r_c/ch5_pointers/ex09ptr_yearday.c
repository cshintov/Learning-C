// convert from  yearday to month and day and vice versa

#include <stdio.h>

static char daytab[2][13] = { 
        {0, 31, 28, 31, 30, 31, 30 ,31, 31, 30 ,31, 30, 31},
        {0, 31, 29, 31, 30, 31, 30 ,31, 31, 30 ,31, 30, 31}
    };

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, char *pmonth, int *pday);
int main() {
    printf("%d year %d month %d day ==> day of year would be %d\n",
            2001, 3, 1, day_of_year(2001, 3, 1));  
    char *pmonth, month;
    int *pday, day;
    pmonth = &month;
    pday = &day;
    month_day(2000, 60, pmonth, pday);
    printf("%d year %d month %d day <== %d th day of year %d\n",
            2000, *pmonth, *pday, 60, 2000); 
    month_day(2001, 60, pmonth, pday);
    printf("%d year %d month %d day <== %d th day of year %d\n",
            2001, *pmonth, *pday, 60, 2001); 
}

int day_of_year(int year, int month, int day) {
    int i, leap;
    leap = (!(year % 4) && year % 100 || !(year % 400)) ? 1: 0;
    for(i=1; i < month; i++)
        day += *(*(daytab + leap)+i);
    return day;
}


void month_day(int year, int yearday, char *pmonth, int *pday) {
    int i, leap;

    leap = (!(year % 4) && year % 100 || !(year % 400)) ? 1: 0;
    for(i=0; yearday > daytab[leap][i]; i++)
        yearday -= *(*(daytab + leap)+i);
    *pmonth = i;
    *pday = yearday;
}
