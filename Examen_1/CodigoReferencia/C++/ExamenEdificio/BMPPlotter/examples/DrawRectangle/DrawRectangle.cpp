#include "BMPPlotter.h"

Matrix<Color> DrawRectangle()
{
    Matrix<Color> colors(400, 600);
    for (unsigned i = 0; i < colors.GetNumRows(); i++)
    {
        for (unsigned j = 0; j < colors.GetNumCols(); j++)
        {
            colors[i][j] = Color((char)255, (char)0, (char)0);
        }
    }
    return colors;
}

int main()
{
    Matrix<Color> plotMatrix = DrawRectangle();
    Plot(plotMatrix, "red.bmp");
}