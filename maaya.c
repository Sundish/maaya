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
	   "             [-p convert number **not working**]\n", stderr);
     exit(1);
}

int
main(int argc, char *argv[])
{
     struct mayaT wm;
     int num_to_convert;

     wm = from_working_time_to_maya(get_working_time());
     if (argc == 1)
	  print_long_round(&wm);
     for (int i = 1; i < argc; i++)
	  if (!strcmp(argv[i], "-l"))
	       print_long_round(&wm);
	  else if (!strcmp(argv[i], "-c"))
	       print_calendar_round((int)get_working_time());
	  else if (i + 1 == argc)
	       usage();
	  else if (!strcmp(argv[i], "-p")) {
	       num_to_convert = atoi(argv[i++]);
	       convert(num_to_convert);
	  } else
	       usage();
     return 0;
}
