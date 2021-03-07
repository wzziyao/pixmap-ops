#include <iostream>
#include "ppm_image.h"
using namespace std;
using namespace agl;

int main(int argc, char** argv)
{
   // test begin
   ppm_image image;
   image.load("../images/hogwarts.ppm");

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
   // test done

   // unique image
   ppm_image unique;
   unique.load("../images/hogwarts.ppm");
   ppm_image i1 = unique.sepia(); 
   ppm_image i2 = i1.border(); 
   ppm_image i3 = i2.boxBlur(); 
   ppm_image i4 = i3.swirlColors(); 
   i4.save("hogwarts_unique.ppm");
}

