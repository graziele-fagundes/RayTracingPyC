#include <math.h>
#include <stdlib.h>
#include <float.h>

typedef struct HitPayload {
    float hitDistance;
    float WorldPosition[3];
    float WorldNormal[3];

    int ObjectIndex;
} s_hitPayload;

typedef struct Ray {
    float origin[3];
    float direction[3];
} s_ray;

float *normalize(float *arr, int size);
s_hitPayload TraceRay(s_ray ray);
s_hitPayload ClosestHit(s_ray ray, int objectIndex, float hitDistance);
s_hitPayload Miss(s_ray ray);
int PerPixel(float x, float y);
float dotProduct(float *a, float *b);
void reflect(float *direction, float *normal, float *reflected);


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
            .position = {0, 0.025, 0},
            .radius = 0.02,
            .color = {255, 0, 255}
        },
        {
            .position = {0, -0.1, 0},
            .radius = 0.08,
            .color = {51, 77, 255}
        },
    },
    .numSpheres = 2
};

s_hitPayload ClosestHit(s_ray ray, int objectIndex, float hitDistance){

    s_hitPayload hitPayload = {
        .hitDistance = hitDistance,
        .ObjectIndex = objectIndex
    };

    s_sphere *closestSphere = &scene.spheres[objectIndex];
    float origin[3];
    float lightDir[] = {-1, -1, -1};
    float normal[3];
    int red, green, blue;

    for (int i = 0; i < 3; i++) {
        origin[i] = ray.origin[i] - closestSphere->position[i];
    }

    for (int i = 0; i < 3; i++) {
        hitPayload.WorldPosition[i] = origin[i] + ray.direction[i] * hitDistance;
    }

    for (int i = 0; i < 3; i++) {
        hitPayload.WorldNormal[i] = hitPayload.WorldPosition[i];
    }
    normalize(hitPayload.WorldNormal, 3);

    for (int i = 0; i < 3; i++) {
        hitPayload.WorldPosition[i] += closestSphere->position[i];
    }

    return hitPayload;
}

s_hitPayload Miss(s_ray ray){
    s_hitPayload HitPayload;
    HitPayload.hitDistance = -1;

    return HitPayload;
}

int PerPixel(float x, float y){
    // Initialize the ray
    s_ray ray = {
        .origin = {0, 0, 0.2},
        .direction = {x, -y, -1.0}
    };
    
    normalize(ray.direction, 3);

    int colorR = 0;
    int colorG = 0;
    int colorB = 0;

    int skyColorR = 0; // Sky blue
    int skyColorG = 0;
    int skyColorB = 0;

    float multiplier = 1.0f;

    float lightDir[] = {-1, -1, -1};
    normalize(lightDir, 3);
    lightDir[0] = -lightDir[0];
    lightDir[1] = -lightDir[1];
    lightDir[2] = -lightDir[2];

    int bounces = 2;
    for (int i = 0; i < bounces; i++){
        s_hitPayload HitPayload = TraceRay(ray);

        if (HitPayload.hitDistance < 0){
            colorR += skyColorR * multiplier;
            colorG += skyColorG * multiplier;
            colorB += skyColorB * multiplier;
            break;
        }

        float lightIntensity = fmaxf(dotProduct(HitPayload.WorldNormal, lightDir), 0.0f);

        s_sphere *Sphere = &scene.spheres[HitPayload.ObjectIndex];
        int red = Sphere->color[0];
        int green = Sphere->color[1];
        int blue = Sphere->color[2];

        colorR += (int)(red * lightIntensity * multiplier);
        colorG += (int)(green * lightIntensity * multiplier);
        colorB += (int)(blue * lightIntensity * multiplier);

        multiplier *= 0.7f;

        for (int i = 0; i < 3; i++){
            ray.origin[i] = HitPayload.WorldPosition[i] + HitPayload.WorldNormal[i] * 0.001f;
        }

        float reflectedDirection[3];
        reflect(ray.direction, HitPayload.WorldNormal, reflectedDirection);

        for (int i = 0; i < 3; i++){
            ray.direction[i] = reflectedDirection[i];
        }
    }

    colorR = fminf(fmaxf(colorR, 0), 255);
    colorG = fminf(fmaxf(colorG, 0), 255);
    colorB = fminf(fmaxf(colorB, 0), 255);

    return (colorR << 16) | (colorG << 8) | colorB;
}


s_hitPayload TraceRay(s_ray ray) {
    float origin[3];
    int closestSphere = -1;
    float hitDistance = FLT_MAX;

    for (int i = 0; i < scene.numSpheres; i++){
        s_sphere sphere = scene.spheres[i];

        origin[0] = ray.origin[0] - sphere.position[0];
        origin[1] = ray.origin[1] - sphere.position[1];
        origin[2] = ray.origin[2] - sphere.position[2];

        float a = dotProduct(ray.direction, ray.direction);
        float b = 2 * dotProduct(ray.direction, origin);
        float c = dotProduct(origin, origin) - pow(sphere.radius, 2);

        float discriminant = pow(b, 2) - 4 * a * c;


        if (discriminant < 0) {
            continue;
        }

        // float t0 = (-b + sqrt(discriminant)) / (2 * a);
        float closestT = (-b - sqrt(discriminant)) / (2 * a);
        if (closestT > 0 && closestT < hitDistance){
            hitDistance = closestT;
            closestSphere = (int)i;
        }
    }

    if (closestSphere < 0){
        return Miss(ray);
    }

    return ClosestHit(ray, closestSphere, hitDistance);
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

void reflect(float *direction, float *normal, float *reflected) {
    // Calculate the dot product of the direction and normal
    float dot = dotProduct(direction, normal);

    // Calculate the reflected vector
    for (int i = 0; i < 3; i++) {
        reflected[i] = direction[i] - 2.0 * dot * normal[i];
    }
}