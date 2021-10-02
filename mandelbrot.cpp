#include<iostream>
#include<fstream>
#include<string>
#include<complex>
#include<cstdlib>
#include<cmath>

#include "config.h"

struct rgb
{
    float r;
    float g;
    float b;
};

struct hsv
{
    float h;
    float s;
    float v;
};

std::complex<long double> pixel_to_cplx(long double x, long double y, int xres, int yres, std::complex<long double> center, long double zoom)
{
    return std::complex<long double> (((x - 0) * (2 - -2) / (xres - 0) + -2), -((y - 0) * (2 - -2) / (yres - 0) + -2)) / zoom + center;
}

struct rgb hsv2rgb(struct hsv color)
{
    struct rgb out_color = {0, 0, 0};

    float chroma = color.v * color.s;
    float hue = color.h / 60.0f;
    float x = chroma * (1 - std::abs((int)hue % 2 - 1));

    switch ((int)std::floor(hue))
    {
    case 0:
        out_color = {chroma, x, 0};
        break;
    case 1:
        out_color = {x, chroma, 0};
        break;
    case 2:
        out_color = {0, chroma, x};
        break;
    case 3:
        out_color = {0, x, chroma};
        break;
    case 4:
        out_color = {x, 0, chroma};
        break;
    case 5:
        out_color = {chroma, 0, x};
        break;
    default:
        break;
    }

    float m = color.v - chroma;

    std::cout << out_color.r + m << std::endl;
    std::cout << out_color.g + m << std::endl;
    std::cout << out_color.b + m << std::endl;

    return {out_color.r + m, out_color.g + m, out_color.b + m};
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
    double color;
    static uint pixels[YRES][XRES][3]; // static pour pas overflow

    float saturation = 0.9f;
    float hue = 350.0f;

    for(int y = 0; y<YRES; ++y)
    {
        for(int x = 0; x<XRES; ++x)
        {
            c = pixel_to_cplx(x, y, XRES, YRES, center, ZOOM);
            color = (float)iterate(c, ITERATIONS) / (float)ITERATIONS;


            float value = color;
            std::cout << hue << std::endl;

            struct rgb pixel_color = hsv2rgb({hue, saturation, value});

            pixels[y][x][0] = pixel_color.r * 256;
            pixels[y][x][1] = pixel_color.g * 256;
            pixels[y][x][2] = pixel_color.b * 256;
        }
    }

    write_to_file("mandelbrot.ppm", pixels);

    return 0;
}
