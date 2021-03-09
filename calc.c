#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "calc.h"

const int BAKTUN = 144000;
const int KATUN = 7200;
const int TUN = 360;
const int UINAL = 20;
const int KIN = 1;

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
     return ceil(0.000011574*difftime(time(NULL),
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

void print_long_round(struct mayaT *mt) {
     printf("%d.%d.%d.%d.%d\n", (int)mt->mayaT_baktun,
            (int)mt->mayaT_katun, (int)mt->mayaT_tun,
            (int)mt->mayaT_uinal, (int)mt->mayaT_kin);
}
