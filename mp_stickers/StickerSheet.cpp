#include "StickerSheet.h"
#include "Image.h"
#include "cs225/HSLAPixel.h"

using cs225::HSLAPixel;

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    background = new Image(picture);
    maxStickers = new unsigned int;
    maxStickers = (&max);
    stickers = new Image*[(*maxStickers)];
    xCoords = new unsigned*[(*maxStickers)];
    yCoords = new unsigned*[(*maxStickers)];

    for (unsigned i = 0; i < (*maxStickers); i++) {
        stickers[i] = NULL;
        xCoords[i] = NULL;
        yCoords[i] = NULL;
    }
}

StickerSheet::~StickerSheet() {
    delete background;
    delete maxStickers;
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
    maxStickers = &max;

    Image ** newStickers = new Image*[(*maxStickers)];
    unsigned ** newXCoords = new unsigned*[(*maxStickers)];
    unsigned ** newYCoords = new unsigned*[(*maxStickers)];

    for (unsigned i = 0; i < (*maxStickers); i++) {
        newStickers[i] = stickers[i];
        newXCoords[i] = xCoords[i];
        newYCoords[i] = yCoords[i];
    }
    delete[] stickers;
    delete[] xCoords;
    delete[] yCoords;
    stickers = newStickers;
    xCoords = newXCoords;
    yCoords = newYCoords;
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
    if (lowestStickerLayer() != -1) {
        stickers[lowestStickerLayer()] = &sticker;
        xCoords[lowestStickerLayer()] = &x;
        yCoords[lowestStickerLayer()] = &y;
    }
    return lowestStickerLayer();
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if (index < (*maxStickers) && (stickers[index]) != NULL) {
        xCoords[index] = &x;
        yCoords[index] = &y;
        return true;
    }
    return false;
}

void StickerSheet::removeSticker(unsigned index) {
    for (unsigned i = index; i < (*maxStickers); i++) {
        stickers[i] = stickers[i + 1];
        xCoords[i] = xCoords[i + 1];
        yCoords[i] = yCoords[i + 1];
    }
    stickers[(*maxStickers)] = NULL;
    xCoords[(*maxStickers)] = NULL;
    yCoords[(*maxStickers)] = NULL;
}

Image * StickerSheet::getSticker(unsigned index) {
    Image * sticker = stickers[index];
    return (sticker);
}

Image StickerSheet::render() const {
    for (unsigned i = 0; i < (*maxStickers); i++) {
        drawSticker(i);
    }
    return (*background);
}

void StickerSheet::drawSticker(unsigned index) const {
    if (stickers[index] == NULL) {
        return;
    }

    Image * sticker = stickers[index];
    unsigned x = (*xCoords[index]);
    unsigned y = (*yCoords[index]);

    for (unsigned i = 0; i < (*sticker).width(); i++) {
        for (unsigned j = 0; j < (*sticker).height(); j++) {
            if ((*sticker).width() + i < background->width() && (*sticker).height() + j < background->height()) {
                HSLAPixel & currPixel = background->getPixel(x + i, y + j);
                HSLAPixel & newPixel = (*sticker).getPixel(i, j);
                currPixel = newPixel;
            }
        }
    }
}

int StickerSheet::lowestStickerLayer() {
    for (unsigned i = 0; i < (*maxStickers); i++) {
        if (stickers[i] != NULL) {
            return i;
        }
    }
    return -1;
}

void StickerSheet::copy(const StickerSheet & other) {
    background = other.background;
    maxStickers = other.maxStickers;
    stickers = other.stickers;
    xCoords = other.xCoords;
    yCoords = other.yCoords;

    for (unsigned i = 0; i < (*maxStickers); i++) {
        stickers[i] = other.stickers[i];
        xCoords[i] = other.xCoords[i];
        yCoords[i] = other.yCoords[i];
    }
}