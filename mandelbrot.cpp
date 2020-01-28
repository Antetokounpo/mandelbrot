#include<iostream>
#include<fstream>
#include<string>
#include<complex>
#include<SDL2/SDL.h>

#include "config.h"

std::complex<long double> pixel_to_cplx(long double x, long double y, int xres, int yres, std::complex<long double> center, long double zoom)
{
    return std::complex<long double> (((x - 0) * (2 - -2) / (xres - 0) + -2), -((y - 0) * (2 - -2) / (yres - 0) + -2)) / zoom + center;
}

unsigned int iterate(std::complex<long double> c, unsigned int iterations)
{
    std::complex<long double> z = 0;

    for(unsigned int i = 0; i<iterations; ++i)
    {
        z = function(z, c);

        if(std::abs(z) > 2)
            return i+1; // Nombre d'itérations avant de tendre vers l'infini
    }
    return 0; // Valeur bool = false
}

void write_to_file(std::string filename, uint pixels[XRES][YRES][3])
{
    std::ofstream fout;
    fout.open(filename, std::ios::out);

    fout << "P3\n";
    fout << std::to_string(XRES) + " " + std::to_string(YRES) << std::endl;
    fout << 255 << std::endl;

    for(uint y = 0; y<YRES; ++y)
    {
        for(uint x = 0; x<XRES; ++x)
        {
            fout << std::to_string(pixels[y][x][2]) << " ";
            fout << std::to_string(pixels[y][x][1]) << " ";
            fout << std::to_string(pixels[y][x][0]) << " ";
        }
        fout << "\n";
    }
    fout.close();
}

int main()
{
    std::complex<long double> center(RCENTER, ICENTER);
    std::complex<long double> c;
    uint color;
    static uint pixels[YRES][XRES][3]; // static pour pas overflow

    for(int y = 0; y<YRES; ++y)
    {
        for(int x = 0; x<XRES; ++x)
        {
            c = pixel_to_cplx(x, y, XRES, YRES, center, ZOOM);
            color = (float)iterate(c, ITERATIONS) / (float)ITERATIONS * 0xFFFFFF;

            pixels[y][x][0] = color & 0xFF;
            pixels[y][x][1] = color >> 8 & 0xFF;
            pixels[y][x][2] = color >> 16 & 0xFF;
        }
    }

    write_to_file("mandelbrot.ppm", pixels);

    return 0;
}
