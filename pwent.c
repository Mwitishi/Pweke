#include "pweke.h"

struct pwent pwent_make(float x, float y, GLuint tex) {
    struct pwent res;

    res.pos.x = x;
    res.pos.y = y;
    res.vel.x = 0;
    res.vel.y = 0;
    res.tex = tex;

    return res;
}


