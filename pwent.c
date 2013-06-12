#include "pweke.h"

//Create an entity given entity data
struct pwent pwent_make(float x, float y, GLuint tex) {
    struct pwent res;

    res.pos.x = x;
    res.pos.y = y;
    res.vel.x = 0;
    res.vel.y = 0;
    res.tex = tex;

    return res;
}

struct poly pwent_box(struct pwent pe1) {
    struct poly res;
    struct vector v1;

    //Create bounding polygon
    res.n = 4;
    res.v = malloc(sizeof(struct vector) * 4);
    v1 = VECTOR_ROTATE(vector_make(-pe1.size.x / 2, -pe1.size.y / 2), pe1.angle);
    res.v[0] = VECTOR_A(pe1.pos, v1);
    v1 = VECTOR_ROTATE(vector_make(-pe1.size.x / 2, pe1.size.y / 2), pe1.angle);
    res.v[1] = VECTOR_A(pe1.pos, v1);
    v1 = VECTOR_ROTATE(vector_make(pe1.size.x / 2, pe1.size.y / 2), pe1.angle);
    res.v[2] = VECTOR_A(pe1.pos, v1);
    v1 = VECTOR_ROTATE(vector_make(pe1.size.x / 2, -pe1.size.y / 2), pe1.angle);
    res.v[3] = VECTOR_A(pe1.pos, v1);

    return res;
}
