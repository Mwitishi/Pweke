/*
 * File: pwaux.c / Project: Pweke
 * Author: Mwitishi
 * This file contains auxiliary functions of the project Pweke.
 * They mainly work with structures vector and poly,
 * both defined in pweke.h
 */

#include "pweke.h"

//Function for creating a vector out of coordinates
struct vector vector_make(float x, float y) {
    struct vector res;

    res.x = x;
    res.y = y;

    return res;
}

//Function for creating a polygon
struct poly poly_make(int n, struct vector *v) {
    struct poly res;

    res.n = n;
    res.v = v;

    return res;
}

//Check if two polygons intersect
char poly_collide(struct poly p1, struct poly p2) {
    int i1,i2;
    struct vector v1;
    float f1;

    //Check each edge in the first polygon
    for(i1 = 0 ; i1 < p1.n ; i1++) {
        //Get vector for projecting distance
        v1 = NVECTOR(VECTOR_A(p1.v[(i1+1) % p1.n], VECTOR_C(p1.v[i1],-1.f)));
        //Get scalar product using point in first polygon
        f1 = VECTOR_S(v1, VECTOR_A(p1.v[(i1+2) % p1.n], VECTOR_C(p1.v[i1], -1.f)));
        if(f1 == 0) continue;

        //Check each point in second polygon
        //If scalar product is same sign, continue to next edge
        for(i2 = 0 ; i2 < p2.n ; i2++)
            if(VECTOR_S(v1, VECTOR_A(p2.v[i2], VECTOR_C(p1.v[i1], -1.f))) / f1 >= 0) break;

        if(i2 < p2.n) continue;

        //If all points are on the other side, no intersection
        return 0;
    }

    //Check the second polygon
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
