#include "pweke.h"

//Function for calculating square root of a number
//Uses simple algorithm s = (s + x/s)/2
float pw_sqrt(float f1) {
    float res = f1;

    while(res * res - f1 > PW_SQRT_ERR) res = (res + f1 / res) / 2;

    return res;
}

//Function for creating a vector out of coordinates
struct vector vector_make(float x, float y) {
    struct vector res;

    res.x = x;
    res.y = y;

    return res;
}

//Function for adding two vectors
struct vector vector_a(struct vector v1, struct vector v2) {
    struct vector res;

    res.x = v1.x + v2.x;
    res.y = v1.y + v2.y;

    return res;
}

//Function for calculating product of vector and constant
struct vector vector_c(struct vector v1, float f1) {
    v1.x *= f1;
    v1.y *= f1;

    return v1;
}
 //Function for calculating scalar product
float vector_s(struct vector v1, struct vector v2) {
    return (v1.x * v2.x + v1.y * v2.y);
}

//Function for calculating module of a number
float vector_mod(struct vector v1) {
    return pw_sqrt(v1.x * v1.x + v1.y * v1.y);
}

//Calculate the projection of a vector over another
struct vector vector_project(struct vector v1, struct vector v2) {
    return vector_c(v2, vector_s(v1, v2) / (vector_mod(v2) * vector_mod(v2)));
}
