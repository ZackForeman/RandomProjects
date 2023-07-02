#include <iostream>
#include <fstream>
#include "SVG.h"

using namespace std;

int main(){
    ofstream newSvg ("example.svg");

    SVG* img = new SVG(500,500);

    Point p1(0,0);
    Point p2(250, 250);
    Point p3(250, 100);

    img->addLine(p1,p2, "red", 4);
    img->addLine(p2,p3, "blue", 8);

    newSvg << img->getOutputString();

    newSvg.close();
}