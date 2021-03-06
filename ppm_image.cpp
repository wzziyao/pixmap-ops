#include "ppm_image.h"
#include <string>
#include <fstream>
#include <sstream> 
#include <cmath> 

using namespace agl;
using namespace std;

ppm_image::ppm_image() 
{
}

ppm_image::ppm_image(int w, int h) 
{
   wid = w;
   hei = h;
   colors = new ppm_pixel [w * h];
   max_color_val = 0;
}

ppm_image::ppm_image(const ppm_image& orig)
{
   format = orig.format;
   wid = orig.wid;
   hei = orig.hei;
   max_color_val = orig.max_color_val;
   colors = new ppm_pixel [wid * hei];
   for (int i = 0; i < wid; i++) {
      for (int j = 0; j < hei; j++) {
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
   for (int i = 0; i < wid; i++) {
      for (int j = 0; j < hei; j++) {
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

   if (!file) {
      file.close();
      return false;
   } else {
      file >> format; 
      file >> wid;
      file >> hei;
      file >> max_color_val; 

      colors = new ppm_pixel [wid * hei];

      for (int i = 0; i < wid * hei; i++) {
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
   for (int i = 0; i < hei; i++) {
      for (int j = 0; j < wid; j++) {
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
   ppm_image result(w, h);
   result.format = format;
   result.max_color_val = max_color_val;
   for (int i = 0; i < h; i++){
      for (int j = 0; j < w; j++) {
         int x, y;
         x = floor((float) i * (hei - 1) / (h - 1));
         y = floor((float) j * (wid - 1) / (w - 1));
         result.colors[i * w + j].r = colors[x * wid + y].r;
         result.colors[i * w + j].g = colors[x * wid + y].g;
         result.colors[i * w + j].b = colors[x * wid + y].b;
      } 
   }
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
   result = *this;
   for (int i = 0; i < result.hei; i++) {
      for (int j = 0; j < result.wid; j++) {
         int r, g, b;
         r = (int) 255 * pow(((float) colors[i * result.wid + j].r/255), 1/gamma);
         g = (int) 255 * pow(((float) colors[i * result.wid + j].g/255), 1/gamma);
         b = (int) 255 * pow(((float) colors[i * result.wid + j].b/255), 1/gamma);
         result.colors[i * result.wid + j].r = (unsigned char) r;
         result.colors[i * result.wid + j].g = (unsigned char) g;
         result.colors[i * result.wid + j].b = (unsigned char) b;
      }
   }
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
      return result;
   } else {
      cout << "Please enter valid row and column numbers!" << endl;
      ppm_pixel empty = {0, 0, 0};
      return empty;
   }
}

void ppm_image::set(int row, int col, const ppm_pixel& c)
{
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
