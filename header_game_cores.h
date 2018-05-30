#ifndef HEADER_GAME_CORES_H_INCLUDED
#define HEADER_GAME_CORES_H_INCLUDED

/*
typedef struct coordinates{
    int x;
    int y;
}coordinates;*/

int loadnewmap(coordinates *Map, int loader, int *whichmap, char ***mapfinal, char **mapstart, int *steps);
int gamecore(char **mapfinal, coordinates *Map, int whichmap, int *steps);
int savemap(char **maptosave, coordinates Map, int whichmap, int steps);

#endif // HEADER_GAME_CORES_H_INCLUDED
