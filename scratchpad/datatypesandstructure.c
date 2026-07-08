#include <stdio.h>

// Refreshing my C skills

typedef struct vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct transform {
    Vec3 position;
    Vec3 rotation;
    Vec3 scale;
} Transform;

typedef struct mesh
{
    float *verts;
} Mesh;

typedef enum collision {
    NONE,
    SOLID,
} Collision;

typedef struct entity {
    long int id;
    char n[16];
    Transform t;
    Mesh *m;
    Collision c;
} Entity;

const Mesh NULL_MESH = {0};

void print_entity(Entity *ep) {
    Entity e = *ep;
    printf("Entity: %s:%02d\n", e.n, e.id);
    printf("Position\n  x: %3.2f\n  y: %3.2f\n  z: %3.2f\n", e.t.position.x, e.t.position.y ,e.t.position.z);
    printf("Rotation\n  x: %3.2f\n  y: %3.2f\n  z: %3.2f\n", e.t.rotation.x, e.t.rotation.y ,e.t.rotation.z);
    printf("Scale\n  x: %3.2f\n  y: %3.2f\n  z: %3.2f\n", e.t.scale.x, e.t.scale.y ,e.t.scale.z);
    printf("Mesh? %s\n", (ep->m != &NULL_MESH ? "Yes" : "No"));
    printf("Collision? %s\n\n", (e.c == (Collision)SOLID ? "Yes" : "No"));
}

#define MAX_ENTIIES 256
long int HAS_TOGGLEABLE[MAX_ENTIIES];


int set_toggleable(Entity *ep) {
    
}

int main() {
    Vec3 p = {1,2,3};
    Vec3 r = {4,5,6};
    Vec3 s = {7,8,9};
    Transform t = {p,r,s};

    float a[3] = {10, 11, 12};
    float *v = a;
    Mesh vs = {v};

    Entity e = {1, {'T', 'E', 'S', 'T'}, t, &vs, SOLID};
    Entity e2 = {4, {'P', 'E', 'T', 'S'}, t, &NULL_MESH, NONE};
    
    print_entity(&e);
    print_entity(&e2);
}