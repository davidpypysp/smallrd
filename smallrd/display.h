#pragma once
#include <math.h>
#include <iostream>
#include "include.h"



struct Vector {
    double x, y, z;                  // position, also color (r,g,b) 

	Vector(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
    Vector operator+(const Vector &b) const { return Vector(x + b.x, y + b.y, z + b.z); }
    Vector operator-(const Vector &b) const { return Vector(x - b.x, y - b.y, z - b.z); }
    Vector operator*(double b) const { return Vector(x*b, y*b, z*b); }
    Vector mult(const Vector &b) const { return Vector(x*b.x, y*b.y, z*b.z); }
    Vector& norm() { return *this = *this * (1 / sqrt(x*x + y*y + z*z)); }
    double dot(const Vector &b) const { return x*b.x + y*b.y + z*b.z; } // cross: 
    Vector operator%(Vector&b) { return Vector(y*b.z - z*b.y, z*b.x - x*b.z, x*b.y - y*b.x); }
};


struct Pixel {
    double r, g, b, a;
    int z;
    Pixel(double r_ = 0, double g_ = 0, double b_ = 0, double a_ = 0, int z_ = 0) { r = r_; g = g_; b = b_; a = a_; z = z_; }
};

struct Display {
    int xres, yres;
    Pixel *fbuf;

    Display(int xres_ = 0, int yres_ = 0) { 
        xres = CLAMP(xres_, 0, MAXXRES); yres = CLAMP(yres_, 0, MAXYRES);
        fbuf = new Pixel[yres * xres];
    }
        
    void init() { 
        memset(fbuf, 0, sizeof(Pixel) * yres * xres); 
    }

    void setPixel(int x, int y, Pixel pixel) {
        if (INBOUND(x, 0, xres) && INBOUND(y, 0, yres)) fbuf[ARRAY(x, y, xres)] = pixel;
    }

    Pixel getPixel(int x, int y) {
        if (INBOUND(x, 0, xres) && INBOUND(y, 0, yres)) return fbuf[ARRAY(x, y, xres)];
        return Pixel(0, 0, 0, 0, 0);
    }

    void flush2File(FILE* outfile) {
        fprintf(outfile, "P6 %d %d 255\r", xres, yres);
        for (int i = 0; i < xres * yres; i++) {
            Pixel pixel = fbuf[i];
            short r = (int)pixel.r >> 4, g = (int)pixel.g >> 4, b = (int)pixel.b >> 4;
            fprintf(outfile, "%c%c%c", r, g, b);
        }
    }


};
