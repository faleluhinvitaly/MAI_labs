/*
 * func.cpp
 *
 *  Created on: Oct 21, 2025
 *      Author: cyberdemon
 */

#include "func.h"
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

const double EPS = 1e-5;

void readPoint(Point& p) {
    cin >> p.x >> p.y;
}

void printPoint(const Point& p) {
    cout << "(" << p.x << ", " << p.y << ")";
}

void readCircle(Circle& c) {
    readPoint(c.center);
    cin >> c.radius;
}

void printCircle(const Circle& c) {
    cout << "Center: ";
    printPoint(c.center);
    cout << ", Radius: " << c.radius;
}

double circlePerimeter(const Circle& c) {
    return 2 * M_PI * c.radius;
}

double circleArea(const Circle& c) {
    return M_PI * c.radius * c.radius;
}

void readSquare(Square& s) {
    readPoint(s.topLeft);
    cin >> s.side;
}

void printSquare(const Square& s) {
    cout << "Top-Left: ";
    printPoint(s.topLeft);
    cout << ", Side: " << s.side;
}

double squarePerimeter(const Square& s) {
    return 4 * s.side;
}

double squareArea(const Square& s) {
    return s.side * s.side;
}

bool isPointInCircle(const Point& p, const Circle& c) {
    double dx = p.x - c.center.x;
    double dy = p.y - c.center.y;
    return (dx*dx + dy*dy) < (c.radius*c.radius - EPS);
}

bool isPointInSquare(const Point& p, const Square& s) {
    return (p.x > s.topLeft.x + EPS) &&
           (p.x < s.topLeft.x + s.side - EPS) &&
           (p.y < s.topLeft.y - EPS) &&
           (p.y > s.topLeft.y - s.side + EPS);
}

bool isPointOnCircle(const Point& p, const Circle& c) {
    double dx = p.x - c.center.x;
    double dy = p.y - c.center.y;
    double dist = dx*dx + dy*dy;
    return fabs(dist - c.radius*c.radius) < EPS;
}

bool isPointOnSquare(const Point& p, const Square& s) {
    bool onVertical = (fabs(p.x - s.topLeft.x) < EPS || 
                      fabs(p.x - s.topLeft.x - s.side) < EPS) &&
                     (p.y <= s.topLeft.y + EPS) &&
                     (p.y >= s.topLeft.y - s.side - EPS);
    
    bool onHorizontal = (fabs(p.y - s.topLeft.y) < EPS || 
                        fabs(p.y - s.topLeft.y + s.side) < EPS) &&
                       (p.x >= s.topLeft.x - EPS) &&
                       (p.x <= s.topLeft.x + s.side + EPS);
    
    return onVertical || onHorizontal;
}

bool circlesIntersect(const Circle& c1, const Circle& c2) {
    double dx = c1.center.x - c2.center.x;
    double dy = c1.center.y - c2.center.y;
    double distance = sqrt(dx*dx + dy*dy);
    return distance < (c1.radius + c2.radius + EPS) && 
           distance > fabs(c1.radius - c2.radius) - EPS;
}

bool squaresIntersect(const Square& s1, const Square& s2) {
    bool xOverlap = s1.topLeft.x < s2.topLeft.x + s2.side + EPS &&
                    s2.topLeft.x < s1.topLeft.x + s1.side + EPS;
    
    bool yOverlap = s1.topLeft.y > s2.topLeft.y - s2.side - EPS &&
                    s2.topLeft.y > s1.topLeft.y - s1.side - EPS;
    
    return xOverlap && yOverlap;
}

bool circleSquareIntersect(const Circle& c, const Square& s) {
    // Проверка пересечения с контуром квадрата
    Point edges[4][2] = {
        {s.topLeft, {s.topLeft.x + s.side, s.topLeft.y}},
        {{s.topLeft.x + s.side, s.topLeft.y}, {s.topLeft.x + s.side, s.topLeft.y - s.side}},
        {{s.topLeft.x, s.topLeft.y - s.side}, {s.topLeft.x + s.side, s.topLeft.y - s.side}},
        {{s.topLeft.x, s.topLeft.y}, {s.topLeft.x, s.topLeft.y - s.side}}
    };

    for (auto& edge : edges) {
        double dx = edge[1].x - edge[0].x;
        double dy = edge[1].y - edge[0].y;
        double t = ((c.center.x - edge[0].x)*dx + (c.center.y - edge[0].y)*dy) / (dx*dx + dy*dy);
        t = max(0.0, min(1.0, t));
        double closestX = edge[0].x + t*dx;
        double closestY = edge[0].y + t*dy;
        double distance = hypot(c.center.x - closestX, c.center.y - closestY);
        if (distance <= c.radius + EPS) return true;
    }
    return false;
}

bool isCircleInCircle(const Circle& c1, const Circle& c2) {
    double dx = c1.center.x - c2.center.x;
    double dy = c1.center.y - c2.center.y;
    double distance = sqrt(dx*dx + dy*dy);
    return distance + c1.radius < c2.radius + EPS;
}

bool isSquareInSquare(const Square& s1, const Square& s2) {
    return s1.topLeft.x >= s2.topLeft.x - EPS &&
           s1.topLeft.x + s1.side <= s2.topLeft.x + s2.side + EPS &&
           s1.topLeft.y <= s2.topLeft.y + EPS &&
           s1.topLeft.y - s1.side >= s2.topLeft.y - s2.side - EPS;
}

bool isSquareInCircle(const Square& s, const Circle& c) {
    Point vertices[4] = {
        s.topLeft,
        {s.topLeft.x + s.side, s.topLeft.y},
        {s.topLeft.x, s.topLeft.y - s.side},
        {s.topLeft.x + s.side, s.topLeft.y - s.side}
    };
    
    for (const Point& v : vertices) {
        double dx = v.x - c.center.x;
        double dy = v.y - c.center.y;
        if (dx*dx + dy*dy > c.radius*c.radius - EPS) return false;
    }
    return true;
}

bool isCircleInSquare(const Circle& c, const Square& s) {
    return (c.center.x - c.radius >= s.topLeft.x - EPS) &&
           (c.center.x + c.radius <= s.topLeft.x + s.side + EPS) &&
           (c.center.y + c.radius <= s.topLeft.y + EPS) &&
           (c.center.y - c.radius >= s.topLeft.y - s.side - EPS);
}


