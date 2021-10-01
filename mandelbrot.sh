#!/bin/bash
echo Compiling...
g++ mandelbrot.cpp -lSDL2 -O3 -o mandelbrot -Wall
echo Running...
time ./mandelbrot
echo Converting to png...
convert mandelbrot.ppm mandelbrot.png