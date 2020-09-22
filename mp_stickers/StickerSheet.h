/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "Image.h"

class StickerSheet {
    public:
        Image * background;
        unsigned * maxStickers;
        Image ** stickers;
        unsigned ** xCoords;
        unsigned ** yCoords;

        StickerSheet(const Image &picture, unsigned max);
        ~StickerSheet();
        StickerSheet(const StickerSheet &other);
        const StickerSheet& operator= (const StickerSheet &other);
        void changeMaxStickers(unsigned max);
        int addSticker (Image &sticker, unsigned x, unsigned y);
        bool translate(unsigned index, unsigned x, unsigned y);
        void removeSticker(unsigned index);
        Image * getSticker(unsigned index);
        Image render() const;

        //making this helper function
        void drawSticker(unsigned index) const;
        int lowestStickerLayer();
        void copy(const StickerSheet & other);
};