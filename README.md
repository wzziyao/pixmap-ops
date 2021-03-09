# pixmap-ops

Image manipulation demos based on the PPM image format.

<img src="images/hogwarts_unique.jpg" alt="unique" width="500"/>

## How to build

*Windows*

Open git bash to the directory containing this repository.

```
pixmap-ops $ mkdir build
pixmap-ops $ cd build
pixmap-ops/build $ cmake -G "Visual Studio 16 2019" ..
pixmap-ops/build $ start Pixmap-Ops.sln
```

Your solution file should contain two projects: `pixmap_art` and `pixmap_test`.
To run from the git bash command shell, 

```
pixmap-ops/build $ ../bin/Debug/pixmap_test
pixmap-ops/build $ ../bin/Debug/pixmap_art
```

*macOS*

Open terminal to the directory containing this repository.

```
pixmap-ops $ mkdir build
pixmap-ops $ cd build
pixmap-ops/build $ cmake ..
pixmap-ops/build $ make
```

To run each program from build, you would type

```
pixmap-ops/build $ ../bin/pixmap_test
pixmap-ops/build $ ../bin/pixmap_art
```

## Image operators

**Original Image:**

<img src="images/hogwarts.jpg" alt="original" width="500"/>

**Rotate Clockwise:**
Rotate an image 90 degree clockwise.
```
ppm_image rotateClockwise();
```
<img src="images/hogwarts_rotate.jpg" alt="rotateClockwise" width="500"/>

**Invert Colors:**
Invert the colors of an image, white becomes black, orange becomes blue, and so on. 
```
ppm_image invertColors();
```
<img src="images/hogwarts_invert.jpg" alt="invertColors" width="500"/>

**Sepia:**
Give an image an old-timey feel by making it look reddish-brown.
```
ppm_image sepia();
```
<img src="images/hogwarts_sepia.jpg" alt="sepia" width="500"/>

**Border:**
Add a black border around the edge of an image.
```
ppm_image border();
```
<img src="images/hogwarts_border.jpg" alt="border" width="500"/>

**Swirl Colors:**
Rotate the colors of an image.
```
ppm_image swirlColors();
```
<img src="images/hogwarts_swirl.jpg" alt="swirlColors" width="500"/>

**Box Blur:**
Create the effect of blurring or softening an image.
```
ppm_image boxBlur();
```
<img src="images/hogwarts_blur.jpg" alt="boxBlur" width="500"/>

**Resize:**
Returns a copy of an image resized to the given width and height.
```
ppm_image resize(int width, int height);
```
<img src="images/hogwarts-200-300.jpg" alt="boxBlur" width="500"/>

**Grayscale:**
Returns a copy of an image as a grayscale image.
```
ppm_image grayscale();
```
<img src="images/hogwarts-grayscale.jpg" alt="boxBlur" width="500"/>

**Horizontal Flip:**
Returns a copy of an image flipped along the horizontal middle axis.
```
ppm_image flip_horizontal();
```
<img src="images/hogwarts-flip.jpg" alt="boxBlur" width="500"/>

**Subimage:**
Returns a sub-image with top, left corner at (x,y) and width and height.
```
ppm_image subimage(int row, int col, int width, int height) const;
```
<img src="images/hogwarts-subimage.jpg" alt="boxBlur" width="500"/>

**Gamma Correction:**
Returns a copy of an image with the given gamma correction factor applied to it.
```
ppm_image gammaCorrect(float gamma);
```
<img src="images/hogwarts-gamma-0.6.jpg" alt="boxBlur" width="500"/>

## Results

Apply the sepia, border, box blur, swirl colors, and alpha blend filters on an image:

<img src="images/hogwarts_unique.jpg" alt="unique" width="500"/>

