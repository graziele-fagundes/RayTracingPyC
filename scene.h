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