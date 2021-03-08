#include <stdio.h>
#include <stdlib.h>
#include <MagickWand/MagickWand.h>

#include "config.h"

int main(int argc,char **argv)
{
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
     d_wand = NewDrawingWand();
     c_wand = NewPixelWand();

     PixelSetColor(c_wand, background_color);
     MagickNewImage(m_wand, diameter, diameter, c_wand);

     DrawSetStrokeOpacity(d_wand,1);

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

     /* Draw any required ones (circles) */
     for (int n=0; n < dwr_ndots ; n++)
          DrawCircle(d_wand, (distance*(n + 1)), x_pos + y_padding,
                     (distance*(n + 1)) + 30, x_pos + y_padding);

     x_pos = dwr_ndots == 0 ? 50 : 100 + y_padding;

     /* Draw any required fives (rectangles) */
     for (int n=0; n < dwr_nbars; n++)
     {
          DrawRectangle(d_wand, 50, x_pos, 600, x_pos + y_width);
          x_pos += y_width + y_padding;
     }

     PopDrawingWand(d_wand);

     MagickDrawImage(m_wand,d_wand);
     MagickWriteImage(m_wand, output_image);

     c_wand = DestroyPixelWand(c_wand);
     m_wand = DestroyMagickWand(m_wand);
     d_wand = DestroyDrawingWand(d_wand);

     MagickWandTerminus();
}
