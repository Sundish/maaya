#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* #include "config.h" */

#include "calc.h"

static void
usage (void)
{
     fputs("usage: maaya [-l print long round] [-c print calendar round]\n"
	   "             [+ add long count]\n", stderr);
     exit(1);
}

int
main(int argc, char *argv[])
{
     /* int num_to_convert; */
     struct mayaT wm;
     int static_i;
     from_working_time_to_maya(get_working_time(), &wm);
     if (argc == 1)
          print_long_round(&wm);
     for (int i = 1; i < argc; i++)
     {
          if (!strcmp(argv[i], "-l"))
               print_long_round(&wm);
          else if (!strcmp(argv[i], "-c"))
               print_calendar_round((int)get_working_time());
          else if (i + 1 == argc)
               usage();
          else if (!strcmp(argv[i++], "+")) {
               static_i = argc - i;
               struct mayaT tm_list[static_i];
               for (int pos = 0; pos < static_i; pos++) {
                    string2maya(argv[i++], &tm_list[pos]);
               }
               add_dates_all(&tm_list, static_i - 1, 0);
          } else
               usage();
     }
     return 0;
}
