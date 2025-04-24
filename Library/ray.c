//
// Created by Juan Pablo on 4/12/2025.
//

#include "ray.h"
#include <stdio.h>

#define SKY 1e+30

float Intersect(TRI tri, RAY ray) {
    /*printf("Normal: %.2f %.2f %.2f\n", tri.n.x, tri.n.y, tri.n.z);
    printf("P1: %.2f %.2f %.2f\n", tri.p1.x, tri.p1.y, tri.p1.z);
    printf("P2: %.2f %.2f %.2f\n", tri.p2.x, tri.p2.y, tri.p2.z);
    printf("P3: %.2f %.2f %.2f\n", tri.p3.x, tri.p3.y, tri.p3.z);
    printf("Ray: %.2f %.2f %.2f\n", ray.o.x, ray.o.y, ray.o.z);
    printf("Dir: %.2f %.2f %.2f\n", ray.d.x, ray.d.y, ray.d.z);*/
    VEC3 v0 = VEC3_sub(tri.p1, tri.p2);
    VEC3 v1 = VEC3_sub(tri.p1, tri.p3);
    tri.n = VEC3_normalize(VEC3_cross(v0, v1));
    /*printf("V0: %.2f %.2f %.2f\n", v0.x, v0.y, v0.z);
    printf("V1: %.2f %.2f %.2f\n", v1.x, v1.y, v1.z);*/
    float denom = VEC3_dot(ray.d, tri.n);
    //printf("Denom: %.2f\n", denom);
    float dst = -1 * VEC3_dot(VEC3_sub(ray.o, tri.p1), tri.n) / denom;
    //printf("Dst: %.2f\n", dst);

    VEC3 intersection = VEC3_add(ray.o, VEC3_scale(ray.d, dst));
    //printf("Intersection: %.2f\n", dst);

    VEC3 v2 = VEC3_sub(tri.p1, intersection);
    float d00 = VEC3_dot(v0, v0);
    float d01 = VEC3_dot(v0, v1);
    float d11 = VEC3_dot(v1, v1);
    float d20 = VEC3_dot(v2, v0);
    float d21 = VEC3_dot(v2, v1);
    float denomBary = d00 * d11 - d01 * d01;

    float v = (d11 * d20 - d01 * d21) / denomBary;
    float w = (d00 * d21 - d01 * d20) / denomBary;
    float u = 1.0f - v - w;
    //printf("u: %f, v: %f, w: %f\n", u, v, w);

    return (u >= 0.0f && v >= 0.0f && w >= 0.0f) ? dst : SKY;
}
float Shading(float dist, int index, VEC3 ray, VEC3 l_d, TRI tris[], int size){
    if (dist >= SKY)
        return 0.0f;
    l_d = VEC3_normalize(l_d);
    VEC3 v0 = VEC3_sub(tris[index].p1, tris[index].p2);
    VEC3 v1 = VEC3_sub(tris[index].p1, tris[index].p3);
    tris[index].n = VEC3_normalize(VEC3_cross(v1, v0));
        float diffuse = VEC3_dot(tris[index].n, l_d);
        diffuse = (diffuse < 0.0) ? -diffuse : diffuse;
        return diffuse;

}

VEC3 RAY_Point(RAY ray, float t){
    return VEC3_add(ray.o, VEC3_scale(ray.d, t));
}
/*
float ShadingTriangle(float dst, int closest_triangle_idx, RAY ray, TRI triangle, VEC3 lights[], int num_lights, TRI triangles[], int num_triangles) {
    if (dst >= SKY)
        return 0.0f;
    VEC3 intersection = VEC3_add(ray.o, VEC3_scale(ray.d, dst));
    VEC3 normal = VEC3_cross(VEC3_sub(triangle.p1, triangle.p2), VEC3_sub(triangle.p1, triangle.p3));
    float total_diffuse = 0.0;

    for (int l = 0; l < num_lights; l++) {
        float diffuse = VEC3_dot(normal, lights[l]);
        diffuse = (diffuse < 0.0) ? -diffuse : diffuse;
        return diffuse;
        RAY shadow_ray = { intersection, VEC3_set(-lights[l].x, -lights[l].y, -lights[l].z) };

        for (int i = 0; i < num_triangles; i++) {
            if (i != closest_triangle_idx && IntersectionTriangle(shadow_ray, triangles[i]) < SKY) {
                diffuse = 0.0;
                break;
            }
        }
        total_diffuse += diffuse;
    }
    return total_diffuse / num_lights;
}



float IntersectionTriangle(RAY ray, TRI tri) {
    VEC3 v0 = VEC3_sub(tri.p1, tri.p2);
    VEC3 v1 = VEC3_sub(tri.p1, tri.p3);
    float denom = VEC3_dot(ray.d, normal);
    float dst = -1 * VEC3_dot(VEC3_sub(ray.o, tri.p1), normal) / denom;

    VEC3 intersection = VEC3_add(ray.o, VEC3_scale(ray.d, dst));

    VEC3 v2 = VEC3_sub(tri.p1, intersection);
    float d00 = VEC3_dot(v0, v0);
    float d01 = VEC3_dot(v0, v1);
    float d11 = VEC3_dot(v1, v1);
    float d20 = VEC3_dot(v2, v0);
    float d21 = VEC3_dot(v2, v1);
    float denomBary = d00 * d11 - d01 * d01;

    float v = (d11 * d20 - d01 * d21) / denomBary;
    float w = (d00 * d21 - d01 * d20) / denomBary;
    float u = 1.0f - v - w;

    return (u >= 0.0f && v >= 0.0f && w >= 0.0f) ? dst : SKY;
}*/