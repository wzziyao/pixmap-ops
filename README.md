# pixmap-ops

Image manipulation demos based on the PPM image format.

TODO: Add a representative image for your project here

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

Original Image:
<img src="images/hogwarts.ppm" alt="original" width="500"/>

Rotate Clockwise:
```
ppm_image rotateClockwise()
```
<img src="images/hogwarts_rotate.ppm" alt="rotateClockwise" width="500"/>

Invert Colors:
```
ppm_image invertColors()
```
<img src="images/hogwarts_invert.ppm" alt="invertColors" width="500"/>

Sepia:
```
ppm_image sepia()
```
<img src="images/hogwarts_sepia.ppm" alt="sepia" width="500"/>

Border:
```
ppm_image rotateClockwise()
```
<img src="images/hogwarts_border.ppm" alt="border" width="500"/>

Swirl Colors:
```
ppm_image swirlColors()
```
<img src="images/hogwarts_swirl.ppm" alt="swirlColors" width="500"/>

Box Blur:
```
ppm_image boxBlur()
```
<img src="images/hogwarts_blur.ppm" alt="boxBlur" width="500"/>

## Results

After applying the sepia, border, box blur, and swirl colors filters:

<img src="images/hogwarts_uniqye.ppm" alt="unique" width="500"/>

