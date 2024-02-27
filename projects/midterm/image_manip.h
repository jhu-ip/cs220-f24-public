#ifndef IMAGE_MANIP_H
#define IMAGE_MANIP_H

#include "ppm_io.h"


//////////////////////////////////
// Image manipulation functions //
//////////////////////////////////

//______grayscale______
/* convert an image to grayscale (NOTE: pixels are still
* RGB, but the three values will be equal)
*/
Image grayscale( const Image in );

/* _______alpha blend________
* blend two images into one using the given alpha factor
*/
Image blend( const Image in1, const Image in2 , double alpha );

/* _______rotate-ccw________
* rotate the input image counter-clockwise
*/
Image rotate_ccw( const Image in );

/* _______pointilism________
* apply a painting like effect i.e. poitilism technique.
*/
Image pointilism( const Image in , unsigned int seed );

//______blur______
/* apply a blurring filter to the image
*/
Image blur( const Image in , double sigma );

//______saturate______
/* Saturate the image by scaling the deviation from gray
*/
Image saturate( const Image in , double scale );

#endif
