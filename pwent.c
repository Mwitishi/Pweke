/*
 * File: pwent.c / Project: Pweke
 * Author: Mwitishi
 * This file contains source code related to entities in the project Pweke.
 * Entities are contained in structure pwent, defined in pweke.h
 */

#include "pweke.h"

//Create an entity given entity data
struct pwent pwent_make(float x, float y, GLuint tex, float w, float h, float angle) {
    struct pwent res;

    res.pos.x = x;
    res.pos.y = y;
    res.vel.x = 0;
    res.vel.y = 0;
    res.tex = tex;
    res.size.x = w;
    res.size.y = h;
    res.angle = angle;

    return res;
}

//Get the bounding rectangle of an entity (for collisions)
struct poly pwent_box(struct pwent pe1) {
    struct poly res;
    struct vector v1;

    //Initialize structure (4 sides, rectangle)
    res.n = 4;
    res.v = malloc(sizeof(struct vector) * 4);
    //For each edge, calculate relative position and rotate
    v1 = VECTOR_ROTATE(vector_make(-pe1.size.x / 2, -pe1.size.y / 2), pe1.angle * M_PI / 180);
    //Then calculate absolute position
    res.v[0] = VECTOR_A(pe1.pos, v1);
    //Repeat for other edges
    v1 = VECTOR_ROTATE(vector_make(-pe1.size.x / 2, pe1.size.y / 2), pe1.angle * M_PI / 180);
    res.v[1] = VECTOR_A(pe1.pos, v1);
    v1 = VECTOR_ROTATE(vector_make(pe1.size.x / 2, pe1.size.y / 2), pe1.angle * M_PI / 180);
    res.v[2] = VECTOR_A(pe1.pos, v1);
    v1 = VECTOR_ROTATE(vector_make(pe1.size.x / 2, -pe1.size.y / 2), pe1.angle * M_PI / 180);
    res.v[3] = VECTOR_A(pe1.pos, v1);

    return res;
}

int pwent_draw(struct pwent *pe1) {
    if(pe1 == NULL) return 0;

    //Translate and rotate matrix
    glLoadIdentity();
    glTranslatef(pe1->pos.x, pe1->pos.y, 0.f);
    glRotatef(pe1->angle, 0.f, 0.f, 1.f);

    //Render the rectangle
    glColor4f(1.f, 1.f, 1.f, 1.f);
    glBegin(GL_QUADS);
        glVertex2f(-pe1->size.x / 2, -pe1->size.y / 2);
        glVertex2f(-pe1->size.x / 2, pe1->size.y / 2);
        glVertex2f(pe1->size.x / 2, pe1->size.y / 2);
        glVertex2f(pe1->size.x / 2, -pe1->size.y / 2);
    glEnd();

    return 0;
}
