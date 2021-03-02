#include "ppm_image.h"
#include <string>
#include <fstream>
#include <sstream> 

using namespace agl;
using namespace std;

ppm_image::ppm_image() 
{
}

ppm_image::ppm_image(int w, int h) 
{
}

ppm_image::ppm_image(const ppm_image& orig)
{
}

ppm_image& ppm_image::operator=(const ppm_image& orig)
{
   if (&orig == this) // protect against self-assignment
   {
      return *this;
   }

   // todo: your code here

   return *this;   
}

ppm_image::~ppm_image()
{
}

bool ppm_image::load(const std::string& filename)
{
   ifstream file(filename);

   if(!file) {
      file.close();
      return false;
   } else {
      string w_string;
      string h_string;
      file >> format; 
      file >> w_string; // width
      file >> h_string; // height
      file >> max_color_val; 

      stringstream width(w_string);
      stringstream height(h_string);
      width >> w;
      height >> h;
      int size = w * h;
      for(int i = 0; i < size; i++) {
         unsigned char r = 0;
         unsigned char g = 0;
         unsigned char b = 0;
         file >> r;
         file >> g;
         file >> b;
         ppm_pixel next = {r, g, b};
         colors[i] = next;
      }
      file.close();
      return true;
   }
}

bool ppm_image::save(const std::string& filename) const
{
   fstream fileStream;
   fileStream.open(filename);

   if (fileStream.fail()) {
      return false;
   } else {
      return true;
   }
}

 ppm_image ppm_image::resize(int w, int h) const
{
    ppm_image result;
    return result;
}

ppm_image ppm_image::flip_horizontal() const
{
    ppm_image result;
    return result;
}

ppm_image ppm_image::subimage(int startx, int starty, int w, int h) const
{
    ppm_image result;
    return result;
}

void ppm_image::replace(const ppm_image& image, int startx, int starty)
{
}

ppm_image ppm_image::alpha_blend(const ppm_image& other, float alpha) const
{
   ppm_image result;
   return result;
}

ppm_image ppm_image::gammaCorrect(float gamma) const
{
   ppm_image result;
   return result;
}

ppm_image ppm_image::grayscale() const
{
   ppm_image result;
   return result;
}

ppm_pixel ppm_image::get(int row, int col) const
{
   if(row <= h && col <= w) {
      return colors[row * w + col];
   } else {
      cout << "Please enter valid row and column numbers!" << endl;
      ppm_pixel empty = {0, 0, 0};
      return empty;
   }
}

void ppm_image::set(int row, int col, const ppm_pixel& c)
{
   colors[row * w + col] = c;
}

int ppm_image::height() const
{
   return h;
}

int ppm_image::width() const
{
   return w;
}
