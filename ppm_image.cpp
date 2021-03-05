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
   format = " ";
   wid = w;
   hei = h;
   colors = new ppm_pixel [wid * hei];
}

ppm_image::ppm_image(const ppm_image& orig)
{
   format = orig.format;
   wid = orig.wid;
   hei = orig.hei;
   max_color_val = orig.max_color_val;
   colors = new ppm_pixel [wid * hei];
   for(int i = 0; i < wid; i++) {
      for(int j = 0; j < hei; j++) {
         // unsigned char r = this->colors[i * w + j]->r;
         // unsigned char g = this->colors[i * w + j]->g;
         // unsigned char b = this->colors[i * w + j]->b;
         // ppm_pixel next = {r, g, b};
         // colors[i * w + j] = next;
         colors[i * wid + j] = orig.colors[i * wid + j];
      }
   }
}

ppm_image& ppm_image::operator=(const ppm_image& orig)
{
   if (&orig == this) // protect against self-assignment
   {
      return *this;
   }

   format = orig.format;
   wid = orig.wid;
   hei = orig.hei;
   max_color_val = orig.max_color_val;
   colors = new ppm_pixel [wid * hei];
   for(int i = 0; i < wid; i++) {
      for(int j = 0; j < hei; j++) {
         // unsigned char r = this->colors[i * w + j]->r;
         // unsigned char g = this->colors[i * w + j]->g;
         // unsigned char b = this->colors[i * w + j]->b;
         // ppm_pixel next = {r, g, b};
         // colors[i * w + j] = next;
         colors[i * wid + j] = orig.colors[i * wid + j];
      }
   }
   // should colors be deleted?

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
      file >> format; 
      file >> wid;
      file >> hei;
      file >> max_color_val; 

      colors = new ppm_pixel [wid * hei];

      for(int i = 0; i < wid * hei; i++) {
         int r,g,b;
         file >> r;
         file >> g;
         file >> b;
         colors[i].r = (unsigned char) r;
         colors[i].g = (unsigned char) g;
         colors[i].b = (unsigned char) b;
      }
      file.close();
      return true;
   }
}

bool ppm_image::save(const std::string& filename) const
{
   ofstream newfile (filename);

   if (wid == 0 || hei == 0 || newfile.fail()) {
      return false;
   }

   newfile << format << endl;
   newfile << wid << " " << hei << endl;
   newfile << max_color_val << endl;
   for(int i = 0; i < hei; i++) {
      for(int j = 0; j < wid; j++) {
         int r, g, b;
         r = (int) colors[i * wid + j].r;
         g = (int) colors[i * wid + j].g;
         b = (int) colors[i * wid + j].b;
         newfile << r << " " << g << " " << b << " ";
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
   for (int i = 0; i < result.hei/2; i++) {
      for (int j = 0; j < result.wid; j++) {
         ppm_pixel* temp = new ppm_pixel; 
         temp->r = result.colors[i * wid + j].r;
         temp->g = result.colors[i * wid + j].g;
         temp->b = result.colors[i * wid + j].b;
         result.colors[i * wid + j] = result.colors[(hei-1-i) * wid + j];
         result.colors[(hei-1-i) * wid + j].r = temp->r;
         result.colors[(hei-1-i) * wid + j].g = temp->g;
         result.colors[(hei-1-i) * wid + j].b = temp->b;
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
   if(row <= hei && col <= wid) {
      ppm_pixel result;
      result.r = colors[row * wid + col].r;
      result.g = colors[row * wid + col].g;
      result.b = colors[row * wid + col].b;
      // return colors[row * w + col];
      return result;
   } else {
      cout << "Please enter valid row and column numbers!" << endl;
      ppm_pixel empty = {0, 0, 0};
      return empty;
   }
}

void ppm_image::set(int row, int col, const ppm_pixel& c)
{
   // ppm_pixel input;
   // input->r = c.r;
   // input->g = c.g;
   // input->b = c.b;
   colors[row * wid + col].r = c.r;
   colors[row * wid + col].g = c.g;
   colors[row * wid + col].b = c.b;
}

int ppm_image::height() const
{
   return hei;
}

int ppm_image::width() const
{
   return wid;
}
