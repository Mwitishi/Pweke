#include "pweke.h"

int pw_load_map(char *str1) {
    FILE *f1;
    char *str2;
    int i1;

    str2 = (char*) malloc(strlen(PW_DATA_FOLD) + strlen(str1) + 1);
    sprintf(str2, "%s%s", PW_DATA_FOLD, str1);

    f1 = fopen(str2, "rb+");

    free(str2);
    str2 = NULL;

    fread(&mapx, sizeof(int), 1, f1);
    fread(&mapy, sizeof(int), 1, f1);

    map = (char**) malloc(sizeof(char*) * mapx);
    for(i1 = 0 ; i1 < mapx ; i1++) {
        map[i1] = (char*) malloc(sizeof(char) * mapy);
        fread(map[i1], sizeof(char), mapy, f1);
    }

    fclose(f1);

    return 0;
}
