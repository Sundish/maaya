#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "calc.h"

const int BAKTUN = 144000;
const int KATUN = 7200;
const int TUN = 360;
const int UINAL = 20;
const int KIN = 1;

const int donc = 4;
/* const int monc = 3; */

const int ndonc = 20;
/* const int nmonc = 13; */

const int days_toadd = 263; /* (total_day_numbers%365 + 263)%365*/

static const char *day_names[] = { "Ahaw", "Imix", "Ik'", "Ak'bal", "K'an", "Chikchán", "Kimi", "Manik"
              , "Lamat", "Muluc", "Ok", "Chuen", "Eb", "Ben", "Ix", "Men", "Kib"
              , "Kaban", "Etz'nab", "Kauak" };

static const char *month_names[] = { "Pop", "Uo", "Zip", "Zotz'", "Tzek", "Xul", "YaxKin", "Mol"
     , "Ch'en", "Yax", "Zak", "Keh", "Mak", "Kankin", "Muan", "Pax"
     , "Kayab", "K'umk'u", "Uayeb" };

double
get_working_time (void) { /* returns the current time in days */
     struct tm new_epoch;
     new_epoch.tm_year = 2012 - 1900;
     new_epoch.tm_mon = 11;
     new_epoch.tm_mday = 22;
     new_epoch.tm_hour = 0;
     new_epoch.tm_min = 0;
     new_epoch.tm_sec = 0;
     new_epoch.tm_isdst = 0;
     return ceil(0.00001157407*difftime(time(NULL),
                                      mktime(&new_epoch)));
}

struct mayaT
from_working_time_to_maya (double wt) { /* Converts the time in days to time in a maya struct */
     struct mayaT mt;
     double a, b, c, d;
     a = fmod(wt,144000);
     b = fmod(a, 7200);
     c = fmod(b, 360);
     d = fmod(c, 20);
     mt.mayaT_baktun = (wt/BAKTUN);
     mt.mayaT_katun = (a/KATUN);
     mt.mayaT_tun = (b/TUN);
     mt.mayaT_uinal = (c/UINAL);
     mt.mayaT_kin = d;
     return mt;
}

double
from_maya_to_working_time (struct mayaT *mt) /* Converts a maya struct of time to days*/
{
     double days;
     days =  (double)(mt->mayaT_baktun * BAKTUN);
     days += (double)(mt->mayaT_katun * KATUN);
     days += (double)(mt->mayaT_tun * TUN);
     days += (double)(mt->mayaT_uinal * UINAL);
     days += (double)(mt->mayaT_kin * KIN);
     return days;

}
void
mprint(int num) /* Currently not in use. prints a number in to dots and bar (up to 19)*/
{
     int dnum, bnum;
     bnum = num/5;
     dnum = num%5;
     if (num == 0) {
          printf("<::>\n\n");
          return;
     }
     for (int c = 0; c < dnum; c++)
          printf(".");
     if (dnum != 0)
          printf("\n");
     if (bnum == 1)
          printf("----\n");
     else if (bnum == 2)
          printf("====\n");
     else if (bnum == 3)
          printf("≡≡≡≡\n");
     printf("\n");
}

void
convert (int num) { /* Currently not in use. prints a number in to dots and bar (up to infinty)*/
     int get_highest, working_number, current_divider;
     get_highest = (int)(log10(num)/log10(20));
     working_number = num;

     for (; get_highest >= 0; get_highest--) {
          current_divider = pow(20, get_highest);
          mprint((working_number/current_divider));
          printf("%d\n", (int)(working_number/current_divider));
          working_number = fmod(working_number, current_divider);
     }
}

void
print_calendar_round (int working_time) { /* Formats time in days to the month and days in the Maya calendar*/
     int wn, nmonth, imonth;
     int nday, iday;
     wn = (working_time%365 + days_toadd)%365;
     iday = fmod(fmod(working_time, 13) + donc, 13);
     nday = fmod(fmod(working_time, 20) + ndonc, 20);
     nmonth = wn/UINAL;
     imonth = fmod(wn, UINAL);
     printf("%d %s ", iday, day_names[nday]);
     printf("%d %s\n", imonth, month_names[nmonth]);
}

void
print_long_round (struct mayaT *mt) { /* Prints the given Maya struct */
     printf("%d.%d.%d.%d.%d\n", (int)mt->mayaT_baktun,
            (int)mt->mayaT_katun, (int)mt->mayaT_tun,
            (int)mt->mayaT_uinal, (int)mt->mayaT_kin);
}

void
fill_array(int arr[5]) /* Fills an array of 5 elements only used in one function */
{
     for (int i = 0; i < 5; i++)
          arr[i] = 0;
}

void
reverse(int *x, int begin, int end) { /* flips an array of ints */
     int c;

     if (begin >= end)
          return;

     c          = *(x+begin);
     *(x+begin) = *(x+end);
     *(x+end)   = c;

     reverse(x, ++begin, --end);
}

struct mayaT
string2maya (char *string) { /* To parse an user input of time doesn't check if its valid */
     struct mayaT maya_out;
     int maya_array[5], i;
     const char del[2] = ".";
     char *token;
     double *maya_ptr = &(maya_out.mayaT_baktun);

     fill_array(maya_array);
     token = strtok(string, del);
     i = 0;
     while ( token != NULL ) {
          maya_array[i] = atoi(token);
          /* printf(" %s\n", token); */
          token = strtok(NULL, del);
          i++;
     }
     reverse(maya_array , 0, sizeof(maya_array)/sizeof(maya_array[0]) -1);
     for (int i = 0; i < 5; i++) {
          printf("%d\n", maya_array[i]);
     }
     for (int i = 0; i < sizeof(maya_out)/sizeof(double); i++)
     {
          *maya_ptr = maya_array[i];
          (*maya_ptr)++;
     }
     return maya_out;
}

struct mayaT
add_dates (struct mayaT *add, struct mayaT *to) { /* Adds two dates and return the result */
     double totalDays;
     totalDays = from_maya_to_working_time(add) + from_maya_to_working_time(to);
     return from_working_time_to_maya(totalDays);
}
