//
// Created by Juan Pablo on 4/12/2025.
//

#ifndef P2_RAY_H
#define P2_RAY_H

#include "vector.h"

typedef struct {
    VEC3 o,d;
} RAY;

typedef struct {
    VEC3 n,p1,p2,p3;
} TRI;

float Intersect(TRI t, RAY r);

float Shading(float a, int b, VEC3 c, VEC3 d, TRI e[], int f);

VEC3 RAY_Point(RAY a, float b);
/*
float IntersectionTriangle(RAY ray, TRI tri);
float ShadingTriangle(float a, int b, RAY c, TRI d, VEC3 e[], int f, TRI g[], int h);
*/

#endif //P2_RAY_H
