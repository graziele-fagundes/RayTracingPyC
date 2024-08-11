typedef struct Material {
    float color[3];
    float roughness;
    float metallic;
} s_material;

typedef struct Sphere {
    float position[3];
    float radius;
    s_material material;
}s_sphere;

typedef struct Scene {
    struct Sphere *spheres;
    int numSpheres;
}s_scene;

s_scene scene = {
    .spheres = (s_sphere[]) {
        {
            .position = {0, 0.001, 0},
            .radius = 0.02,
            .material.color = {31, 255, 0},
            .material.roughness = 1
        },
        {
            .position = {0, -0.92, 0},
            .radius = 0.9,
            .material.color = {51, 77, 255},
            .material.roughness = 0.1
        },
        {
            .position = {0.04, -0.005, 0.035},
            .radius = 0.015,
            .material.color = {115, 62, 156},
            .material.roughness = 0.1
        },
        {
            .position = {-0.04, -0.005, 0.035},
            .radius = 0.015,
            .material.color = {156, 62, 118},
            .material.roughness = 0.1
        }
    },
    .numSpheres = 4
};