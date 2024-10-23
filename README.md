# Alpha Channel Pixel-Perfect Collision Detection in raylib

### Overview

This is a simple demo of pixel-perfect collision detection between two images based on their alpha channels using raylib.

The main goal is to show how precise collision detection can be implemented by first checking if two objects (images) collide via bounding circles for efficiency, and then performing a pixel-perfect check by comparing the transparency (alpha) values of overlapping pixels. The collision occurs only when the non-transparent pixels of both images overlap.


### How it Works

- Bounding Circle Detection: The images are surrounded by invisible bounding circles, which are calculated based on the images' dimensions. If these circles overlap, it suggests the images are close enough for further testing.

- Pixel-Perfect Detection: If the bounding circles overlap, the algorithm checks the pixels within the overlapping area between the images. It converts the screen (world) coordinates of each pixel into local image coordinates and compares the alpha channel values. A collision occurs only if non-transparent pixels from both images overlap.

### Controls

- Mouse Movement: Moves the "ship" around the screen.
- Press S: Toggles the visibility of the bounding circles around both images.

#### Compile with these flags:
`-lraylib -lwinmm -lgdi32 -Wall -std=c99`