#include<iostream>
#include<vector>
#include<complex>
#include<SDL2/SDL.h>

#include "config.h"

std::complex<double> pixel_to_cplx(double x, double y, int xres, int yres, std::complex<double> center, double zoom)
{
    return std::complex<double> ((x/xres*2 - (1 + center.real()))/zoom, (-y/yres*2 + (1 + center.imag()))/zoom);
}

uint iterate(std::complex<double> c, uint iterations)
{
    std::complex<double> z = (0, 0);

    for(uint i = 0; i<iterations; ++i)
    {
        z = std::pow(z, 2) + c;

        if(std::abs(z) > 2)
            return i+1; // Nombre d'itérations avant de tendre vers l'infini
    }
    return 0; // Valeur bool = false
}

int main()
{
    bool quit = false;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event e;
    std::complex<double> center(0.5, 0);
    std::complex<double> c;
    uint color;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }

    window = SDL_CreateWindow("Mandelbrot", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, XRES, YRES, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);

    while(!quit)
    {
        while(SDL_PollEvent(&e) > 0)
        {
            if(e.type == SDL_QUIT)
                quit = true;
        }

        for(int y = 0; y<YRES; ++y)
        {
            for(int x = 0; x<XRES; ++x)
            {
                c = pixel_to_cplx(x, y, XRES, YRES, center, ZOOM);
                color = (float)iterate(c, ITERATIONS) / (float)ITERATIONS * 0xFFFFFF;
                std::cout << color << std::endl;
                if(color)
                    SDL_SetRenderDrawColor(renderer, color & 0xFF0000, color & 0x00FF00, color &  0x0000FF, 255);
                else
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }

        SDL_RenderPresent(renderer);
    }

    SDL_Quit();
    return 0;
}
