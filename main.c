#include "main.h"

SDL_Surface *screen = NULL;

int g_start() {
    //SDL initialization
    if(SDL_Init(SDL_INIT_EVERYTHING)) {
        printf("Error while starting SDL.\n");
        return 1;
    }

    //OpenGL stuff
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    //Create screen
    screen = SDL_SetVideoMode(640, 480, 16, SDL_OPENGL);

    return 0;
}

int g_exit() {
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
    if(g_start()) return 1;

end:
    //Tasks before exiting
    if(g_exit()) return 1;

    return 0;
}
