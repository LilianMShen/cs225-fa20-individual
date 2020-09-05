#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>
#include <cmath>

using cs225::HSLAPixel;
using cs225::PNG;

void rotate(std::string inputFile, std::string outputFile) {
  PNG* image = new PNG();
  image->readFromFile(inputFile);
  unsigned width = image->width();
  unsigned height = image->height();
  PNG* output = new PNG(width, height);

  unsigned newX = 0;
  unsigned newY = 0;

  for (unsigned int x = 0; x < width; x++) {
    for (unsigned int y = 0; y < height; y++) {
      HSLAPixel& oldPixel = image->getPixel(x,y);
      newX = width - x - 1;
      newY = height - y - 1;
      output->getPixel(newX, newY) = oldPixel;
    }
  }
  output->writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  HSLAPixel* background = new HSLAPixel(260.0, 1.0, 1.0);
  HSLAPixel* primaryColor = new HSLAPixel(333.0, 0.65, 0.82);
  HSLAPixel* secondaryColor = new HSLAPixel(253.0, 0.67, 0.77);

  unsigned multiplier = height * .05;
  unsigned quarterSide = height / 4;

  for (unsigned x = 0; x < width; x++) {
    unsigned a = (multiplier) * sin(x / multiplier) + quarterSide;
    unsigned b = (multiplier) * sin(x / multiplier) + (3 * quarterSide);
    for (unsigned y = 0; y < height; y++) {
      HSLAPixel& currPixel = png.getPixel(x,y);

      if(y < a) {
        currPixel = *primaryColor;
      } else if (y > b) {
        currPixel = *secondaryColor;
      } else {
        currPixel = *background;
      }
    }
  }

  return png;
}
