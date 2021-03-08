#include <iostream>
#include "ppm_image.h"
using namespace std;
using namespace agl;

int main(int argc, char** argv)
{
   ppm_image image;
   image.load("../images/hogwarts.ppm");

   // my filters
   // rotate clockwise
   ppm_image rotate = image.rotateClockwise(); 
   rotate.save("hogwarts_rotate.ppm"); 

   // invert colors
   ppm_image invert = image.invertColors(); 
   invert.save("hogwarts_invert.ppm"); 

   // sepia
   ppm_image sepia = image.sepia(); 
   sepia.save("hogwarts_sepia.ppm"); 

   // border
   ppm_image border = image.border(); 
   border.save("hogwarts_border.ppm"); 

   // swirl colors
   ppm_image swirl = image.swirlColors(); 
   swirl.save("hogwarts_swirl.ppm"); 

   // box blur
   ppm_image blur = image.boxBlur(); 
   blur.save("hogwarts_blur.ppm"); 

   // unique image
   ppm_image unique;
   unique.load("../images/hogwarts.ppm");
   ppm_image i1 = unique.sepia(); 
   ppm_image i2 = i1.border(); 
   ppm_image i3 = i2.boxBlur(); 
   ppm_image i4 = i3.swirlColors(); 

   ppm_image letter;
   letter.load("../images/letter.ppm");

   int y = (int) (0.5f * (i4.width() - letter.width()));
   int x = (int) (0.5f * (i4.height() - letter.height()));
   ppm_image background = i4.subimage(x, y, letter.width(), letter.height());
   ppm_image blend = background.alpha_blend(letter, 0.5f);
   i4.replace(blend, x, y);
   i4.save("hogwarts_unique.ppm");
}

