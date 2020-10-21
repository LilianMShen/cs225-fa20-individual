#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

MyColorPicker::MyColorPicker(HSLAPixel cOne, HSLAPixel cTwo, unsigned stripeWidth) {
  colorOne = cOne;
  colorTwo = cTwo;
  stripe = stripeWidth;
}

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */

  //stripes!
  if ((x / stripe) % 2 == 0) {
    return colorOne;
  } 
  return colorTwo;
}
