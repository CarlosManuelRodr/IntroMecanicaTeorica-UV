#include <cmath>
#include <complex>
#include "BMPPlotter.h"
using namespace std;

Matrix<Color> DrawMandelbrot()
{
    int rows = 400;
    int columns = 600;
    Matrix<Color> mandelbrot(rows, columns);

    double minRe = -2.45296;
    double maxRe = 1.1624;
    double minIm = -1.169;
    double maxIm = minIm + (maxRe - minRe) * rows / columns;

    double reFactor = (maxRe - minRe) / (columns - 1);
    double imFactor = (maxIm - minIm) / (rows - 1);

    complex<double> z, c;
    unsigned n;
    unsigned int maxIter = 100;
    bool belongsToSet;

    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < columns; x++)
        {
            z = c = complex<double>(minRe + x * reFactor, maxIm - y * imFactor);

            belongsToSet = true;

            for (n = 0; n < maxIter; n++)
            {
                if (z.real() * z.real() + z.imag() * z.imag() > 4)
                {
                    belongsToSet = false;
                    break;
                }
                z = pow(z, 2) + c;
            }

            if (belongsToSet)
            {
                mandelbrot[y][x] = Color((char)0, (char)0, (char)0);
            }
            else
            {
                mandelbrot[y][x] = Color((char)255, (char)255, (char)255);
            }
        }
    }

    return mandelbrot;
}

int main()
{
    Matrix<Color> plotMatrix = DrawMandelbrot();
    Plot(plotMatrix, "mandelbrot.bmp");
}