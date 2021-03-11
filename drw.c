#include <stdio.h>
#include <stdlib.h>
#include <MagickWand/MagickWand.h>

#include "drw.h"

void
drw_dots (DrawingWand *wand, unsigned int ndot, unsigned int distance, int *xpos, unsigned int ypadding)
{
     int xval = *xpos;
     for (int n=0; n < ndot ; n++)
       DrawCircle(wand, (distance*(n + 1)), xval + ypadding,
		  (distance*(n + 1)) + 30, xval + ypadding);
}

void
drw_bars (DrawingWand *wand, unsigned int nbar, unsigned int distance, int *xpos, unsigned int ywidth, unsigned int ypadding)
{
     int xval = *xpos;
     for (int n=0; n < nbar; n++)
     {
          DrawRectangle(wand, 50, xval, 600, xval + ywidth);
          xval += ywidth + ypadding;
     }
     *xpos = xval;
}
