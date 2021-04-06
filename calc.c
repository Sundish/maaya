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
get_working_time (void) {
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
from_working_time_to_maya (double wt) {
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

void
mprint(int num)
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
convert (int num) {
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
print_calendar_round (int working_time) {
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
print_long_round (struct mayaT *mt) {
     printf("%d.%d.%d.%d.%d\n", (int)mt->mayaT_baktun,
            (int)mt->mayaT_katun, (int)mt->mayaT_tun,
            (int)mt->mayaT_uinal, (int)mt->mayaT_kin);
}

void fill_mayaT (struct mayaT *mt) {
     mt->mayaT_baktun = 0;
     mt->mayaT_katun = 0;
     mt->mayaT_tun = 0;
     mt->mayaT_uinal = 0;
     mt->mayaT_kin = 0;
}

void
fill_array(int arr[5])
{
     for (int i = 0; i < 5; i++)
          arr[i] = 0;
}

void reverse(int *x, int begin, int end) {
     int c;

     if (begin >= end)
          return;

     c          = *(x+begin);
     *(x+begin) = *(x+end);
     *(x+end)   = c;

     reverse(x, ++begin, --end);
}

struct mayaT
*string2maya (char *string) {
     struct mayaT maya_out;
     int maya_array[5], i;
     const char del[2] = ".";
     char *token;
     fill_mayaT(&maya_out);
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
     return &maya_out;
}
