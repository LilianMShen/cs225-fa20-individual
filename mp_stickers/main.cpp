#include "Image.h"
#include "StickerSheet.h"

int main() {
  Image background;
  background.readFromFile("pink clouds.png");
  //background.desaturate(.1);

  Image hamOne, hamTwo, hamThree, hamFour, hamFive, hamSix, hamSeven, hamEight, hamNine, hamTen, hamEleven, hamTwelve, hamThirteen;
  hamOne.readFromFile("1.png");
  hamTwo.readFromFile("2.png");
  hamThree.readFromFile("3.png");
  hamFour.readFromFile("4.png");
  hamFive.readFromFile("5.png");
  hamSix.readFromFile("6.png");
  hamSeven.readFromFile("7.png");
  hamEight.readFromFile("8.png");
  hamNine.readFromFile("9.png");
  hamTen.readFromFile("10.png");
  hamEleven.readFromFile("11.png");
  hamTwelve.readFromFile("12.png");
  hamThirteen.readFromFile("13.png");
  
  hamOne.scale(hamOne.width() * 2, hamOne.height() * 2);
  hamTwo.scale(hamTwo.width() * 2, hamTwo.height() * 2);
  hamThree.scale(hamThree.width() * 2, hamThree.height() * 2);
  hamFour.scale(hamFour.width() * 2, hamFour.height() * 2);
  hamFive.scale(hamFive.width() * 2, hamFive.height() * 2);
  hamSix.scale(hamSix.width() * 2, hamSix.height() * 2);
  hamSeven.scale(hamSeven.width() * 2, hamSeven.height() * 2);
  hamEight.scale(hamEight.width() * 2, hamEight.height() * 2);
  hamNine.scale(hamNine.width() * 2, hamNine.height() * 2);
  hamTen.scale(hamTen.width() * 2, hamTen.height() * 2);
  hamEleven.scale(hamEleven.width() * 2, hamEleven.height() * 2);
  hamTwelve.scale(hamTwelve.width() * 2, hamTwelve.height() * 2);
  hamThirteen.scale(hamThirteen.width() * 2, hamThirteen.height() * 2);
  
  StickerSheet s1(background, 13);
  
  unsigned width = background.width() / 10;
  unsigned height = background.height() / 5;
  
  s1.addSticker(hamOne, width, height); 
  s1.addSticker(hamTwo, 3 * width, height);
  s1.addSticker(hamThree, 6 * width, height);
  s1.addSticker(hamFour, width, 2 *height);
  s1.addSticker(hamFive, 3 * width, 2 * height);
  s1.addSticker(hamSix, 6 * width, 2 *height);
  s1.addSticker(hamSeven, width, 3 * height);
  s1.addSticker(hamEight, 3 * width, 3 * height);
  s1.addSticker(hamNine, 6 * width, 3 * height);
  s1.addSticker(hamTen, width, 4 * height);
  s1.addSticker(hamEleven, 3 * width, 4 * height);
  s1.addSticker(hamTwelve, 6 * width, 4 * height);
  s1.addSticker(hamThirteen, 3 * width, height / 3); 
  
  s1.render().writeToFile("myImage.png");

  return 0;
}
