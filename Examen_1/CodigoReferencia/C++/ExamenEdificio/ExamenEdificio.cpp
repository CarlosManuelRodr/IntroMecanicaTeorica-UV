#include <iostream>
#include <vector>
#include <cmath>
#include "BMPPlotter/include/BMPPlotter.h"
using namespace std;

// Parámetros
double g = 9.81;
double m = 1.0;
double k = 18.0;
double h = 1.0;
double l = 2.0;
double pi = 3.141593;

// Estructura que contiene las listas de valores t, theta1 y theta2.
struct Solution
{
    double eventTime;
    vector<double> t;
    vector<double> theta1;
    vector<double> theta2;
};

// Solucionador por medio del método de Euler
Solution euler_solve(double A, double omega, double deltaT, double tMax)
{
    // Valores iniciales.
    double theta1 = 0.0;
    double theta2 = 0.0;
    double theta1Prime = 0.0;
    double theta2Prime = 0.0;
    double theta1BiPrime = 0.0;
    double theta2BiPrime = 0.0;

    // Guarda el primer punto.
    Solution output;
    output.t.push_back(0.0);
    output.theta1.push_back(theta1);
    output.theta2.push_back(theta2);

    // Resuelve numéricamente hasta t = tMax.
    for (double t = 0.0; t <= tMax; t += deltaT)
    {
        // Método de Euler.
        theta1BiPrime = -(k * theta1 + h * m * (2 * A * pow(omega, 2.0) * cos(theta1) * sin(t * omega)
            - 2 * g * sin(theta1) + h * sin(theta1 - theta2) * pow(theta2, 2.0) +
            h * cos(theta1 - theta2) * theta2BiPrime)) / (2 * pow(h, 2.0) * m);

        theta2BiPrime = (-k * theta2 + h * m * (-A * pow(omega, 2.0) * cos(theta2) * sin(t * omega) + g * sin(theta2)
            + h * sin(theta1 - theta2) * pow(theta1Prime, 2.0) - h * cos(theta1 - theta2) * theta1BiPrime))
            / (pow(h, 2.0) * m);

        theta1Prime += theta1BiPrime * deltaT;
        theta2Prime += theta2BiPrime * deltaT;
        theta1 += theta1Prime * deltaT;
        theta2 += theta2Prime * deltaT;

        // Guarda los nuevos valores.
        output.t.push_back(t);
        output.theta1.push_back(theta1);
        output.theta2.push_back(theta2);

        // Si ocurre el evento, guarda el tiempo y sale de la función.
        if ((abs(theta1) > pi / 2.0) || (abs(theta2) > pi / 2.0))
        {
            output.eventTime = t;
            return output;
        }
    }

    // Si no ocurrió el evento, se asigna eventTime = tMax.
    output.eventTime = tMax;
    return output;
}

int main()
{
    // Gráficas de theta1 y theta2.
    cout << "Plotting solution for theta1 and theta2..." << endl;
    Solution sol = euler_solve(0.5, 1.0, 0.01, 10.0);
    Plot(sol.theta1, "theta1.bmp");
    Plot(sol.theta2, "theta2.bmp");
    cout << "Done" << endl;

    // Mapa de estabilidad A vs omega.
    cout << "Plotting stability map..." << endl;
    double AMin = 0.1, AMax = 3.0;
    double omegaMin = 0.1, omegaMax = 4.0;
    double tMax = 10.0;
    double delta = 0.01;
    int horizontalRows = (int) floor((AMax - AMin) / delta);
    int verticalRows = (int) floor((omegaMax - omegaMin) / delta);

    // Crea matriz de canvas. Aquí se dibuja la imagen.
    Matrix<Color> canvas(verticalRows + 1, horizontalRows + 1);
    int i = 0;
    int j = 0;

    // Llena la matriz con un color que depende del tiempo de evento.
    for (double A = AMin; A < AMax; A += delta)
    {
        j = 0;
        for (double omega = omegaMin; omega < omegaMax; omega += delta)
        {
            Solution sol = euler_solve(A, omega, 0.01, tMax);
            canvas[j][i] = Color((char)0.0, (char) (255*(sol.eventTime/ tMax)), (char)0.0);
            j++;
        }
        i++;
    }
    Plot(canvas, "AvsOmega.bmp");
    cout << "Done" << endl;

    return 0;
}