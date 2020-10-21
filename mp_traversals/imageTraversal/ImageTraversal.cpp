#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() : traversal(NULL) {
  /** @todo [Part 1] */
  //nothing for this dumb constructor. use mine instead.
}

ImageTraversal::Iterator::Iterator(ImageTraversal * trav, PNG& png, const Point& start, double tolerance) {
  traversal = trav;
  picture = png;
  startingPoint = start;
  toler = tolerance;
  current = start;
  pixelIsTraversed = std::vector<bool>(png.width() * png.height(), false);
  //std::cout << "starting point is " << startingPoint.x << " " << startingPoint.y << std::endl;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  //std::cout << "current x y " << current.x << " " << current.y << std::endl;
  //std::cout << "image bounds " << picture.width() << " " << picture.height() << std::endl;
  
  if (traversal->empty()) {
    return *this;
  }

  traversal->pop();
  setVisited(current);

  Point right = Point(current.x + 1, current.y);
  Point down = Point(current.x, current.y + 1);
  Point left = Point(current.x - 1, current.y);
  Point up = Point(current.x, current.y - 1);

  while (!traversal->empty() && isVisited(traversal->peek())) {
    current = traversal->pop();
  }

  if (isValidNeighbor(right)) {
    traversal->add(right);
  }

  if (isValidNeighbor(down)) {
    traversal->add(down);
  }

  if (isValidNeighbor(left)) {
    traversal->add(left);
  }

  if (isValidNeighbor(up)) {
    traversal->add(up);
  }

  if (!traversal->empty()){
    current = traversal->peek();
  }

  //std::cout << "current is now " << current.x << " " << current.y << std::endl;
  return *this;
}

/**
 * Helper function to determine if the neighbor is a pixel we can travel to
 */
bool ImageTraversal::Iterator::isValidNeighbor(Point neighbor) {
  // is within image bounds
  
  if (neighbor.x >= picture.width() || (int) neighbor.x < 0) {
    //std::cout << "reached line " << __LINE__ <<std::endl;
    return false;
  }
  if (neighbor.y >= picture.height() || (int) neighbor.y < 0) {
    //std::cout << "reached line " << __LINE__ <<std::endl;
    return false;
  }

  // is within tolerance
  if (calculateDelta(picture.getPixel(startingPoint.x, startingPoint.y), picture.getPixel(neighbor.x, neighbor.y)) > toler) {
    return false;
  }

  // has it been traversed yet?
  if(isVisited(neighbor)) {
    return false;
  }

  //std::cout << "reached line " << __LINE__ <<std::endl;
  return true;
}

bool ImageTraversal::Iterator::isVisited(Point pixel) {
  return (pixelIsTraversed[picture.width() * pixel.y + pixel.x]);
}

void ImageTraversal::Iterator::setVisited(Point pixel) {
  pixelIsTraversed[picture.width() * pixel.y + pixel.x] = true;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool thisEmpty = false; 
  bool otherEmpty = false;

  if (traversal == NULL) { thisEmpty = true; }
  if (other.traversal == NULL) { otherEmpty = true; }

  if (!thisEmpty)  { thisEmpty = traversal->empty(); }
  if (!otherEmpty) { otherEmpty = other.traversal->empty(); }

  if (thisEmpty && otherEmpty) return false; // both empty then the traversals are equal, return true
  else if ((!thisEmpty)&&(!otherEmpty)) return (traversal != other.traversal); //both not empty then compare the traversals
  else return true;
}

