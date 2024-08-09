#include <math.h>
#include <stdlib.h>

float *normalize(float *arr, int size);
int rayTracing(float x, float y, float xLightDir);
float dotProduct(float *a, float *b);


int rayTracing(float x, float y, float xLightDir) {
    float rayOrigin[] = {0, 0, 0.2};
    float radius = 0.1;
    float hitPoint[3];
    float normal[3];
    float lightDir[] = {xLightDir, -1, -1};
    float lightDirNormalized[3];
    float rayDirection[] = {x, -y, -1.0};

    float a = dotProduct(rayDirection, rayDirection);
    float b = 2 * dotProduct(rayDirection, rayOrigin);
    float c = dotProduct(rayOrigin, rayOrigin) - pow(radius, 2);

    float discriminant = pow(b, 2) - 4 * a * c;

    int red, green, blue;

    if (discriminant < 0) {
        red = 128;
        green = 128;
        blue = 128;
    } else {
        float t0 = (-b + sqrt(discriminant)) / (2 * a);
        float t1 = (-b - sqrt(discriminant)) / (2 * a);
        float closestT = fminf(t0, t1);

        for (int i = 0; i < 3; i++) {
            hitPoint[i] = rayOrigin[i] + rayDirection[i] * closestT;
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

        red = (int)((d) * 255);
        green = (int)((d) * 0);
        blue = (int)((d) * 0);  

        red = fminf(fmaxf(red, 0), 255);
        green = fminf(fmaxf(green, 0), 255);
        blue = fminf(fmaxf(blue, 0), 255);
    }	

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
