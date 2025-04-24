//
// Created by Juan Pablo on 4/12/2025.
//

#ifndef P2_VECTOR_H
#define P2_VECTOR_H

typedef struct {
    float x,y,z;
} VEC3;

VEC3 VEC3_add(VEC3 a, VEC3 b);
VEC3 VEC3_sub(VEC3 a, VEC3 b);
float VEC3_dot(VEC3 a, VEC3 b);
VEC3 VEC3_cross(VEC3 a, VEC3 b);
VEC3 VEC3_normalize(VEC3 a);
VEC3 VEC3_scale(VEC3 a, float b);
VEC3 VEC3_zero();
float VEC3_lenght(VEC3 a);
VEC3 VEC3_set(float x, float y, float z);
float VEC3_get_x(VEC3 a);
float VEC3_get_y(VEC3 a);
float VEC3_get_z(VEC3 a);
VEC3 VEC3_rotateX(VEC3 a, float b, VEC3 c);
VEC3 VEC3_rotateY(VEC3 a, float b, VEC3 c);
VEC3 VEC3_rotateZ(VEC3 a, float b, VEC3 c);
void VEC3_print(VEC3 a);

#endif //P2_VECTOR_H
