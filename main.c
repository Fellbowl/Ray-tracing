#include <stdio.h>
#include "Library/ray.h"
#include "Library/read.h"
#include "Library/vector.h"


#define WIDTH  350
#define HEIGHT 350
#define FRAMES 120

#define SCALE 255
#define SKY 1e+30

#define M_PI 3.14159

int main(void) {
    int size = 1;
    TRI* triangles = ReadTriangles("Figuras/yo.stl", &size);
    printf("size: %d\n", size);
    //TRI triangles[1] = {VEC3_set(0,0,1), VEC3_set(-1,0,0), VEC3_set(0,1,0), VEC3_set(1,0,0)};
    if (!triangles) {
        perror("Error al leer el archivo STL");
        return 1;
    }

    VEC3 origen = VEC3_set(0., -1, 0);
    VEC3 foco = VEC3_set(0, -0.5, 0);
    VEC3 techo = VEC3_set(0, 0, 1);
    // Se define el rayo que se lanzará desde el origen de la cámara
    RAY ray = { origen, VEC3_zero() };

    float count = 0;

    for(int t = FRAMES/4; t < FRAMES/2; t++){
        printf("Frame %d\n", t);
        char name[100];
        snprintf(name, sizeof(name), "Animacion/RAY_TRACING_%d.pgm", t);
        FILE *file = fopen(name, "w");
        if (!file) {
            perror("Error al abrir el archivo (RAY)");
            return 1;
        }
        fprintf(file, "P2\n%d %d\n%d\n", WIDTH, HEIGHT, SCALE);

        if(t!=0) {
            ray.o = VEC3_rotateZ(ray.o, M_PI*2*t/FRAMES,VEC3_set(0,0,0));
            foco = VEC3_rotateZ(foco, M_PI*2*t/FRAMES,VEC3_set(0,0,0));
        }
        VEC3 right = VEC3_normalize(VEC3_cross( ray.o,techo));
        VEC3 up =  VEC3_normalize(VEC3_cross( ray.o,right));

        VEC3 l_d = VEC3_sub(foco, ray.o);

        for (int v = 0; v < HEIGHT; v++) {
            for (int h = 0; h < WIDTH; h++) {
                float x = ((float)h - WIDTH/2.0f) / WIDTH;
                float y = ((float)v - HEIGHT/2.0f) / HEIGHT;
                RAY ray_p = ray;
                ray_p.d= VEC3_add(VEC3_scale(right,x),VEC3_scale(up,y));
                ray_p.d = VEC3_add(ray_p.d, VEC3_normalize(VEC3_scale(foco, -1)));
                ray_p.d = VEC3_normalize(ray_p.d);
                //printf("Direccion: %.2f %.2f %.2f\n", ray_p.d.x, ray_p.d.y, ray_p.d.z);

                float min_dst = SKY;
                int closest_triangle_idx = 0;
                if(size!=0){
                    for (int k = 0; k < size; k++) {
                        float d = Intersect(triangles[k],ray_p);
                        if (d < min_dst) {
                            min_dst = d;
                            //printf("Distancia: %.2f\n", min_dst);
                            closest_triangle_idx = k;
                        }
                    }
                }
                float brightness = Shading(min_dst, closest_triangle_idx, ray_p.d, l_d, triangles, size);
                if (brightness > 1.0f) brightness = 1.0f;
                unsigned char u = (unsigned char)(brightness * 255);
                fprintf(file, "%d ", u);
                count++;
                printf("\rProgreso: %.2f%% ", count/(FRAMES*WIDTH*HEIGHT) * 100);
                fflush(stdout);
            }
            fprintf(file, "\n");
        }



        fclose(file);
    }
}
