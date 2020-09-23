#include "StickerSheet.h"
#include "Image.h"
#include "cs225/HSLAPixel.h"

using cs225::HSLAPixel;

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    background = new Image(picture);
    maxStickers = (max);
    numStickers = 0;
    stickers = new Image*[(maxStickers)];
    xCoords = new unsigned[(maxStickers)];
    yCoords = new unsigned[(maxStickers)];

    /**

    for (unsigned i = 0; i < (maxStickers); i++) {
        stickers[i] = NULL;
        xCoords[i] = 0;
        yCoords[i] = 0;
    }*/
}

StickerSheet::~StickerSheet() {
    clear();
}

StickerSheet::StickerSheet(const StickerSheet &other) {
    copy(other);
}

const StickerSheet& StickerSheet::operator= (const StickerSheet &other) {
    if (this != &other) {
        clear();
        copy(other);
    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
    Image** newStickers = new Image*[numStickers];
    unsigned * newXCoords = new unsigned[numStickers];
    unsigned * newYCoords = new unsigned[numStickers];

    for (unsigned index = 0; index < numStickers; index++) {
        newStickers[index] = stickers[index];
        newXCoords[index] = xCoords[index];
        newYCoords[index] = yCoords[index];
    }

    delete[] stickers;
    delete[] xCoords;
    delete[] yCoords;

    maxStickers = max;

    stickers = new Image*[maxStickers];
    xCoords = new unsigned[maxStickers];
    yCoords = new unsigned[maxStickers];

    for (unsigned i = max; i < numStickers; i++) {
        delete newStickers[i];
        newStickers[i] = NULL;
    }
    
    if (max < numStickers) {
        numStickers = max;
    }

    for (unsigned l = 0; l < (numStickers); l++) {
        stickers[l] = newStickers[l];
        xCoords[l] = newXCoords[l];
        yCoords[l] = newYCoords[l];
    }

    /**
    for (unsigned i = numStickers; i < maxStickers; i++) {
        stickers[i] = NULL;
        xCoords[i] = 0;
        yCoords[i] = 0;
    }**/
    
    delete[] newStickers;
    delete[] newXCoords;
    delete[] newYCoords;
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
    if (numStickers < maxStickers) {
        stickers[numStickers] = new Image(sticker);
        xCoords[numStickers] = x;
        yCoords[numStickers] = y;
    }
    numStickers++;
    return numStickers - 1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if (index < numStickers) {
        xCoords[index] = x;
        yCoords[index] = y;
        return true;
    }
    return false;
}

void StickerSheet::removeSticker(unsigned index) {
    /*
    Image ** memoryLeakFixer = new Image*[maxStickers];

    for (unsigned i = 0; i < index; i++) {
        memoryLeakFixer[i] = stickers[i];
    }
    for (unsigned j = index + 1; j < maxStickers; j++) {
        memoryLeakFixer[j - 1] = stickers[j];
    }
    memoryLeakFixer[maxStickers - 1] = new Image();
    
    delete[] stickers;
    stickers = new Image*[maxStickers];

    for (unsigned k = 0; k < maxStickers; k++) {
        stickers[k] = memoryLeakFixer[k];
    }

    delete[] memoryLeakFixer;*/

    delete stickers[index];
    stickers[index] = NULL;

    for (unsigned i = index; i < (maxStickers) - 1; i++) {
        stickers[i] = stickers[i + 1];
        xCoords[i] = xCoords[i + 1];
        yCoords[i] = yCoords[i + 1];
    }

    stickers[maxStickers - 1] = NULL;
    xCoords[(maxStickers) - 1] = 0;
    yCoords[(maxStickers) - 1] = 0;

    numStickers--;
}

Image * StickerSheet::getSticker(unsigned index) {
    if (index < numStickers) {
        Image * sticker = stickers[index];
        return sticker;
    }
    return NULL;
}

Image StickerSheet::render() const {
    Image output;
    output.resize(background->width(), background->height());

    for (unsigned i = 0; i < background->width(); i++) {
        for (unsigned j = 0; j < background->height(); j++) {
            HSLAPixel & currPixel = output.getPixel(i, j);
            HSLAPixel & newPixel = background->getPixel(i, j);
            currPixel = newPixel;
        }
    }

    for (unsigned index = 0; index < numStickers; index++) {
        Image * sticker = stickers[index];
        unsigned x = (xCoords[index]);
        unsigned y = (yCoords[index]);

        if ((*sticker).width() + (x) > (*background).width()) {
            (output).resize(sticker->width() + x, output.height());
        }
        
        if ((*sticker).height() + (y) > (*background).height()) {
            (output).resize(output.width(), sticker->height() + y);
        }

        for (unsigned i = 0; i < (*sticker).width(); i++) {
            for (unsigned j = 0; j < (*sticker).height(); j++) {
                HSLAPixel & currPixel = output.getPixel((x) + i, (y) + j);
                HSLAPixel & newPixel = (*sticker).getPixel(i, j);
                if (newPixel.a != 0) {
                    currPixel = newPixel;
                }
            }
        }
    }
    return (output);
}

void StickerSheet::clear() {
    delete background;
    for (unsigned i = 0; i < numStickers; i++) {
        delete (stickers[i]);
        stickers[i] = NULL;
    }
    delete[] stickers;
    delete[] xCoords;
    delete[] yCoords;
}

void StickerSheet::copy(const StickerSheet & other) {
    maxStickers = other.maxStickers;
    numStickers = other.numStickers;
    background = new Image(*(other.background));
    stickers = new Image*[(maxStickers)];
    xCoords = new unsigned[(maxStickers)];
    yCoords = new unsigned[(maxStickers)];

    for (unsigned i = 0; i < (numStickers); i++) {
        stickers[i] = new Image();
        (*stickers[i]) = (*other.stickers[i]);
        xCoords[i] = other.xCoords[i];
        yCoords[i] = other.yCoords[i];
    }
}