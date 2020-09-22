#include "Image.h"
#include "StickerSheet.h"

int main() {

  Image alma;
  alma.readFromFile("tests/alma.png");
  Image i;
  i.readFromFile("tests/i.png");

  StickerSheet s1(alma, 5);
  s1.addSticker(i, 20, 200);
  s1.addSticker(i, 40, 200);

  StickerSheet s2(s1);
  s2.removeSticker(1);

  s2.render().writeToFile("myImage.png");
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  return 0;
}
