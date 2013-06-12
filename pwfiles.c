/*
 * File: pwfiles.c / Project: Pweke
 * Author: Mwitishi
 * This file contains functions related to files used by program Pweke.
 * Files are accessed using functions in stdio.h, included in pweke.h
 * Data files are contained in folder PW_DATA_FOLD,
 * defined in pweke.h
 */

#include "pweke.h"

//Function for loading a tilemap from a file
int pw_load_map(char *str1) {
    FILE *f1;
    char *str2;
    int i1;

    //Make path for the file
    str2 = (char*) malloc(strlen(PW_DATA_FOLD) + strlen(str1) + 1);
    sprintf(str2, "%s%s", PW_DATA_FOLD, str1);

    //Open file specified by the path
    f1 = fopen(str2, "rb+");
    if(f1 == NULL) return 1;

    //Free memory
    free(str2);
    str2 = NULL;

    //Read map size
    fread(&mapx, sizeof(int), 1, f1);
    fread(&mapy, sizeof(int), 1, f1);

    //Read map data into 2D array
    map = (char**) malloc(sizeof(char*) * mapx);
    for(i1 = 0 ; i1 < mapx ; i1++) {
        map[i1] = (char*) malloc(sizeof(char) * mapy);
        fread(map[i1], sizeof(char), mapy, f1);
    }

    //Close file
    fclose(f1);
    f1 = NULL;

    return 0;
}
