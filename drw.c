#include <stdio.h>
#include <stdlib.h>
#include <MagickWand/MagickWand.h>

#include "drw.h"

void
drw_dots (DrawingWand *wand, unsigned int ndot, unsigned int distance, double *xpos, unsigned int diameter, double ypadding)
{
     double xval = *xpos;
     double radius = diameter > 300 ? diameter*0.046875 : 5;
     for (int n=0; n < ndot ; n++)
       DrawCircle(wand, (distance*(n + 1)), xval + ypadding,
		  (distance*(n + 1)) + radius, xval + ypadding);
}

void
drw_bars (DrawingWand *wand, unsigned int nbar, unsigned int diameter, double *xpos, double ypadding)
{
     double xval = *xpos;
     double ywidth, xstart, xend;
     if (diameter > 300) {
       ywidth = diameter*0.09375;
       xstart = diameter*0.0781;
       xend = diameter*0.9375;
     } for (int n=0; n < nbar; n++) {
       DrawRectangle(wand, xstart, xval, xend, xval + ywidth);
          xval += ywidth + ypadding;
     }
     *xpos = xval;
}
