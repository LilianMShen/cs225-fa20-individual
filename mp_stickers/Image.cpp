#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using cs225::PNG;
using cs225::HSLAPixel;

void Image::lighten() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x,y);

            if (pixel.l <= .9) {
                pixel.l += .1;
            } else {
                pixel.l = 1;
            }
        }
    }
}

void Image::lighten(double amount) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x,y);

            if (pixel.l <=  1 - amount) {
                pixel.l += amount;
            } else {
                pixel.l = 1;
            }
        }
    }
}

void Image::darken() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x,y);

            if (pixel.l >= .1) {
                pixel.l -= .1;
            } else {
                pixel.l = 0;
            }
        }
    }
}

void Image::darken(double amount) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x,y);

            if (pixel.l >= amount) {
                pixel.l -= amount;
            } else {
                pixel.l = 0;
            }
        }
    }
}

void Image::saturate() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x,y);

            if (pixel.s <= .9) {
                pixel.s += .1;
            } else {
                pixel.s = 1;
            }
        }
    }
}

void Image::saturate(double amount) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x,y);

            if (pixel.s <=  1 - amount) {
                pixel.s += amount;
            } else {
                pixel.s = 1;
            }
        }
    }
}

void Image::desaturate() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x,y);

            if (pixel.s >= .1) {
                pixel.s -= .1;
            } else {
                pixel.s = 0;
            }
        }
    }
}

void Image::desaturate(double amount) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x,y);

            if (pixel.s >= amount) {
                pixel.s -= amount;
            } else {
                pixel.s = 0;
            }
        }
    }
}

void Image::grayscale(){
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x,y);

            pixel.s = 0;
        }
    }
}

void Image::rotateColor(double degrees) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x,y);

            if (pixel.h + degrees <= 360) {
                pixel.h += degrees;
            } else {
                pixel.h = ((pixel.h + degrees) - 360);
                
            }

            if (pixel.h < 0) {
                pixel.h += 360;
            }
        }
    }
}

void Image::illinify() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x,y);

            if (pixel.h >= 113.5 && pixel.h <= 293.5) {
                pixel.h = 216.0;
            } else {
                pixel.h = 11;
            }
        }
    }
}

void Image::scale(double factor) {
    PNG * original = new PNG(*this);
    
    resize(width() * factor, height() * factor);
    
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & currPixel = getPixel(x,y);
            HSLAPixel & oldPixel = (*original).getPixel(x / factor, y / factor);
            currPixel = oldPixel;
        }
    }

    delete original;
}

void Image::scale(unsigned w, unsigned h) {
    PNG * original = new PNG(*this);

    unsigned xFactor = w / width();
    unsigned yFactor = h / height();

    resize(w, h);
    
    
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & currPixel = getPixel(x,y);
            HSLAPixel & oldPixel = (*original).getPixel(x / xFactor, y / yFactor);
            currPixel = oldPixel;
        }
    }

    delete original;
}