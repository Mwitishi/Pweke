//Basic library includes
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_opengl.h>

//Game name and version
#define G_NAME "Pweke"
#define G_VERSION "0.0"

//Folder names
#define G_IMG_FOLD "imgs/"
#define G_DATA_FOLD "data/"

//Data files
#define G_TILE_DATA "tiles.dat"
#define G_WALK_DATA "walk.dat"

//Image files
#define G_TILE_IMG "tiles.png"
#define G_PLAYER_IMG "player.png"

//Declare extern variables
#ifndef NO_EXTERN

extern SDL_Surface *screen;

#define NO_EXTERN
#endif
