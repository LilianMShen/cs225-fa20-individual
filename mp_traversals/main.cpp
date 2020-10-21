
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready. 

  PNG berd;
  berd.readFromFile("berd.png");
  FloodFilledImage picture(berd);

  DFS dfs(berd, Point(0,0), .1);
  BFS bfs(berd, Point(berd.width() / 2, berd.height() / 2), .1);

  MyColorPicker stripes(HSLAPixel(183, 1, .86, 1), HSLAPixel(189, 0, 1, 1), berd.width()/5);
  SolidColorPicker furamingo(HSLAPixel(325, 1, .85, 1));

  picture.addFloodFill(dfs, stripes);
  picture.addFloodFill(bfs, furamingo);

  Animation animation = picture.animate(5000); 

  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");

  return 0;
}
