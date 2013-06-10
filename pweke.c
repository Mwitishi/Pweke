//Avoid double declaring global variables
#define NO_EXTERN

//Include game header
#include "pweke.h"

//Pointer to the screen struct
SDL_Surface *screen = NULL;

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
    screen = SDL_SetVideoMode(640, 480, 16, SDL_OPENGL);

    //OpenGL initialization
    glEnable( GL_TEXTURE_2D );

    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    glViewport( 0, 0, 640, 480 );

    glClear( GL_COLOR_BUFFER_BIT );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    glOrtho(0.0f, 640, 480, 0.0f, -1.0f, 1.0f);

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
    printf("%s %s\n", G_NAME, G_VERSION);

    //Initialization tasks
    if(pw_start()) return 1;

    //Main loop
    while(1) {
        //Event processing
        if(pw_event()) break;
    }

end:
    //Tasks before exiting
    if(pw_exit()) return 1;

    return 0;
}
