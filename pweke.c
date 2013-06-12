/*
 * File: pweke.c / Project: Pweke
 * Author: Mwitishi
 * This is the main source code file in project Pweke.
 * It contains the main function of the program,
 * as well as functions which make up the main processing tree.
 * Global variables are declared in this file.
 */

//Avoid double declaring global variables
#define NO_EXTERN

//Include game header
#include "pweke.h"

//Pointer to the screen struct
SDL_Surface *screen = NULL;

//Handlers to OpenGL textures
GLuint player_tex, tile_tex;

//Texture data
char tile_walk[PW_TILE_QUAN] = PW_TILE_WALK;

//Loaded map data
int mapx = 0, mapy = 0;
char **map;

//Entities
struct pwent *player = NULL;

//Scroll data
float sx = 0, sy = 0;

//Game tick count
uint32_t tick;

//Function for initializing the game
int pw_start() {
    char *str1 = NULL;
    SDL_Surface *img1 = NULL;

    //SDL initialization
    if(SDL_Init(SDL_INIT_EVERYTHING)) {
        printf("Error while starting SDL.\n");
        return 1;
    }

    //OpenGL stuff
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    //Create screen
    screen = SDL_SetVideoMode(PW_SCREEN_W, PW_SCREEN_H, 16, SDL_OPENGL);
    SDL_WM_SetCaption(PW_NAME,NULL);

    //OpenGL initialization: 2D textures
    glEnable( GL_TEXTURE_2D );

    //Background color: black
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

    //Viewport (drawing area) = all screen
    glViewport( 0, 0, PW_SCREEN_W, PW_SCREEN_H);

    //Clear screen
    glClear( GL_COLOR_BUFFER_BIT );

    //Set projection data
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(0.0f, PW_SCREEN_W, PW_SCREEN_H, 0.0f, -1.0f, 1.0f);

    //Reset matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Load textures
    glGenTextures(1, &tile_tex);
    glGenTextures(1, &player_tex);

    //Load image into SDL surface
    str1 = (char*) malloc(strlen(PW_IMG_FOLD) + strlen(PW_TILE_IMG) + 1);
    sprintf(str1, "%s%s", PW_IMG_FOLD, PW_TILE_IMG);
    img1 = IMG_Load(str1);

    glBindTexture(GL_TEXTURE_2D, tile_tex);
    // Set the texture's stretching properties
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexImage2D(GL_TEXTURE_2D, 0, 3, img1->w, img1->h, 0, GL_RGB, GL_UNSIGNED_BYTE, img1->pixels );

    SDL_FreeSurface(img1);
    img1 = NULL;
    free(str1);
    str1 = NULL;

    //Load map

    return 0;
}

//Function for processing events (keyboard, mouse etc.)
int pw_event() {
    //Structure which holds event data
    SDL_Event e1;

    //Loop for processing all events
    while(SDL_PollEvent(&e1) != 0) {
        //If the user closes the game
        if(e1.type == SDL_QUIT) return 1;
    }

    return 0;
}

//Function for updating positions and checking collisions
int pw_update() {
    if(player != NULL) {
        player->pos.x += player->vel.x;
        player->pos.y += player->vel.y;
    }

    return 0;
}

//Function for rendering the scene
int pw_draw() {
    int i1, i2, i3, i4;

    //Set matrix and initialize
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Clear screen
    glClear(GL_COLOR_BUFFER_BIT);

    //Render the tilemap
    //Get the minimum coordinates for tiles on screen
    i1 = (float)PW_TILE_SIZE * (int)(sx / PW_TILE_SIZE);
    i2 = (float)PW_TILE_SIZE * (int)(sy / PW_TILE_SIZE);
    //Loop through all tiles to be rendered
    for (i3 = i1 ; i3 * PW_TILE_SIZE < sx + PW_SCREEN_W ; i3++) {
        for(i4 = i2 ; i4 * PW_TILE_SIZE < sy + PW_SCREEN_H ; i4++) {
            //Translate to specified position
            glLoadIdentity();
            glTranslatef(i3 * PW_TILE_SIZE - sx, i4 * PW_TILE_SIZE - sy, 0.f);

            glBindTexture(GL_TEXTURE_2D, tile_tex);

            //Render quad
            glBegin(GL_QUADS);
                glTexCoord2f(0, 0);
                glVertex2f(0.f, 0.f);
                glTexCoord2f(0, 1);
                glVertex2f(0.f, (float)PW_TILE_SIZE);
                glTexCoord2f(1 / PW_TILE_QUAN, 1);
                glVertex2f((float)PW_TILE_SIZE, (float)PW_TILE_SIZE);
                glTexCoord2f(1 / PW_TILE_QUAN, 0);
                glVertex2f((float)PW_TILE_SIZE, 0.f);
            glEnd();
        }
    }

    //Render player
    pwent_draw(player);

    //Switch buffers, update screen
    SDL_GL_SwapBuffers();

    return 0;
}

//Function for cleaning up before exit
int pw_exit() {
    //Free player structure
    if(player != NULL) {
        free(player);
        player = NULL;
    }

    //Free the map array
    if(map != NULL) {
        free(map);
        map = NULL;
    }

    //Free the screen
    SDL_FreeSurface(screen);
    screen = NULL;

    //Quit SDL
    SDL_Quit();

    return 0;
}

int main(int argc, char **argv) {
    //Write game name and version
    printf("%s %s\n", PW_NAME, PW_VERSION);

    //Initialization tasks
    if(pw_start()) return 1;

    //Main loop
    while(1) {
        //Event processing
        if(pw_event()) goto end;

        //Entity updates
        if(pw_update()) goto end;

        //Render the scene
        if(pw_draw()) goto end;
    }

end:
    //Tasks before exiting
    if(pw_exit()) return 1;

    return 0;
}
