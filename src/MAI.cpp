//============================================================================
// Name        : MAI.cpp
// Author      : Faleluhin Vitaly
// Version     :
// Copyright   : no copyright
// Description : 
//============================================================================

#include <iostream>
#include "func.h"
using namespace std;

int main() {
    Circle c1, c2;
    Square s1, s2;
    Point p;

    cout << "Demo:" << endl;

    cout << "Enter circle (x y r): ";
    readCircle(c1);
    cout << "Enter square (x y side): ";
    readSquare(s1);
    cout << "Enter point (x y): ";
    readPoint(p);

    cout << "\nCircle: ";
    printCircle(c1);
    cout << "\nPerimeter: " << circlePerimeter(c1) << endl;
    cout << "Area: " << circleArea(c1) << endl;

    cout << "\nSquare: ";
    printSquare(s1);
    cout << "\nPerimeter: " << squarePerimeter(s1) << endl;
    cout << "Area: " << squareArea(s1) << endl;

    cout << "\nPoint in circle: " << isPointInCircle(p, c1) << endl;
    cout << "Point on circle: " << isPointOnCircle(p, c1) << endl;
    cout << "Point in square: " << isPointInSquare(p, s1) << endl;
    cout << "Point on square: " << isPointOnSquare(p, s1) << endl;

    cout << "\nEnter second circle (x y r): ";
    readCircle(c2);
    cout << "Circles intersect: " << circlesIntersect(c1, c2) << endl;
    cout << "Circle in circle: " << isCircleInCircle(c1, c2) << endl;

    cout << "\nEnter second square (x y side): ";
    readSquare(s2);
    cout << "Squares intersect: " << squaresIntersect(s1, s2) << endl;
    cout << "Square in square: " << isSquareInSquare(s1, s2) << endl;

    cout << "Circle-square intersect: " << circleSquareIntersect(c1, s1) << endl;
    cout << "Square in circle: " << isSquareInCircle(s1, c1) << endl;
    cout << "Circle in square: " << isCircleInSquare(c1, s1) << endl;

    return 0;
}