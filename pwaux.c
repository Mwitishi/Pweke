#include "pweke.h"

//Function for creating a vector out of coordinates
struct vector vector_make(float x, float y) {
    struct vector res;

    res.x = x;
    res.y = y;

    return res;
}

struct poly poly_make(int n, struct vector *v) {
    struct poly res;

    res.n = n;
    res.v = v;

    return res;
}

char poly_collide(struct poly p1, struct poly p2) {
    int i1,i2;
    struct vector v1;
    float f1;

    for(i1 = 0 ; i1 < p1.n ; i1++) {
        v1 = NVECTOR(VECTOR_A(p1.v[(i1+1) % p1.n], VECTOR_C(p1.v[i1],-1.f)));
        f1 = VECTOR_S(v1, VECTOR_A(p1.v[(i1+2) % p1.n], VECTOR_C(p1.v[i1], -1.f)));
        if(f1 == 0) continue;

        for(i2 = 0 ; i2 < p2.n ; i2++)
            if(VECTOR_S(v1, VECTOR_A(p2.v[i2], VECTOR_C(p1.v[i1], -1.f))) / f1 >= 0) break;

        if(i2 < p2.n) continue;

        return 0;
    }

    for(i1 = 0 ; i1 < p2.n ; i1++) {
        v1 = NVECTOR(VECTOR_A(p2.v[(i1+1) % p2.n], VECTOR_C(p2.v[i1],-1.f)));
        f1 = VECTOR_S(v1, VECTOR_A(p2.v[(i1+2) % p2.n], VECTOR_C(p2.v[i1], -1.f)));
        if(f1 == 0) continue;

        for(i2 = 0 ; i2 < p1.n ; i2++)
            if(VECTOR_S(v1, VECTOR_A(p1.v[i2], VECTOR_C(p2.v[i1], -1.f))) / f1 >= 0) break;

        if(i2 < p1.n) continue;

        return 0;
    }

    return 1;
}
