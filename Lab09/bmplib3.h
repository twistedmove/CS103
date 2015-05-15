#ifndef BMPLIB_H
#define BMPLIB_H

struct color {
   // constructors
   color(); // default, black
   color(unsigned char r, unsigned char g, unsigned char b);
   // data members
   unsigned char red;
   unsigned char green;
   unsigned char blue;
};

const color red(255, 0, 0);
const color blue(0, 0, 255);
const color green(0, 255, 0);
const color yellow(255, 255, 0);
const color cyan(0, 255, 255);
const color magenta(255, 0, 255);
const color white(255, 255, 255);
const color black(0, 0, 0);
const color gray(127, 127, 127);
const color orange(255, 127, 0);
const color purple(127, 0, 127);

const int SIZE = 256;
const int RGB = 3;

// global variable for the image.
// it is "extern" to avoid redefining when .h is multiply included
extern color std_image[SIZE][SIZE];

// read color image from the file specified, into std_image
int std_read(const char* filename);

// write color image to the file specified, from std_image
int std_write(const char* filename);

// display std_image with eog, pause 0.2 sec. (uses temp file)
void std_show();

// draw a pixel to std_image, but only if it's in-bounds
void std_draw_pixel(color pen_color,
                int r, int c);

// draw a line to std_image, w this color, between these two points
void std_draw_line(color pen_color,
               int r0, int c0, int r1, int c1);

// draw a circle to std_image, with a given color, center, radius
void std_draw_circle(color pen_color,
                 int r0, int c0, int radius);


// functions to work with individual pictures
// read color image from the file specified, into inputImage
int readRGBBMP(const char* filename, color inputImage[][SIZE]);

// write color image to the file specified, from outputImage
int writeRGBBMP(const char* filename, color outputImage[][SIZE]);

// display color image with eog, pause 0.2 sec. (uses temp file)
void showRGBBMP(color inputImage[][SIZE]);

// draw a pixel, but only if it's in-bounds
void draw_pixel(color image[][SIZE],
                color pen_color,
                int r, int c);

// draw a line with this color between these two points
void draw_line(color image[][SIZE], 
               color pen_color,
               int r0, int c0, int r1, int c1);

// draw a circle with a given color, center, radius
void draw_circle(color image[][SIZE], 
                 color pen_color,
                 int r0, int c0, int radius);

#endif
