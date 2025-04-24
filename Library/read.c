//
// Created by Juan Pablo on 4/12/2025.
//

#include "read.h"
#include "ray.h"
#include <stdlib.h>
#include <stdio.h>

TRI* ReadTriangles(const char* name, int *size){
    FILE* archivo = fopen(name, "rb");
    if (!archivo) {
        perror("No se pudo abrir el archivo STL");
        EXIT_FAILURE;
    }
    fseek(archivo, 80, SEEK_SET);
    fread(size, sizeof(unsigned int), 1, archivo);
    TRI* triangles = (TRI*)malloc(*size * sizeof(TRI));
    if (!triangles) {
        perror("Error al asignar memoria para triangles");
        fclose(archivo);
        *size = 0;
        EXIT_FAILURE;
    }
    for (unsigned int i = 0; i < *size; ++i) {
        float aux[3] = {0,0,0};
        //printf("Leyendo triangulo %d\n",i);
        fread(aux, sizeof(float), 3, archivo);
        triangles[i].n.x = aux[0];
        triangles[i].n.y = aux[1];
        triangles[i].n.z = aux[2];
        //printf("Normal: %.2f %.2f %.2f\n", triangles[i].n.x, triangles[i].n.y, triangles[i].n.z);
        aux[0] = 0, aux[1] = 0, aux[2] = 0;
        fread(aux, sizeof(float), 3, archivo);
        triangles[i].p1.x=aux[0];
        triangles[i].p1.y=aux[1];
        triangles[i].p1.z=aux[2];
        //printf("Punto 1: %.2f %.2f %.2f\n", triangles[i].p1.x, triangles[i].p1.y, triangles[i].p1.z);
        aux[0] = 0, aux[1] = 0, aux[2] = 0;
        fread(aux, sizeof(float), 3, archivo);
        triangles[i].p2.x=aux[0];
        triangles[i].p2.y=aux[1];
        triangles[i].p2.z=aux[2];
        //printf("Punto 2: %.2f %.2f %.2f\n", triangles[i].p2.x, triangles[i].p2.y, triangles[i].p2.z);
        aux[0] = 0, aux[1] = 0, aux[2] = 0;
        fread(aux, sizeof(float), 3, archivo);
        triangles[i].p3.x=aux[0];
        triangles[i].p3.y=aux[1];
        triangles[i].p3.z=aux[2];
        //printf("Punto 3: %.2f %.2f %.2f\n", triangles[i].p3.x, triangles[i].p3.y, triangles[i].p3.z);
        aux[0] = 0, aux[1] = 0, aux[2] = 0;
        fseek(archivo, 2, SEEK_CUR); // Saltar atributo de 2 bytes
    }
    fclose(archivo);
    return triangles;
}
