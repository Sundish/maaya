#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <MagickWand/MagickWand.h>

#include "config.h"

#include "calc.h"
#include "drw.h"



static void
usage (void)
{
     fputs("usage maaya [-l print long round]\n", stderr);
     exit(1);
}

int
main(int argc, char *argv[])
{
     struct mayaT wm;
     unsigned int num_to_convert;

     MagickWand *m_wand = NULL;
     DrawingWand *d_wand = NULL;
     PixelWand *c_wand = NULL;
     unsigned int num, x_pos;
     unsigned long diameter;

     /* Rectangle Variables */
     unsigned int dwr_nbars, y_width;
     x_pos = 50;
     y_width = 60;

     /* Circle Variables */
     unsigned int dwr_ndots, distance;
     unsigned width, height;

     /* for (int i = 1; i < argc; i++) */
     /* 	  if (!strcmp(argv[i], "-l")) { */
     /* 	       wm = from_working_time_to_maya(get_working_time()); */
     /* 	       print_long_round(&wm); */
     /* 	       exit(0); */
     /* 	  } else if (!strcmp(argv[i], "-p")) */
     /* 	       num_to_convert = atoi(argv[i++]); */
     /* 	  else */
     /* 	       usage(); */

     /* Check for user input if non exit program */
     if (argc != 2){
          fprintf(stderr, "No number supplied. Can't do nothing.\n");
          return -1;
     }

     /* Get the input number TODO: detect if the input is a valid number */
     num = atoi(argv[1]);

     dwr_nbars = num/5;
     dwr_ndots = num%5;

     diameter = 640;
     distance = diameter/(dwr_ndots == 0 ? 1 : dwr_ndots + 1); /* Avoid division by zero :P */

     MagickWandGenesis();
     m_wand = NewMagickWand();
     MagickReadImage(m_wand,"/path/to/image.jpg");

     d_wand = NewDrawingWand();
     c_wand = NewPixelWand();

     /* width = MagickGetImageWidth(m_wand); */
     /* height = MagickGetImageHeight(m_wand); */

     PixelSetColor(c_wand, background_color);
     DrawSetStrokeOpacity(d_wand, 1.0);

// circle and rectangle
     PushDrawingWand(d_wand);
// Hmmmm. Very weird. rgb(0,0,1) draws a black line around the edge
// of the circle as it should. But rgb(0,0,0) or black don't.
// AND if I remove the PixelSetColor then it draws a white boundary
// around the rectangle (and presumably around the circle too)
     PixelSetColor(c_wand,"rgb(0,0,1)");

     DrawSetStrokeColor(d_wand,c_wand);
     DrawSetStrokeWidth(d_wand,4);
     DrawSetStrokeAntialias(d_wand,1);
     PixelSetColor(c_wand, foreground_color);

     //DrawSetStrokeOpacity(d_wand,1);
     DrawSetFillColor(d_wand,c_wand);
     DrawTranslate(d_wand, x_margin, y_margin);

     /* Draw any required ones (circles) */
     drw_dots(d_wand, dwr_ndots, distance, &x_pos, y_padding);

     x_pos = dwr_ndots == 0 ? 50 : 100 + y_padding;
     /* Draw any required fives (rectangles) */
     drw_bars(d_wand, dwr_nbars, distance, &x_pos, y_width, y_padding);

     PopDrawingWand(d_wand);

     MagickDrawImage(m_wand, d_wand);

     MagickWriteImage(m_wand, "test.jpg");

     c_wand = DestroyPixelWand(c_wand);
     d_wand = DestroyDrawingWand(d_wand);
     if(m_wand)m_wand = DestroyMagickWand(m_wand);

     MagickWandTerminus();
     return 0;
}
