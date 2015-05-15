//--------------------------------------------------------
// File: chromakey.cpp
//
// Author: Will Gauthier
//
// email: wgauthie@usc.edu
//
// Usage: chromakey colbert_gs.bmp campus1.bmp 80 meth1.bmp meth2.bmp
//
// Notes:
// This program performs the chroma key operation  on an input 
// using two different methods.
//
// Method 1 Utilize a user-defined distance threshold from the
//          chromakey value as a discriminator
//
// Method 2 Utilize three thresholds(the farthest distances between the 
//          reference and chromakey values for each color) as a discriminator
//--------------------------------------------------------

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "bmplib.h"

using namespace std;

// Prototypes
void findAbsPtDist(unsigned char inImage[][SIZE][RGB],
       double chromaRef[RGB],
       double subDist[RGB],
       int row,
       int col);
       
void findChromaRef(unsigned char inImage[][SIZE][RGB],
       double chromaRef[RGB]);

void method1(unsigned char inImage[][SIZE][RGB], 
       bool mask[][SIZE],
       double threshold);

void method2(unsigned char inImage[][SIZE][RGB], 
       bool mask[][SIZE]);

void replace(bool mask[][SIZE],
       unsigned char inImage[][SIZE][RGB],
       unsigned char bgImage[][SIZE][RGB],
       unsigned char outImage[][SIZE][RGB]);

int main(int argc, char *argv[])
{
 // Image data array
 // Note:  Use the static keyword *ONLY* for VERY LARGE data
 //        arrays. 'static' indicates not to allocate it on 
 //        the stack but in a separate area of memory more
 //        amenable to large objects.  
 static unsigned char inputImage[SIZE][SIZE][RGB];
 static unsigned char bgrndImage[SIZE][SIZE][RGB];
 static unsigned char outputImage[SIZE][SIZE][RGB];
 static bool chromaMask[SIZE][SIZE];

 double threshold;

 if(argc < 6){
  cerr << "usage: program_name input.bmp background.bmp "
       << "dist_threshold output1.bmp output2.bmp" << endl;
  return 0;
 }
  
 if(readRGBBMP(argv[1], inputImage) ){
  cerr << "Error reading file: " << argv[1] << endl;
  return 1;
 }

 if(readRGBBMP(argv[2], bgrndImage) ){
  cout << "Error reading file: " << argv[2] << endl;
  return 1;
 }
  
 // Convert the threshold (argv[3])
 //  from string format to a double and assign to 'threshold'
 threshold = atof(argv[3]);

 // Call Method 1 Function
 method1(inputImage, chromaMask, threshold);

 // Produce the output by calling replace()
 replace(chromaMask, inputImage, bgrndImage, outputImage);

 // Write the output image to a file using the filename argv[4]
 if (writeRGBBMP(argv[4], outputImage) ){
  cout << "Error writing file: " << argv[4] << endl;
  exit(1);
 }  

 // Call Method 2 Function
 method2(inputImage, chromaMask);

 // Produce the output by calling replace()
 replace(chromaMask, inputImage, bgrndImage, outputImage);

 // Write the output image to a file using the filename argv[5]
 if (writeRGBBMP(argv[5], outputImage) ){
  cout << "Error writing file: " << argv[5] << endl;
  exit(1);
 }  

 return 0;
}



//Finds the average chroma key color by referencing the top 20 rows and the
// first and last 25 columns of the remaining rows of an input image
//
//Inputs: bitmap RGB input image, double array of size 3
//Outpus: double array input now holds the average chroma key RGB values
void findChromaRef(unsigned char inImage[][SIZE][RGB],
       double chromaRef[RGB])
{
 // Stores the number of reference pixels used to calculate the
 //  average chromakey reference point
 int inputs = 0;

 // Runs through inImage to collect RGB values for a chromakey reference point
 for(int row = 0; row < SIZE; row++)
 {
  for(int col = 0; col < SIZE; col++)
  {
   // Use the entire top 20 rows for reference
   if(row < 21)
   {
    for(int color = 0; color < RGB; color++)
     chromaRef[color] += inImage[row][col][color];

    inputs++;
   }
   // Use the first and last 25 columns of the remaining rows for reference
   else
   {
    if(col < 26 || col > SIZE-26)
    {
     for(int color = 0; color < RGB; color++)
      chromaRef[color] += inImage[row][col][color];

     inputs++;
    }
   }
  }
 } 

 // Averages the RGB values from inImage to finalize the reference point
 for(int color = 0; color < RGB; color++)
  chromaRef[color] = chromaRef[color]/inputs;
}

//Computes the absolute distances between the RGB values of the 
// reference point and the inImage point
//
//Inputs: bitmap RGB input image, chromakey reference pt array, double array 
//         of size 3, row and column number
//Outputs: double array input now holds the absolute distances between
//          the reference and inImage pts
//*Requires <cmath>
void findAbsPtDist(unsigned char inImage[][SIZE][RGB],
       double chromaRef[RGB],
       double subDist[RGB],
       int row,
       int col)
{
 for(int color = 0; color < RGB; color++)
  subDist[color] = abs(chromaRef[color]-inImage[row][col][color]);
}

//Sets a 2D mask array(0 if greenscreen, 1 if foreground) based on a
// user-provided threshold for the chroma-key distance
//
//Inputs: bitmap RGB input image, mask array, user threshold double
//Outputs: mask array is now initialized to 0 for green and 1 elsewhere
//
//*Requires findChromaRef and findAbsPtDist functions, <cmath>
void method1(unsigned char inImage[][SIZE][RGB], 
       bool mask[][SIZE],
       double threshold)
{
 // Finds and stores the average chroma key color
 double chromaRef[RGB] = {0};
 findChromaRef(inImage, chromaRef);

 // Runs through inImage to set the mask
 for(int row = 0; row < SIZE; row++)
 {
  for(int col = 0; col < SIZE; col++)
  {
   // Computes the absolute distances between the RGB values of the 
   //  reference point and the inImage point
   double subDist[RGB] = {0};
   findAbsPtDist(inImage, chromaRef, subDist, row, col);

   // Computes the distance between reference point and inImage point
   double dist = sqrt(pow(subDist[0],2)+pow(subDist[1],2)+pow(subDist[2],2));

   // Sets the mask to 0 if the distance is less than the threshold so the
   //  bgImage will be used, otherwise sets mask to 1 to leave the inImage
   if(dist < threshold)
    mask[row][col] = 0;
   else
    mask[row][col] = 1;
  }
 }
}

//Sets a 2D mask array(0 if greenscreen, 1 if foreground) based on each of
// the input image's color pixels being farther than the longest distance
// between the average chroma key pixel and the farthest reference pixel
// of that color
//
//Inputs: bitmap RGB input image, mask array
//Outputs: mask array is now initialized to 0 for green and 1 elsewhere
//
//*Requires findChromaRef and findAbsPtDist functions, <cmath>
void method2(unsigned char inImage[][SIZE][RGB], 
       bool mask[][SIZE])  
{
 double threshold[RGB] = {0}, chromaRef[RGB] = {0};

 // Finds and stores the average chroma key color
 findChromaRef(inImage, chromaRef);

 // Runs through inImage to find the largest distance between the chromakey 
 //  reference point and gathered pixel for each color
 for(int row = 0; row < SIZE; row++)
 {
  for(int col = 0; col < SIZE; col++)
  {
   // Use the entire top 20 rows for reference
   if(row < 21)
   {
    // Computes the absolute distances between the RGB values of the 
    //  reference point and the inImage point
    double subDist[RGB] = {0};
    findAbsPtDist(inImage, chromaRef, subDist, row, col);

    // Updates threshold whenever a larger distance is found
    for(int color = 0; color < RGB; color++)
    {
     if(subDist[color] > threshold[color])
      threshold[color] = subDist[color];
    }
   }
   // Use the first and last 25 columns of the remaining rows for reference
   else
   {
    if(col < 26 || col > SIZE-26)
    {
     // Same computations as in the entire top 20 rows
     double subDist[RGB] = {0};
     findAbsPtDist(inImage, chromaRef, subDist, row, col);

     for(int color = 0; color < RGB; color++)
     {
      if(subDist[color] > threshold[color])
       threshold[color] = subDist[color];
     }
    }
   }
  }
 } 

 // Adds a fractional "fudge factor" (determined by experimenting with the
 //  given images) to the threshold just in case
 for(int color = 0; color < RGB; color++)
  threshold[color] += 0.3*threshold[color];

 // Runs through inImage to set the mask
 for(int row = 0; row < SIZE; row++)
 {
  for(int col = 0; col < SIZE; col++)
  {
   // Computes the absolute distances between the RGB values of the reference
   //  point and the inImage point
   double subDist[RGB] = {0};
   findAbsPtDist(inImage, chromaRef, subDist, row, col);

   // Sets the mask to 0 if all color distances are less than the threshold
   //  so the bgImage will be used, otherwise sets mask to 1 to leave the 
   //  inImage
   if(subDist[0] < threshold[0] && subDist[1] < threshold[1] 
      && subDist[2] < threshold[2])
       mask[row][col] = 0;
   else
    mask[row][col] = 1;
  }
 }
}

//If mask[i][j] = 1 use the input image pixel for the output image
//Else if mask[i][j] = 0 use the background image pixel
//
//Inputs: mask array; bitmap RGB input, output, and background images
//Outputs: output image now is the input image green-screened 
//         with the background image
void replace(bool mask[SIZE][SIZE],
       unsigned char inImage[SIZE][SIZE][RGB],
       unsigned char bgImage[SIZE][SIZE][RGB],
       unsigned char outImage[SIZE][SIZE][RGB])
{
 // Create the output image using the mask to determine
 //  whether to use the pixel from the Input or Background image
 for(int row = 0; row < SIZE; row++)
 {
  for(int col = 0; col < SIZE; col++)
  {
   for(int color = 0; color < RGB; color++)
   {
    if(mask[row][col] == 1)
     outImage[row][col][color] = inImage[row][col][color];
    else
     outImage[row][col][color] = bgImage[row][col][color];
   }
  }
 }
}
