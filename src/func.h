/*
 * func.h
 *
 *  Created on: Oct 21, 2025
 *      Author: cyberdemon
 */

#ifndef FUNC_H_
#define FUNC_H_

#include "structs.h"

// Точка
void readPoint(Point& p);
void printPoint(const Point& p);

// Круг
void readCircle(Circle& c);
void printCircle(const Circle& c);
double circlePerimeter(const Circle& c);
double circleArea(const Circle& c);

// Квадрат
void readSquare(Square& s);
void printSquare(const Square& s);
double squarePerimeter(const Square& s);
double squareArea(const Square& s);

// Принадлежность точки фигуре
bool isPointInCircle(const Point& p, const Circle& c);
bool isPointInSquare(const Point& p, const Square& s);

// Нахождение точки на контуре
bool isPointOnCircle(const Point& p, const Circle& c);
bool isPointOnSquare(const Point& p, const Square& s);

// Пересечение фигур
bool circlesIntersect(const Circle& c1, const Circle& c2);
bool squaresIntersect(const Square& s1, const Square& s2);
bool circleSquareIntersect(const Circle& c, const Square& s);

// Принадлежность фигур
bool isCircleInCircle(const Circle& c1, const Circle& c2);
bool isSquareInSquare(const Square& s1, const Square& s2);
bool isSquareInCircle(const Square& s, const Circle& c);
bool isCircleInSquare(const Circle& c, const Square& s);


#endif /* FUNC_H_ */
