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

#endif

//Struct for holding vector data
struct vector {
    float x;
    float y;
};

//Struct for containing entity data
struct pwent {
    //Entity position
    float x;
    float y;
    //Entity speed
    float vx;
    float vy;
    //Entity texture
    GLuint tex;
};

//Declare functions in pwent.c
struct pwent pwent_make(float, float, GLuint);

//Declare functions in pwaux.c
struct vector vector_make(float, float);
struct vector vector_a(struct vector, struct vector);
struct vector vector_c(struct vector, float);
float vector_s(struct vector, struct vector);

#endif
