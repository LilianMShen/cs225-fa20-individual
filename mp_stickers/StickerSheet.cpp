#include "StickerSheet.h"
#include "Image.h"
#include "cs225/HSLAPixel.h"

using cs225::HSLAPixel;

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    background = new Image(picture);
    maxStickers = (max);
    stickers = new Image*[(maxStickers)];
    xCoords = new unsigned[(maxStickers)];
    yCoords = new unsigned[(maxStickers)];

    for (unsigned i = 0; i < (maxStickers); i++) {
        stickers[i] = NULL;
        xCoords[i] = 0;
        yCoords[i] = 0;
    }
}

StickerSheet::~StickerSheet() {
    delete background;
    delete[] stickers;
    delete[] xCoords;
    delete[] yCoords;
}

StickerSheet::StickerSheet(const StickerSheet &other) {
    copy(other);
}

const StickerSheet& StickerSheet::operator= (const StickerSheet &other) {
    if (this != &other) {
        copy(other);
    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
    /**
    for (unsigned k = max; k < maxStickers; k++) {
        if (stickers[k] != NULL) {
            delete stickers[k];
        }
        stickers[k] = NULL;
    }*/

    if (maxStickers > max) {
        maxStickers = max;
    }

    Image ** newStickers = new Image*[(max)];
    unsigned * newXCoords = new unsigned[(max)];
    unsigned * newYCoords = new unsigned[(max)];

    for (unsigned i = 0; i < (maxStickers); i++) {
        (newStickers[i]) = (stickers[i]);
        newXCoords[i] = xCoords[i];
        newYCoords[i] = yCoords[i];
    }
    for (unsigned l = maxStickers; l < max; l++) {
        newStickers[l] = NULL;
        newXCoords[l] = 0;
        newYCoords[l] = 0;
    }

    maxStickers = max;
    delete[] stickers;
    delete[] xCoords;
    delete[] yCoords;

    stickers = new Image*[(max)];
    xCoords = new unsigned[(max)];
    yCoords = new unsigned[(max)];

    for (unsigned j = 0; j < (maxStickers); j++) {
        stickers[j] = newStickers[j];
        xCoords[j] = newXCoords[j];
        yCoords[j] = newYCoords[j];
    }

    delete[] newStickers;
    delete[] newXCoords;
    delete[] newYCoords;
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
    int lowestIndex = lowestStickerLayer();
    if (lowestIndex != -1) {
        stickers[lowestIndex] = &sticker;
        xCoords[lowestIndex] = x;
        yCoords[lowestIndex] = y;
    }
    return lowestIndex;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if (index < (maxStickers) && (stickers[index]) != NULL) {
        xCoords[index] = x;
        yCoords[index] = y;
        return true;
    }
    return false;
}

void StickerSheet::removeSticker(unsigned index) {
    for (unsigned i = index; i < (maxStickers) - 1; i++) {
        stickers[i] = stickers[i + 1];
        xCoords[i] = xCoords[i + 1];
        yCoords[i] = yCoords[i + 1];
    }
    stickers[(maxStickers) - 1] = NULL;
    xCoords[(maxStickers) - 1] = 0;
    yCoords[(maxStickers) - 1] = 0;
}

Image * StickerSheet::getSticker(unsigned index) {
    Image * sticker = stickers[index];
    return (sticker);
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

    for (unsigned index = 0; index < (maxStickers); index++) {

        if (stickers[index] == NULL) {
            break;
        }

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

int StickerSheet::lowestStickerLayer() {
    for (unsigned i = 0; i < (maxStickers); i++) {
        if (stickers[i] == NULL) {
            return i;
        }
    }
    return -1;
}

void StickerSheet::copy(const StickerSheet & other) {
    maxStickers = other.maxStickers;
    background = new Image(*other.background);
    stickers = new Image*[(maxStickers)];
    xCoords = new unsigned int [(maxStickers)];
    yCoords = new unsigned int [(maxStickers)];

    for (unsigned i = 0; i < (maxStickers); i++) {
        if (other.stickers[i] != NULL) {
            stickers[i] = new Image();
            (*stickers[i]) = (*other.stickers[i]);
        } else {
            stickers[i] = NULL;
        }
        xCoords[i] = other.xCoords[i];
        yCoords[i] = other.yCoords[i];
    }
}