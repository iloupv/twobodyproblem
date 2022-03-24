#include <stdio.h>      /* printf */
#include <math.h>       /* sqrt */
#include <iostream>     /* file write */
#include <fstream>
#include <cstring>
#include "two_body_problem.h"

using namespace std;

Model::Model(float qaux, float ecce)
{
    q = qaux;
    ec = ecce;
    
    time = 10;
    step = 0.1;

    mass1 = 1.0;
    mass2 = 1.0 * q;
    massTotal = mass1 + mass2;

    distance = 1.0; // not used

    memset(coords, 0.0, 4*sizeof(coords));

    u[0] = 1; u[1] = 0; u[2] = 0; u[3] = sqrt((1 + q) * (1 + ec));
}

float* Model::derivative()
{
    float* du = (float*) malloc(4*sizeof(float));
    float rr;

    rr = sqrt(pow(u[0],2) + pow(u[1],2));

    for(int i = 0; i < 2; i++)
    {
        du[i] = u[i + 2];
        du[i + 2] = -(1 + q) * u[i] / (pow(rr,3));
    }

    return du;

}

void Model::eulercalc()
{
    float* du = (float*) malloc(4*sizeof(float));

    for(int i = 0; i < (time / step); i++)
    {
        du = derivative();
        for(i=0; i < 4; i++)
        {
            u[i] = u[i] + step * du[i];
        }
    }

    updateCoord();
    writeToFile();
}

void Model::updateCoord()
{
    float a1 = (mass2 / massTotal) * distance;
    float a2 = (mass1 / massTotal) * distance;

    coords[0] = -a2 * u[0];
    coords[1] = -a2 * u[1];
    coords[2] = a1 * u[0];
    coords[3] = a1 * u[1];

}

void Model::writeToFile()
{
    ofstream MyFile("../output/output.txt");

    for(int i = 0; i < 4; i++)
    {
        MyFile << u[i] << '\t';
    }
    MyFile << '\n';

    MyFile.close();
}

int main(){
    float qaux = 0.0; float ecce = 0.0;
    cout << "Enter Mass Ratio (0-1): ";
    scanf("%f", &qaux);
    cout << "Enter the eccentricity of the planets: ";
    scanf("%f", &ecce);

    Model model(qaux, ecce);
    model.eulercalc();
    return 0;
}