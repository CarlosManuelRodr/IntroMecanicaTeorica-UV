BMPPlotter
=========

Header-only C++ library for basic plotting and drawing. The resulting plot is shown in a BMP file.

This library is designed to be as minimal and simple as possible. Just include it in your project or add it to its include path.

# Examples
![Mandelbrot set](https://github.com/CarlosManuelRodr/BMPPlotter/blob/main/images/mandelbrot.bmp?raw=true)

![Sine plot](https://github.com/CarlosManuelRodr/BMPPlotter/blob/main/images/plot.bmp?raw=true)

# Usage

## Basic plotting

For basic usage you only need to include the library,

    #include "BMPPlotter.h"

define a vector of doubles,

    std::vector<double> data

and fill it with the data you wish to plot. Then you can create the plot with

    Plot(data, "plot.bmp");

## xy plotting
If you instead wish to plot pairs of values (x,y) you can create a vector of 2D coordinates,

	std::vector<Vector2> data;

fill it with values, and then plot it with

    Plot(data, "plot.bmp");

## Matrix plotting
You can use a Matrix as a canvas to draw things and then plot it. To do so first create a matrix object,

    Matrix<Color> canvas(rows, columns);

and plot it with

    Plot(canvas, "canvas.bmp");

Color is a struct with rgb values that can be instantiated directly:

    canvas[y][x] = Color((char)90, (char)128, (char)255);