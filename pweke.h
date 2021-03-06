/*
 * File: pweke.h / Project: Pweke
 * Author: Mwitishi
 * This is the main header file for project Pweke.
 * It contains other header includes, macros containing data about the game,
 * extern variable declarations, struct definitions, and declarations of functions.
 * This header is included in all source code files in project Pweke.
 */

#ifndef PWEKE_H
#define PWEKE_H

//Basic library includes
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_opengl.h>

//Game name and version
#define PW_NAME "Pweke"
#define PW_VERSION "0.0"

//Number constants
#define PW_SCREEN_W 640
#define PW_SCREEN_H 480
#define PW_TILE_SIZE 64
#define PW_TILE_QUAN 3
#define PW_TILE_WALK {0, 1, 1}

//Auxiliary constants
#define PW_SQRT_ERR 0.001f

//Folder names
#define PW_IMG_FOLD "imgs/"
#define PW_DATA_FOLD "data/"

//Data files
#define PW_TILE_DATA "tiles.dat"
#define PW_WALK_DATA "walk.dat"

//Image files
#define PW_TILE_IMG "tiles.png"
#define PW_PLAYER_IMG "player.png"

//Declare extern variables
#ifndef NO_EXTERN
#define NO_EXTERN

extern SDL_Surface *screen;
extern GLuint player_tex, tile_tex;
extern char *tile_walk;
extern int mapx, mapy;
extern char **map;
extern struct pwent *player;
extern float sx, sy;
extern uint32_t tick;
extern float angle;

#endif

//Struct for holding vector data
struct vector {
    float x;
    float y;
};

//Struct for holding polygons
//Each vector represents one point
struct poly {
    int n;
    struct vector *v;
};

//Struct for containing entity data
struct pwent {
    //Entity position (centre of rectangle)
    struct vector pos;
    //Entity speed
    struct vector vel;
    //Entity texture
    GLuint tex;
    //Entity size
    struct vector size;
    //Rotation angle
    float angle;
};

//Declare functions and macros in pwent.c
struct pwent pwent_make(float, float, GLuint, float, float, float);
struct poly pwent_box(struct pwent);
int pwent_draw(struct pwent*);
//Obtain facing direction of an entity
#define PWENT_FACE(pe1) vector_make(cos(pe1.angle * M_PI / 180), sin(pe1.angle * M_PI / 180));


//Declare functions and macros in pwaux.c
float pw_sqrt(float);
struct vector vector_make(float, float);
struct poly poly_make(int, struct vector*);
char poly_collide(struct poly, struct poly);
//Add two vectors
#define VECTOR_A(v1, v2) vector_make(v1.x + v2.x, v1.y + v2.y)
//Product of a vector and a constant
#define VECTOR_C(v1, f1) vector_make(v1.x * f1, v1.y * f1)
//Scalar product of two vectors
#define VECTOR_S(v1, v2) (v1.x * v2.x + v1.y * v2.y)
//Module of a vector
#define VECTOR_MOD(v1) sqrt(v1.x * v1.x + v1.y * v1.y)
//Projection of one vector over another
#define VECTOR_PROJECT VECTOR_C(v2, VECTOR_S(v1, v2) / VECTOR_S(v2, v2))
//Rotate a vector by angle f1 (clockwise)
#define VECTOR_ROTATE(v1, f1) VECTOR_A(VECTOR_C(v1, (float)cos((double)f1)), VECTOR_C(NVECTOR(v1), (float)sin((double)f1)));
//Get normal vector to v1
#define NVECTOR(v1) vector_make(-v1.y, v1.x)

//Declare functions in pwfiles.c
int pw_load_map(char*);

#endif
