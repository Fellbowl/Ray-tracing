//
// Created by Juan Pablo on 4/12/2025.
//

#include "vector.h"
#include <math.h>

VEC3 VEC3_add(VEC3 a, VEC3 b){
    return (VEC3) {a.x + b.x, a.y + b.y, a.z + b.z};
}
VEC3 VEC3_sub(VEC3 a, VEC3 b){
    return (VEC3) {a.x - b.x, a.y - b.y, a.z - b.z};
}
float VEC3_dot(VEC3 a, VEC3 b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
VEC3 VEC3_cross(VEC3 a, VEC3 b){
    return (VEC3) {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}
VEC3 VEC3_normalize(VEC3 a){
    float lenght = VEC3_lenght(a);
    return VEC3_scale(a, 1/lenght);
}
VEC3 VEC3_scale(VEC3 a, float b){
    return (VEC3) {a.x * b, a.y * b, a.z * b};
}
VEC3 VEC3_zero(){
    return (VEC3) {0, 0, 0};
}
float VEC3_lenght(VEC3 a){
    return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
}
VEC3 VEC3_set(float x, float y, float z){
    return (VEC3) {x, y, z};
}
VEC3 VEC3_rotateX(VEC3 a, float b, VEC3 c) {
    // Paso 1: trasladar al origen
    float tx = a.x - c.x;
    float ty = a.y - c.y;
    float tz = a.z - c.z;

    // Paso 2: rotación alrededor del eje X
    float cosb = cosf(b);
    float sinb = sinf(b);
    float ry = ty * cosb - tz * sinb;
    float rz = ty * sinb + tz * cosb;
    float rx = tx; // X no cambia en rotación sobre eje X

    // Paso 3: trasladar de vuelta
    VEC3 result;
    result.x = rx + c.x;
    result.y = ry + c.y;
    result.z = rz + c.z;

    return result;
}


VEC3 VEC3_rotateY(VEC3 a, float b, VEC3 c) {
    // Paso 1: trasladar 'a' al origen con respecto a 'c'
    float tx = a.x - c.x;
    float ty = a.y - c.y;
    float tz = a.z - c.z;

    // Paso 2: rotar alrededor del eje Y
    float cosb = cosf(b);
    float sinb = sinf(b);
    float rx = tx * cosb + tz * sinb;
    float rz = -tx * sinb + tz * cosb;
    float ry = ty; // Y no cambia en rotación alrededor de Y

    // Paso 3: re-trasladar al punto original
    VEC3 result;
    result.x = rx + c.x;
    result.y = ry + c.y;
    result.z = rz + c.z;

    return result;
}

VEC3 VEC3_rotateZ(VEC3 a, float b, VEC3 c) {
    // Paso 1: trasladar al origen
    float tx = a.x - c.x;
    float ty = a.y - c.y;
    float tz = a.z - c.z;

    // Paso 2: rotación alrededor del eje Z
    float cosb = cosf(b);
    float sinb = sinf(b);
    float rx = tx * cosb - ty * sinb;
    float ry = tx * sinb + ty * cosb;
    float rz = tz; // Z no cambia en rotación sobre eje Z

    // Paso 3: trasladar de vuelta
    VEC3 result;
    result.x = rx + c.x;
    result.y = ry + c.y;
    result.z = rz + c.z;

    return result;
}
