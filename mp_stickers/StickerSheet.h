/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "Image.h"

class StickerSheet {
    private: 
        Image * background;
        unsigned maxStickers;
        unsigned numStickers;
        Image ** stickers;
        unsigned * xCoords;
        unsigned * yCoords;
    public:
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
        void clear();
        void copy(const StickerSheet & other);
};