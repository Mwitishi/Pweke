#include "pweke.h"

struct pwent pwent_make(float x, float y, GLuint tex) {
    struct pwent res;

    res.x = x;
    res.y = y;
    res.vx = 0;
    res.vy = 0;
    res.tex = tex;

    return res;
}

