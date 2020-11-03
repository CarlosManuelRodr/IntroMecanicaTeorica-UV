#include <cmath>
#include "BMPPlotter.h"
using namespace std;

int main()
{
    vector<Vector2> data;
    for (double i = 0; i < 6.28; i += 0.01)
    {
        data.push_back(Vector2(i, sin(i)));
    }

    Plot(data, "plot.bmp");
    return 0;
}
