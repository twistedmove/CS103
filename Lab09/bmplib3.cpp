#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "bmplib3.h"
#include "unistd.h"

color::color(unsigned char r, unsigned char g, unsigned char b) {
  red = r;
  green = g;
  blue = b;
} 

color::color() { // default to black
  red = 0;
  green = 0;
  blue = 0;
}

// private adaptors
void doCopy(color cimage[][SIZE], 
        unsigned char aimage[][SIZE][RGB]) {
  for (int i=0; i<SIZE; i++) {
    for (int j=0; j<SIZE; j++) {
      cimage[i][j].red = aimage[i][j][0];
      cimage[i][j].green = aimage[i][j][1];
      cimage[i][j].blue = aimage[i][j][2];
    }
  }
}

unsigned char (*tempCopy(color image[][SIZE]))[SIZE][RGB] {
  unsigned char (*result)[SIZE][RGB] 
    = new unsigned char[SIZE][SIZE][RGB];
  for (int i=0; i<SIZE; i++) {
    for (int j=0; j<SIZE; j++) {
      result[i][j][0] = image[i][j].red;
      result[i][j][1] = image[i][j].green;
      result[i][j][2] = image[i][j].blue;
    }
  }
  return result;
}

using namespace std;
using std::cout;
using std::cin;
using std::endl;

typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned int uint32;

//#define BMP_BIG_ENDIAN
#define BYTE_SWAP(num) (((num>>24)&0xff) | ((num<<8)&&0xff0000) | ((num>>8)&0xff00) | ((num<<24)&0xff000000))

typedef struct { 
  uint8    bfType1; 
  uint8    bfType2; 
  uint32   bfSize;
  uint16    bfReserved1; 
  uint16    bfReserved2; 
  uint32   bfOffBits; 
  uint32   biSize;          // size of structure, in bytes
  uint32   biWidth;         // bitmap width, in pixels
  uint32   biHeight;        // bitmap height, in pixels
  uint16    biPlanes;        // see below
  uint16    biBitCount;      // see below
  uint32   biCompression;   // see below
  uint32   biSizeImage;     // see below
  uint32   biXPelsPerMeter; // see below
  uint32   biYPelsPerMeter; // see below
  uint32   biClrUsed;       // see below
  uint32   biClrImportant;  // see below
} BITMAPFILEHEADER, *PBITMAPFILEHEADER; 

typedef struct {
  uint8 rgbBlue;
  uint8 rgbGreen;
  uint8 rgbRed;
} RGBTRIPLE;

void write_hdr(uint8 *hdr, int *hdr_idx, uint32 data, uint32 size);


uint8 tempImage[SIZE][SIZE][RGB];
uint8 tempGSImage[SIZE][SIZE];

int readRGBBMP(const char* filename, unsigned char inputImage[][SIZE][RGB])
{
  uint8 type[2];
  int headersize = 0;

  int i,j,k;

  //BITMAPFILEHEADER bfh;

  /* file pointer */
  FILE *file;
	
  /* read input bmp into the data matrix */
  if (!(file=fopen(filename,"rb")))
	{
	  cout << "Cannot open file: " << filename <<endl;
	  return(1);
	}

  fread(type, sizeof(unsigned char), 0x2, file);
  if(type[0] != 'B' and type[1] != 'M'){
    cout << "Not a BMP file" << endl;
    return(1);
  }
  fseek(file, 8, SEEK_CUR);
  fread(&headersize, sizeof(uint32), 1, file);
#ifdef BMP_BIG_ENDIAN
  headersize = BYTE_SWAP(headersize); 
#endif
  //cout << "Header size is " << headersize << endl;

  fseek(file, headersize, SEEK_SET);
  fread(tempImage, sizeof(uint8), SIZE*SIZE*RGB, file);
  cout << (int)tempImage[0][0][0] << "," << (int)tempImage[0][0][1] << "," << (int)tempImage[0][0][2] << endl;
  fclose(file);

  for(i=0; i < SIZE; i++){
    for(j=0; j < SIZE; j++){
      for(k=0; k < RGB; k++){
	inputImage[SIZE-1-i][j][RGB-1-k] = tempImage[i][j][k];
	//cerr << tempImage[i][j][k] << ",";
      }
    }
	//cerr << endl;
  }
  return 0;
}

int writeRGBBMP(const char* filename, unsigned char outputImage[][SIZE][RGB])
{
  uint8 hdr[54];
  int hdr_idx = 0;

  int i,j,k;

  BITMAPFILEHEADER bfh;

  // file pointer
  FILE *file;
	
  bfh.bfType1 = 'B';
  bfh.bfType2 = 'M';
  bfh.bfSize = 0x36;
  bfh.bfReserved1 = 0x0;
  bfh.bfReserved2 = 0x0;
  bfh.bfOffBits = 0x36;
  
  bfh.biSize = 0x28;
  bfh.biWidth = SIZE;
  bfh.biHeight = SIZE;
  bfh.biPlanes = 1;
  bfh.biBitCount = 24;
  bfh.biCompression  = 0;
  bfh.biSizeImage = sizeof(RGBTRIPLE)*SIZE*SIZE;
  bfh.biXPelsPerMeter = 2400;
  bfh.biYPelsPerMeter = 2400;
  bfh.biClrUsed = 0;
  bfh.biClrImportant = 0;

  write_hdr(hdr, &hdr_idx, bfh.bfType1, sizeof(uint8));
  write_hdr(hdr, &hdr_idx, bfh.bfType2, sizeof(uint8));
  write_hdr(hdr, &hdr_idx, bfh.bfSize, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.bfReserved1, sizeof(uint16));
  write_hdr(hdr, &hdr_idx, bfh.bfReserved2, sizeof(uint16));
  write_hdr(hdr, &hdr_idx, bfh.bfOffBits, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biSize, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biWidth, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biHeight, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biPlanes, sizeof(uint16));
  write_hdr(hdr, &hdr_idx, bfh.biBitCount, sizeof(uint16));
  write_hdr(hdr, &hdr_idx, bfh.biCompression, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biSizeImage, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biXPelsPerMeter, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biYPelsPerMeter, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biClrUsed, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biClrImportant, sizeof(uint32));

  for(i=0; i < SIZE; i++){
    for(j=0; j < SIZE; j++){
      for(k=0; k < RGB; k++){
	tempImage[SIZE-1-i][j][RGB-1-k] = outputImage[i][j][k];
      }
    }
  }

  // write result bmp file
  if (!(file=fopen(filename,"wb")))
    {
      cout << "Cannot open file: " << filename << endl;
      return(1);
    }
  fwrite(&hdr, sizeof(unsigned char), 0x36, file);
  fwrite(tempImage, sizeof(unsigned char), SIZE*SIZE*RGB, file);
  fclose(file);

  return 0;
}

void write_hdr(uint8 *hdr, int *hdr_idx, uint32 data, uint32 size)
{
  if(size == 1){
    hdr[*hdr_idx] = (uint8) data;
    (*hdr_idx) += 1;
  }
  else if(size == 2){
    hdr[*hdr_idx] = (uint8) (data & 0x00ff);
    (*hdr_idx) += 1;
    hdr[*hdr_idx] = (uint8) ((data & 0xff00) >> 8);
    (*hdr_idx) += 1;
  }
  else if(size == 4){
    hdr[*hdr_idx] = (uint8) (data & 0x000000ff);
    (*hdr_idx) += 1;
    hdr[*hdr_idx] = (uint8) ((data & 0x0000ff00) >> 8);
    (*hdr_idx) += 1;
    hdr[*hdr_idx] = (uint8) ((data & 0x00ff0000) >> 16);
    (*hdr_idx) += 1;
    hdr[*hdr_idx] = (uint8) ((data & 0xff000000) >> 24);
    (*hdr_idx) += 1;
  }
  else {
    printf("Illegal size in write_hdr...consult your instructor\n"); 
  }
}

int readGSBMP(const char* filename, unsigned char inputImage[][SIZE])
{
  uint8 type[2];
  int headersize = 0;

  int i,j;

  //BITMAPFILEHEADER bfh;

  /* file pointer */
  FILE *file;
	
  /* read input bmp into the data matrix */
  if (!(file=fopen(filename,"rb")))
	{
	  cout << "Cannot open file: " << filename <<endl;
	  return(1);
	}

  fread(type, sizeof(unsigned char), 0x2, file);
  if(type[0] != 'B' and type[1] != 'M'){
    cout << "Not a BMP file" << endl;
    return(1);
  }
  fseek(file, 8, SEEK_CUR);
  fread(&headersize, sizeof(uint32), 1, file);
#ifdef BMP_BIG_ENDIAN
  headersize = BYTE_SWAP(headersize); 
#endif
  //cout << "Header size is " << headersize << endl;

  fseek(file, headersize, SEEK_SET);
  fread(tempGSImage, sizeof(uint8), SIZE*SIZE, file);
  //  cout << (int)tempGSImage[0][0][0] << "," << (int)tempGSImage[0][0][1] << "," << (int)tempGSImage[0][0][2] << endl;
  fclose(file);

  for(i=0; i < SIZE; i++){
    for(j=0; j < SIZE; j++){
	inputImage[SIZE-1-i][j] = tempGSImage[i][j];
	//	inputImage[SIZE-1-i][SIZE-1-j] = tempGSImage[i][j];
	//cerr << tempGSImage[i][j][k] << ",";
    }
	//cerr << endl;
  }
  return 0;
}


int writeGSBMP(const char* filename, unsigned char outputImage[][SIZE])
{
  uint8 hdr[54];
  int hdr_idx = 0;

  int i,j;

  BITMAPFILEHEADER bfh;

  // file pointer
  FILE *file;
	
  bfh.bfType1 = 'B';
  bfh.bfType2 = 'M';
  // 0x10436 = 2^16 + 1024 for color def + 0x36 for header
  bfh.bfSize = 0x010436; //0x36;
  
  bfh.bfReserved1 = 0x0;
  bfh.bfReserved2 = 0x0;
  // 0x0436
  bfh.bfOffBits = 0x436; //0x36;
  
  bfh.biSize = 0x28;
  bfh.biWidth = SIZE;
  bfh.biHeight = SIZE;
  bfh.biPlanes = 1;
  bfh.biBitCount = 8;
  bfh.biCompression  = 0;
  bfh.biSizeImage = SIZE*SIZE;
  bfh.biXPelsPerMeter = 0; //2400;
  bfh.biYPelsPerMeter = 0; //2400;
  bfh.biClrUsed = SIZE; // 0;
  bfh.biClrImportant = SIZE; // 0;

  write_hdr(hdr, &hdr_idx, bfh.bfType1, sizeof(uint8));
  write_hdr(hdr, &hdr_idx, bfh.bfType2, sizeof(uint8));
  write_hdr(hdr, &hdr_idx, bfh.bfSize, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.bfReserved1, sizeof(uint16));
  write_hdr(hdr, &hdr_idx, bfh.bfReserved2, sizeof(uint16));
  write_hdr(hdr, &hdr_idx, bfh.bfOffBits, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biSize, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biWidth, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biHeight, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biPlanes, sizeof(uint16));
  write_hdr(hdr, &hdr_idx, bfh.biBitCount, sizeof(uint16));
  write_hdr(hdr, &hdr_idx, bfh.biCompression, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biSizeImage, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biXPelsPerMeter, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biYPelsPerMeter, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biClrUsed, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biClrImportant, sizeof(uint32));


  for(i=0; i < SIZE; i++){
    for(j=0; j < SIZE; j++){
      //tempGSImage[SIZE-1-i][SIZE-1-j] = outputImage[i][j]; 
	tempGSImage[SIZE-1-i][j] = outputImage[i][j];
    }
  }

  // write result bmp file
  if (!(file=fopen(filename,"wb")))
    {
      cout << "Cannot open file: " << filename << endl;
      return(1);
    }
  uint8 z = 0;
  fwrite(&hdr, sizeof(unsigned char), 0x36, file);
  for(i=0; i < SIZE; i++){
    uint8 x = i;
    //cout << (int)x << endl;
    fwrite(&x, sizeof(uint8), 0x01, file);
    fwrite(&x, sizeof(uint8), 0x01, file);
    fwrite(&x, sizeof(uint8), 0x01, file);
    fwrite(&z, sizeof(uint8), 0x01, file);
 
  }
  fwrite(tempGSImage, sizeof(unsigned char), SIZE*SIZE, file);
  fclose(file);

  return 0;
}









// int readGS_BMP(char filename[], unsigned char image[][SIZE], BMPHDR *hdr)
// {
//   int i,j;

//   // Open the file for reading and ensure it opened successfully
//   //  Print a message and return -1 if it fails
//   ifstream ifile(filename);
//   if( ! ifile.good() ){
//     cerr << "Unable to open file: " << filename << endl;
//     return -1;
//   }

//   BMPTYPE type;
//   // Read in the BMP Header
//   ifile.read( reinterpret_cast<char *>(&type), sizeof(BMPTYPE) );


//   // Check its the format we want
//   if(type.signature[0] != 'B' && type.signature[1] != 'M'){
//     cerr << "Not a BMP file" << endl;
//     return -1;
//   }

//   // Read in the BMP Header
//   ifile.read( reinterpret_cast<char *>(hdr), sizeof(BMPHDR) );

//   // Print out the file size in bytes and the byte offset to the pixel array
//   cout << "Size of the file: " << hdr->fh.fileSize << endl;
//   cout << "Pixel offset: " << hdr->fh.pixelOffset << endl;

//   // Print out the dimensions (height x width) read in from the file header
//   cout << "Dimensions:  " << hdr->bh.height << "x" << hdr->bh.width << endl;
//   // Print out the color depth (planes * bits_per_pixel) 
//   //  read in from the file header
//   cout << "Color depth: " << hdr->bh.planes * hdr->bh.bpp << endl;

//   // Seek to the point in the file where the pixel data starts
//   ifile.seekg(hdr->fh.pixelOffset, ios::beg);

//   // Ensure the SEEK (read) pointer of the FILE is now pointing at the
//   // pixel array

//   // Data is read in opposite order (it is stored backwards in the file)
//   for(i=0; i < SIZE; i++){
//     for(j=0; j < SIZE; j++){
//       ifile.read( reinterpret_cast<char *>(&image[SIZE-1-i][j]), sizeof(uint8));
//     }
//   }
//   return 0;
// }


// int writeGS_BMP(char *filename, uint8 outputImage[][SIZE], BMPHDR *hdr)
// {
//   ofstream ofile(filename);
//   if(! ofile.good() ){
//     cerr << "Can't open file: " << filename << endl;
//     return -1;
//   }

//   BMPTYPE type;
//   type.signature[0] = 'B';
//   type.signature[1] = 'M';
//   ofile.write( reinterpret_cast<char *>(&type), sizeof(BMPTYPE) );

//   // Write the hdr (which is of size:  sizeof(BMPHDR size) ) data to the file
//   ofile.write( reinterpret_cast<char *>(hdr), sizeof(BMPHDR) );

//   // For bits_per_pixel <= 8 we have to write in the color table
//   uint8 colorVal[4] = {0,0,0,0};
//   for(int i=0; i < SIZE; i++){
//     colorVal[0] = colorVal[1] = colorVal[2] = i;
//     ofile.write( reinterpret_cast<char *>(colorVal), 4*sizeof(uint8) );
//   }

//   // Write the data in opposite order
//   for(int i=0; i < SIZE; i++){
//     for(int j=0; j < SIZE; j++){
//       ofile.write( reinterpret_cast<char *>(&outputImage[SIZE-1-i][j]), sizeof(uint8) );
//     }
//   }

//   ofile.close();
//   return 0;
// }

int readRGBBMP(const char* filename, color inputImage[][SIZE]) {
  unsigned char (*copy)[SIZE][RGB] = tempCopy(inputImage);
  int result = readRGBBMP(filename, copy);
  doCopy(inputImage, copy);
  delete copy;
  return result;
}

int writeRGBBMP(const char* filename, color outputImage[][SIZE]) {
  unsigned char (*copy)[SIZE][RGB] = tempCopy(outputImage); 
  int result = writeRGBBMP(filename, copy);
  delete copy;
  return result;
}



int shows = 0;

void show() {
  system("eog --single-window /tmp/bmplib.bmp &");

  // wait longer on the first show, OS takes time to start eog
  if (shows == 0) sleep(1);

  // generally, wait 0.2 seconds = 200000 milliseconds
  usleep(200000);
  shows++;
}

void showRGBBMP(unsigned char inputImage[][SIZE][RGB]) {
  writeRGBBMP("/tmp/bmplib.bmp", inputImage);
  show();
}

void showRGBBMP(color inputImage[][SIZE]) {
  unsigned char (*copy)[SIZE][RGB] = tempCopy(inputImage);
  writeRGBBMP("/tmp/bmplib.bmp", copy);
  show();
  delete copy;
}

void showGSBMP(unsigned char inputImage[][SIZE]) {
  writeGSBMP("/tmp/bmplib.bmp", inputImage);
  show();
}

// draw a pixel, but only if it's in-bounds
void draw_pixel(color image[][SIZE],
                color pen_color,
                int r, int c) {
    if (r >= 0 && c >= 0 && r < SIZE && c < SIZE) {
        image[r][c] = pen_color;
    }
}

// draw a line with this color between these two points
void draw_line(color image[][SIZE], 
               color pen_color,
               int r0, int c0, int r1, int c1) {
  int steps = max(abs(r1-r0), abs(c1-c0));
  double dr = (r1-r0)/(double)steps;
  double dc = (c1-c0)/(double)steps;
  double r = r0+0.5;
  double c = c0+0.5;
  for (int i=0; i<=steps; i++) {
    draw_pixel(image, pen_color, r, c);
    r += dr;
    c += dc;
  }
}

// draw a circle with a given color, center, radius
void draw_circle(color image[][SIZE], 
                 color pen_color,
                 int r0, int c0, int radius) {
  int f = 1 - radius;
  int ddF_x = 0;
  int ddF_y = -2 * radius;
  int x = 0;
  int y = radius;
 
  draw_pixel(image, pen_color, r0, c0 + radius);
  draw_pixel(image, pen_color, r0, c0 - radius);
  draw_pixel(image, pen_color, r0 + radius, c0);
  draw_pixel(image, pen_color, r0 - radius, c0);
 
  while (x < y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x + 1;    
    draw_pixel(image, pen_color, r0 + x, c0 + y);
    draw_pixel(image, pen_color, r0 - x, c0 + y);
    draw_pixel(image, pen_color, r0 + x, c0 - y);
    draw_pixel(image, pen_color, r0 - x, c0 - y);
    draw_pixel(image, pen_color, r0 + y, c0 + x);
    draw_pixel(image, pen_color, r0 - y, c0 + x);
    draw_pixel(image, pen_color, r0 + y, c0 - x);
    draw_pixel(image, pen_color, r0 - y, c0 - x);               
  }
}

// draw a pixel to stdimg, but only if it's in-bounds
void std_draw_pixel(color pen_color,
                int r, int c) {
   draw_pixel(std_image, pen_color, r, c);
}

// draw a line to stdimg, with this color between these two points
void std_draw_line(color pen_color,
               int r0, int c0, int r1, int c1) {
   draw_line(std_image, pen_color, r0, c0, r1, c1);
}               

// draw a circle to stdimg, with a given color, center, radius
void std_draw_circle(color pen_color,
                 int r0, int c0, int radius) {
   draw_circle(std_image, pen_color, r0, c0, radius);
}                 

int std_read(const char* filename) {
  return readRGBBMP(filename, std_image);
}

// write color image to the file specified, from outputImage
int std_write(const char* filename) {
  return writeRGBBMP(filename, std_image); 
}

// display color image with eog, pause 0.2 sec. (uses temp file)
void std_show() {
  showRGBBMP(std_image);
}

color std_image[SIZE][SIZE];
