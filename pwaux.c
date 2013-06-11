#include "pweke.h"

float pw_sqrt(float f1) {
    float res = f1;

    while(res * res - f1 > PW_SQRT_ERR) res = (res + f1 / res) / 2;

    return res;
}

struct vector vector_make(float x, float y) {
    struct vector res;

    res.x = x;
    res.y = y;

    return res;
}

struct vector vector_a(struct vector v1, struct vector v2) {
    struct vector res;

    res.x = v1.x + v2.x;
    res.y = v1.y + v2.y;

    return res;
}

struct vector vector_c(struct vector v1, float f1) {
    v1.x *= f1;
    v1.y *= f1;

    return v1;
}

float vector_s(struct vector v1, struct vector v2) {
    return (v1.x * v2.x + v1.y * v2.y);
}

float vector_mod(struct vector v1) {
    return pw_sqrt(v1.x * v1.x + v1.y * v1.y);
}
