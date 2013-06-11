//Avoid double declaring global variables
#define NO_EXTERN

//Include game header
#include "pweke.h"

//Pointer to the screen struct
SDL_Surface *screen = NULL;

//Handlers to OpenGL textures
GLuint player_tex;
int tile_quan = 0;
GLuint tile_tex;

//Loaded map data
int mapx = 0, mapy = 0;
char **map;

//Scroll data
float sx = 0, sy = 0;

float angle = 0;

//Function for initializing the game
int pw_start() {
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

    //OpenGL initialization
    glEnable( GL_TEXTURE_2D );

    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

    glViewport( 0, 0, PW_SCREEN_W, PW_SCREEN_H);

    glClear( GL_COLOR_BUFFER_BIT );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    glOrtho(0.0f, PW_SCREEN_W, PW_SCREEN_H, 0.0f, -1.0f, 1.0f);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

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

//Function for rendering the scene
int pw_draw() {
    int i1, i2, i3, i4;

    //Set matrix and initialize
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);

    //Render the tilemap
    i1 = (float)PW_TILE_SIZE * (int)(sx / PW_TILE_SIZE);
    i2 = (float)PW_TILE_SIZE * (int)(sy / PW_TILE_SIZE);
    for (i3 = i1 ; i3 * PW_TILE_SIZE < sx + PW_SCREEN_W ; i3++) {
        for(i4 = i2 ; i4 * PW_TILE_SIZE < sy + PW_SCREEN_H ; i4++) {
            glLoadIdentity();
            glTranslatef(i3 * PW_TILE_SIZE - sx, i4 * PW_TILE_SIZE - sy, 0.f);
            if((i3 + i4) % 2 == 0) glColor3f(1.f, 0.f, 1.f);
            else glColor3f(0.f, 1.f, 0.f);

            glBegin(GL_QUADS);
                glVertex2f(0.f, 0.f);
                glVertex2f(0.f, (float)PW_TILE_SIZE);
                glVertex2f((float)PW_TILE_SIZE, (float)PW_TILE_SIZE);
                glVertex2f((float)PW_TILE_SIZE, 0.f);
            glEnd();
        }
    }


    //Render rotating rectangle (sample)
    glLoadIdentity();
    glTranslatef(PW_SCREEN_W / 2.f, PW_SCREEN_H / 2.f, 0.f);
    glRotatef(angle, 0.f, 0.f, 1.f);

    glBegin(GL_QUADS);
        glColor3f(1.f, 1.f, 1.f);
        glVertex2f(-64.f, 32.f);
        glColor3f(1.f, 0.f, 0.f);
        glVertex2f(64.f, 32.f);
        glVertex2f(64.f, -32.f);
        glColor3f(1.f, 1.f, 1.f);
        glVertex2f(-64.f, -32.f);
    glEnd();

    //Render rectangle outside screen (sample)
    glLoadIdentity();
    glTranslatef(PW_SCREEN_W + 20.f, PW_SCREEN_H / 2.f, 0.f);

    glBegin(GL_QUADS);
        glVertex2f(-32.f, 32.f);
        glVertex2f(32.f, 32.f);
        glVertex2f(32.f, -32.f);
        glVertex2f(-32.f, -32.f);
    glEnd();

    SDL_GL_SwapBuffers();

    return 0;
}

//Function for cleaning up before exit
int pw_exit() {
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

        angle += 1.f;

        pw_draw();
    }

end:
    //Tasks before exiting
    if(pw_exit()) return 1;

    return 0;
}
