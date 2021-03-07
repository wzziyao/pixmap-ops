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
   
   delete[] colors;

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

   return *this;   
}

ppm_image::~ppm_image()
{
   delete[] colors;
}

bool ppm_image::load(const std::string& filename)
{
   delete[] colors;
   
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
   try {
      if (w <= 0 || h <= 0) {
         throw "Image width and height must both be positive!";
      }
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
   } catch (const char* msg) {
      cout << msg << endl;
      return *this;
   }
   
}

ppm_image ppm_image::flip_horizontal() const
{
   ppm_image result(wid, hei);
   result.format = format;
   result.max_color_val = max_color_val;
   for (int i = 0; i < result.hei/2; i++) {
      for (int j = 0; j < result.wid; j++) {
         ppm_pixel* temp = new ppm_pixel; 
         temp->r = result.colors[i * wid + j].r;
         temp->g = result.colors[i * wid + j].g;
         temp->b = result.colors[i * wid + j].b;
         result.colors[i * wid + j] = result.colors[(hei-1-i) * wid + j];
         result.colors[(hei - 1 - i) * wid + j].r = temp->r;
         result.colors[(hei - 1 - i) * wid + j].g = temp->g;
         result.colors[(hei - 1 - i) * wid + j].b = temp->b;
      }
   }
    return result;
}

ppm_image ppm_image::subimage(int startx, int starty, int w, int h) const
{
   try {
      if (startx < 0 || starty < 0 || startx >= hei || starty >= wid || w <= 0 || h <= 0) {
         throw "Top left corner must be in the image, and image width and height must both be positive!";
      }
      ppm_image result(w, h);
      result.format = format;
      result.max_color_val = max_color_val;
      int count = 0;
      for (int i = startx; i < min(startx + h, hei); i++) {
         for (int j = starty; j < min(starty + w, wid); j++) {
            result.colors[count] = colors[i * wid + j];
            count++;
         }
      }
      return result;
   } catch (const char* msg) {
      cout << msg << endl;
      return *this;
   }
}

void ppm_image::replace(const ppm_image& image, int startx, int starty)
{
   try {
      if (startx < 0 || starty < 0) {
         throw "Top left corner must be in the image!";
      }
      int count = 0;
      for (int i = startx; i < startx + image.hei; i++){
         for (int j = starty; j < starty + image.wid; j++) {
            colors[i * wid + j] = image.colors[count];
            count++;
         }
      }
   } catch (const char* msg) {
      cout << msg << endl;
   }
}

ppm_image ppm_image::alpha_blend(const ppm_image& other, float alpha) const
{
   try {
      if (alpha >= 1 || alpha <= 0) {
         throw "Alpha must be in the range [0, 1]!";
      }
      ppm_image result(wid, hei);
      result.format = format;
      result.max_color_val = max_color_val;
      for (int i = 0; i < result.hei; i++) {
         for (int j = 0; j < result.wid; j++) {
            int r, g, b;
            r = colors[i * result.wid + j].r * (1 - alpha) + other.colors[i * result.wid + j].r * alpha;
            g = colors[i * result.wid + j].g * (1 - alpha) + other.colors[i * result.wid + j].g * alpha;
            b = colors[i * result.wid + j].b * (1 - alpha) + other.colors[i * result.wid + j].b * alpha;
            result.colors[i * result.wid + j].r = (unsigned char) r;
            result.colors[i * result.wid + j].g = (unsigned char) g;
            result.colors[i * result.wid + j].b = (unsigned char) b;
         }
      }
      return result;
   } catch (const char* msg) {
      cout << msg << endl;
      return *this;
   }
}

ppm_image ppm_image::gammaCorrect(float gamma) const
{
   ppm_image result(wid, hei);
   result.format = format;
   result.max_color_val = max_color_val;
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
   ppm_image result(wid, hei);
   result.format = format;
   result.max_color_val = max_color_val;
   for (int i = 0; i < result.hei; i++) {
      for (int j = 0; j < result.wid; j++) {
         int r, g, b, c;
         r = (float) colors[i * result.wid + j].r;
         g = (float) colors[i * result.wid + j].g;
         b = (float) colors[i * result.wid + j].b;
         c = 0.3 * r + 0.59 * g + 0.11 * b;
         result.colors[i * result.wid + j].r 
         = result.colors[i * result.wid + j].g 
         = result.colors[i * result.wid + j].b 
         = (unsigned char) c;
      }
   }
   return result;
}

ppm_pixel ppm_image::get(int row, int col) const
{
   try {
      if(row > hei || col > wid) {
         throw "Please enter valid row and column numbers!";
      }
      return colors[row * wid + col];
   } catch (const char* msg) {
      cout << msg << endl;
      ppm_pixel empty = {0, 0, 0};
      return empty;
   }
}

void ppm_image::set(int row, int col, const ppm_pixel& c)
{
   try {
      if(row > hei || col > wid) {
         throw "Please enter valid row and column numbers!";
      }
      colors[row * wid + col] = c;
   } catch (const char* msg) {
      cout << msg << endl;
   }
   
}

int ppm_image::height() const
{
   return hei;
}

int ppm_image::width() const
{
   return wid;
}

ppm_image ppm_image::rotateClockwise() const
{
   int h = hei;
   int w = wid;
   ppm_image result(h, w);
   result.format = format;
   result.max_color_val = max_color_val;

   int count = 0;
   for (int i = 0; i < wid; i++){
      for (int j = hei-1; j >= 0; j--) {
         result.colors[count] = colors[j * wid + i];
         count++;
      }
   }
   return result;
}

ppm_image ppm_image::invertColors() const
{
   ppm_image result(wid, hei);
   result.format = format;
   result.max_color_val = max_color_val;

   for (int i = 0; i < hei; i++) {
      for (int j = 0; j < wid; j++) {
         result.colors[i * wid + j].r = (unsigned char) (255 - (int)colors[i * wid + j].r);
         result.colors[i * wid + j].g = (unsigned char) (255 - (int)colors[i * wid + j].g);
         result.colors[i * wid + j].b = (unsigned char) (255 - (int)colors[i * wid + j].b);
      }
   }
   return result;
}

ppm_image ppm_image::sepia() const
{
   ppm_image result(wid, hei);
   result.format = format;
   result.max_color_val = max_color_val;

   for (int i = 0; i < hei; i++) {
      for (int j = 0; j < wid; j++) {
         int r, g, b;
            r = (int) (0.393 * (float) colors[i * result.wid + j].r
             + 0.769 * (float) colors[i * result.wid + j].g 
             + 0.189 * (float) colors[i * result.wid + j].b);
            g = (int) (0.349 * (float) colors[i * result.wid + j].r
             + 0.686 * (float) colors[i * result.wid + j].g 
             + 0.168 * (float) colors[i * result.wid + j].b);
            b = (int) (0.272 * (float) colors[i * result.wid + j].r
             + 0.534 * (float) colors[i * result.wid + j].g 
             + 0.131 * (float) colors[i * result.wid + j].b);
            r = min(r, 255);
            g = min(g, 255);
            b = min(b, 255);
            result.colors[i * result.wid + j].r = (unsigned char) r;
            result.colors[i * result.wid + j].g = (unsigned char) g;
            result.colors[i * result.wid + j].b = (unsigned char) b;
      }
   }
   return result;
}

ppm_image ppm_image::border() const
{
   ppm_image result(wid, hei);
   result.format = format;
   result.max_color_val = max_color_val;

   for (int i = 0; i < hei; i++) {
      for (int j = 0; j < wid; j++) {
         if (!(i < 50 || i > hei-51 || j < 50 || j > wid-51)) {
            result.colors[i * wid + j] = colors[i * wid + j];
         }
      }
   }
   return result;
}

ppm_image ppm_image::swirlColors() const
{
   ppm_image result(wid, hei);
   result.format = format;
   result.max_color_val = max_color_val;

   for (int i = 0; i < hei; i++) {
      for (int j = 0; j < wid; j++) {
         result.colors[i * wid + j].r = colors[i * wid + j].g;
         result.colors[i * wid + j].g = colors[i * wid + j].b;
         result.colors[i * wid + j].b = colors[i * wid + j].r;
      }
   }
   return result;
}

ppm_image ppm_image::boxBlur() const
{
   ppm_image result(wid, hei);
   result.format = format;
   result.max_color_val = max_color_val;

   int sum_r, sum_g, sum_b;

   for (int i = 0; i < hei; i++) {
      for (int j = 0; j < wid; j++) {
         result.colors[i * wid + j] = colors[i * wid + j];
         if (i < 1 || j < 1 || i + 1 == hei || j + 1 == wid) {
            result.colors[i * wid + j] = colors[i * wid + j];
         } else {
            sum_r = (int)colors[(i-1) * wid + (j-1)].r 
            + (int)colors[(i-1) * wid + j].r
            + (int)colors[(i-1) * wid + (j+1)].r
            + (int)colors[i * wid + (j-1)].r
            + (int)colors[i * wid + j].r
            + (int)colors[i * wid + (j+1)].r
            + (int)colors[(i+1) * wid + (j-1)].r
            + (int)colors[(i+1) * wid + j].r
            + (int)colors[(i+1) * wid + (j+1)].r;

            sum_g = (int)colors[(i-1) * wid + (j-1)].g
            + (int)colors[(i-1) * wid + j].g
            + (int)colors[(i-1) * wid + (j+1)].g
            + (int)colors[i * wid + (j-1)].g
            + (int)colors[i * wid + j].g
            + (int)colors[i * wid + (j+1)].g
            + (int)colors[(i+1) * wid + (j-1)].g
            + (int)colors[(i+1) * wid + j].g
            + (int)colors[(i+1) * wid + (j+1)].g;

            sum_b = (int)colors[(i-1) * wid + (j-1)].b
            + (int)colors[(i-1) * wid + j].b
            + (int)colors[(i-1) * wid + (j+1)].b
            + (int)colors[i * wid + (j-1)].b
            + (int)colors[i * wid + j].b
            + (int)colors[i * wid + (j+1)].b
            + (int)colors[(i+1) * wid + (j-1)].b
            + (int)colors[(i+1) * wid + j].b
            + (int)colors[(i+1) * wid + (j+1)].b;

            result.colors[i * wid + j].r = (unsigned char) (int) (sum_r/9);
            result.colors[i * wid + j].g = (unsigned char) (int) (sum_g/9);
            result.colors[i * wid + j].b = (unsigned char) (int) (sum_b/9);
         }
      }
   }
   return result;
}