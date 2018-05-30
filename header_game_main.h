#ifndef HEADER_GAME_MAIN_H_INCLUDED
#define HEADER_GAME_MAIN_H_INCLUDED

typedef struct coordinates{
    int x;
    int y;
}coordinates;

int move(char **mapfinal, coordinates *Object, coordinates *Axis);
int drawresults(char **mapfinal, coordinates *Map, int steps, int whichmap);
char **drawmap(char **mapfinal, coordinates *Map);
int keypressed(char **mapfinal, coordinates *Axis, coordinates *Map, int *steps);
int searchplayer(char **mapfinal, coordinates *Map, coordinates *Player);

#endif // HEADER_GAME_MAIN_H_INCLUDED
