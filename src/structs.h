/*
 * sctucts.h
 *
 *  Created on: Oct 21, 2025
 *      Author: cyberdemon
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_


struct Point {
    double x, y;
};

struct Circle {
    Point center;
    double radius;
};

struct Square {
    Point topLeft;
    double side;
};

#endif /* STRUCTS_H_ */
