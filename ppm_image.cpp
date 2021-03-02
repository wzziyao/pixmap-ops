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

   format = orig.format;
   w = orig.w;
   h = orig.h;
   max_color_val = orig.max_color_val;
   ppm_pixel colors[w * h];
   for(int i = 0; i < w; i++) {
      for(int j = 0; j < h; j++) {
         unsigned char r = this->colors[i * w + j].r;
         unsigned char g = this->colors[i * w + j].g;
         unsigned char b = this->colors[i * w + j].b;
         colors[i * w + j] = {r, g, b};
      }
   }

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
      for(int i = 0; i < w * h; i++) {
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
   fstream newfile;
   newfile.open (filename);

   if (w == 0 || h == 0 || newfile.fail()) {
      return false;
   }

   newfile << format << endl;
   newfile << w << " " << h << endl;
   newfile << max_color_val << endl;
   for(int i = 0; i < h; i++) {
      for(int j = 0; j < w; j++) {
         newfile << colors[i * w + j].r << " " << colors[i * w + j].g << " " << colors[i * w + j].b << " ";
      }
      newfile << endl;
   }
   newfile.close();
   return true;
}

 ppm_image ppm_image::resize(int w, int h) const
{
    ppm_image result;
    return result;
}

ppm_image ppm_image::flip_horizontal() const
{
   ppm_image result;
   result = *this;
   for (int i = 0; i < result.h/2; i++) {
      for (int j = 0; j < result.w; j++) {
         ppm_pixel temp = result.colors[i * w + j];
         result.colors[i * w + j] = result.colors[(h-1-i) * w + j];
         result.colors[(h-1-i) * w + j] = temp;
      }
   }
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
