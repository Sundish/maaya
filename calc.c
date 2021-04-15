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
              , "Kaban", "Etz'nab", "Kawak" };

static const char *month_names[] = { "Pop", "Uo", "Zip", "Zotz'", "Tzek", "Xul", "YaxKin", "Mol"
     , "Ch'en", "Yax", "Zak", "Keh", "Mak", "Kankin", "Muan", "Pax"
     , "Kayab", "K'umk'u", "Wayeb" };

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

void
from_working_time_to_maya (double wt, struct mayaT *mt) { /* Converts the time in days to time in a maya struct */
     double a, b, c, d;
     a = fmod(wt,144000);
     b = fmod(a, 7200);
     c = fmod(b, 360);
     d = fmod(c, 20);
     mt->mayaT_baktun = (wt/BAKTUN);
     mt->mayaT_katun = (a/KATUN);
     mt->mayaT_tun = (b/TUN);
     mt->mayaT_uinal = (c/UINAL);
     mt->mayaT_kin = d;
}

double
from_maya_to_working_time (struct mayaT *mt) /* Converts a maya struct of time to days*/
{
     double days;
     days =  (mt->mayaT_baktun * BAKTUN);
     days += (mt->mayaT_katun * KATUN);
     days += (mt->mayaT_tun * TUN);
     days += (mt->mayaT_uinal * UINAL);
     days += (mt->mayaT_kin * KIN);
     /* printf("DAYS: %f\n",days); */
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
fill_mayaT (struct mayaT *mt)
{
     mt->mayaT_baktun = 0;
     mt->mayaT_katun = 0;
     mt->mayaT_tun = 0;
     mt->mayaT_uinal = 0;
     mt->mayaT_kin = 0;
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

void
string2maya (char *instr, struct mayaT *mt) { /* To parse an user input of time doesn't check if its valid */
     const char del[2] = ".";
     char *token;
     double *maya_ptr = &(mt->mayaT_baktun);


     token = strtok(instr, del);

     while ( token != NULL ) {
          *maya_ptr = atoi(token);
          token = strtok(NULL, del);
          maya_ptr++;
     }
}

void
add_dates_all (struct mayaT *may_ptr, int size, int beg, int use_ct) {
     double totalD = use_ct ? get_working_time() : 0.0;
     while (size >= beg) {
          totalD += from_maya_to_working_time(may_ptr++);
          beg++;
     }
     from_working_time_to_maya(totalD, may_ptr);
     print_long_round(may_ptr);
     exit(0);
}

void
substract_dates_all (struct mayaT *may_ptr, int size, int beg, int use_ct) {
     double totalD = use_ct ? get_working_time() : from_maya_to_working_time(may_ptr++);
     beg++;
     while (size >= beg) {
          totalD -= from_maya_to_working_time(may_ptr++);
          beg++;
     }
     from_working_time_to_maya(totalD, may_ptr);
     print_long_round(may_ptr);
     exit(0);
}
