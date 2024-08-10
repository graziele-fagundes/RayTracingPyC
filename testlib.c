#include <math.h>
#include <stdlib.h>
#include <float.h>

float *normalize(float *arr, int size);
int rayTracing(float x, float y, float xLightDir);
float dotProduct(float *a, float *b);

typedef struct Sphere {
    float position[3];
    float radius;
    float color[3];
}s_sphere;

typedef struct Scene {
    struct Sphere *spheres;
    int numSpheres;
}s_scene;

s_scene scene = {
    .spheres = (s_sphere[]) {
        {
            .position = {0, 0, 0},
            .radius = 0.1,
            .color = {255, 0, 0}
        },
        {
            .position = {-0.1, 0, -0.1},
            .radius = 0.1,
            .color = {0, 255, 0}
        },
    },
    .numSpheres = 2
}; 

int rayTracing(float x, float y, float xLightDir) {
    float rayOrigin[] = {0, 0, 0.2};
    float origin[3];
    float spherePosition[3] = {-0.1, 0, 0};
    float hitPoint[3];
    float normal[3];
    float lightDir[] = {xLightDir, -1, -1};
    float lightDirNormalized[3];
    float rayDirection[] = {x, -y, -1.0};
    int red, green, blue;

    if (scene.numSpheres == 0) {
        red = 128;
        green = 128;
        blue = 128;
        int rgb = (red << 16) | (green << 8) | blue;
        return rgb;
    }

    s_sphere *closestSphere = NULL;
    float hitDistance = FLT_MAX;

    for (int i = 0; i < scene.numSpheres; i++){
        s_sphere sphere = scene.spheres[i];

        origin[0] = rayOrigin[0] - sphere.position[0];
        origin[1] = rayOrigin[1] - sphere.position[1];
        origin[2] = rayOrigin[2] - sphere.position[2];

        float a = dotProduct(rayDirection, rayDirection);
        float b = 2 * dotProduct(rayDirection, origin);
        float c = dotProduct(origin, origin) - pow(sphere.radius, 2);

        float discriminant = pow(b, 2) - 4 * a * c;


        if (discriminant < 0) {
            continue;
        }

        // float t0 = (-b + sqrt(discriminant)) / (2 * a);
        float closestT = (-b - sqrt(discriminant)) / (2 * a);
        if (closestT < hitDistance){
            hitDistance = closestT;
            closestSphere = &scene.spheres[i];
        }
    }

    if (closestSphere == NULL){
        red = 128;
        green = 128;
        blue = 128;
        int rgb = (red << 16) | (green << 8) | blue;
        return rgb;
    }

    origin[0] = rayOrigin[0] - closestSphere->position[0];
    origin[1] = rayOrigin[1] - closestSphere->position[1];
    origin[2] = rayOrigin[2] - closestSphere->position[2];

    for (int i = 0; i < 3; i++) {
        hitPoint[i] = origin[i] + rayDirection[i] * hitDistance;
    }

    for (int i = 0; i < 3; i++) {
        normal[i] = hitPoint[i];
    }
    normalize(normal, 3);

    normalize(lightDir, 3);
    lightDir[0] = -lightDir[0];
    lightDir[1] = -lightDir[1];
    lightDir[2] = -lightDir[2];


    float d = fmaxf(dotProduct(normal, lightDir), 0);

    red = (int)((d) * closestSphere->color[0]);
    green = (int)((d) * closestSphere->color[1]);
    blue = (int)((d) * closestSphere->color[2]);  

    // Combine RGB values into a single integer
    int rgb = (red << 16) | (green << 8) | blue;

    return rgb;
}

float *normalize(float *arr, int size) {
    float denominator = sqrt(pow(arr[0], 2) + pow(arr[1], 2) + pow(arr[2], 2));

    for (int i = 0; i < size; i++) {
        arr[i] = arr[i] / denominator;
    }

    return arr;
}

float dotProduct(float *a, float *b) {
    float result = 0;

    for (int i = 0; i < 3; i++) {
        result += a[i] * b[i];
    }

    return result;
}
