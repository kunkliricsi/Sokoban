#ifndef HEADER_SOKOBAN_H_INCLUDED
#define HEADER_SOKOBAN_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

/* a hiba kezelő függvény kilépési kódjai */
enum EXIT_CODE
{
    OPENING_MAPS            = 90,
    OPENING_LOADED_MAPS     = 91,
    ONE_DIM_ARRAY_MALLOC    = 92,
    TWO_DIM_ARRAY_MALLOC1   = 93,
    TWO_DIM_ARRAY_MALLOC2   = 94,
    SAVING_TO_LOADED_MAPS   = 95,
    SAVING_MAP_LIST_MALLOC  = 96,
    SAVING_NEW_LIST_MALLOC  = 97,
    OPENING_HIGHSCORE_WRITE = 98,
    OPENING_HIGHSCORE_READ  = 99,
    TWO_DIM_ARRAY_MALLOC3   =100,
    TWO_DIM_ARRAY_MALLOC4   =101,
    OPENING_CREATEDMAP_WRITE=102,
    OPENING_CREATED_MAPS    =103,
};

/* a menupontok pozícióinak tárolására való, illetve kezeli a kiválasztott játékmódokat */
enum MENU
{
    LOAD_MENU   = 5,
    LOAD_SAVED  = 7,
    LOAD_GAME   = 9,
    NEW_GAME    = 11,
    MAP_CREATOR = 13,
    HIGH_SCORE  = 15,
    ABOUT       = 17,
    OPTIONS     = 19,
    EXIT        = 21,
    EXIT_SAVED  = 22,
    DONT_EXIT   = 23,
    LOAD_CREATED= 24,
    CONTINUE    = 0,
    STEPBACK    = -1,
};

/* a objektum mozgató függvény visszatérési értékei */
enum MOVE
{
    NOT_MOVED       = 0,
    MOVED           = 1,
    MOVED_WITH_BOX  = 2,
};

/* az objektumok kezelésére szolgál */
enum WALLS
{
    NOTHING             = '0',
    WALL                = '1',
    BOX                 = '2',
    FINISHZONE          = '3',
    BOX_IN_FINISHZONE   = '4',
    PLAYER              = '5',
    PLAYER_IN_FINISHZONE= '6',
};

/* a billentyű parancsok kezelésére szolgál */
enum KEYS
{
    UP      = 'w',
    DOWN    = 's',
    LEFT    = 'a',
    RIGHT   = 'd',
    CTRL_Z  =  26,
    ENTER   =  13,
    ESC     =  27,
    BCKSPC  =   8,
    RESTART = 'r',
};

/* az infoc-n letöltött econio header cursort kezelő enum-jai */
enum CURSOR
{
    NOCURSOR     =   0,
    SOLIDCURSOR  = 100,
    NORMALCURSOR =  20,
};

/* az infoc-n letöltött econio header színeket kezelő enum-jai */
enum COLORS
{
    BLACK           = 0,
    BLUE            = FOREGROUND_BLUE,
    GREEN           = FOREGROUND_GREEN,
    CYAN            = FOREGROUND_GREEN | FOREGROUND_BLUE,
    RED             = FOREGROUND_RED,
    MAGENTA         = FOREGROUND_RED   | FOREGROUND_BLUE,
    BROWN           = FOREGROUND_RED   | FOREGROUND_GREEN,
    DARKGRAY        = FOREGROUND_INTENSITY,
    LIGHTGRAY       = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE,
    LIGHTBLUE       = FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
    LIGHTGREEN      = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    LIGHTCYAN       = FOREGROUND_GREEN | FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
    LIGHTRED        = FOREGROUND_RED   | FOREGROUND_INTENSITY,
    LIGHTMAGENTA    = FOREGROUND_RED   | FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
    YELLOW          = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    WHITE           = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
};

/* két int tárolására szolgáló struktúra, általában koordináták tárolására használandó */
typedef struct coordinates
{
    int x;
    int y;

} coordinates;

/* nincs használatban */
typedef struct mapinfo
{
    coordinates mapsize;
    char **mapdata;

} mapinfo;

/* nincs használatban */
typedef struct listmap
{
    char *maptosave;
    struct listmap *previous;

} listmap;

/* ezzel lehet tárolni a toplistába kiirandó értékeket */
typedef struct scoreinfo
{
    char name[50];
    int level;
    int steps;
    int stepbacks;
} scoreinfo;

/* global változók a színek használatára,
 * azért lett global mert minden eggyes függvény megkapná paraméterként
 * és így egyszerűbb és logikusabb használni */
int COLOR, LIGHTCOLOR;

/* main.h */
void drawmenu( void );
void draw_outtermenu(int y);
int stepmenu(int y);

/* game_modes.h */
int newgame(int loader);
int exitgame(char *exitstate);
int exitmenu(char *exitstate);
void errorexit(int error);

/* game_cores.h */
int loadnewmap      (coordinates *Map, int loader, int *whichmap, char ***mapfinal, char **mapstart, int *steps, int *stepbackcounter);
int savemap         (char **maptosave, coordinates Map, int whichmap, int steps, int stepbackcounter);
int gamecore        (char **mapfinal, coordinates *Map, int whichmap, int *steps, char **savedmap, int stepbackcounter, int *stepbackenable);
void save_stepback  (char **savedmap, char **maptosave, coordinates Map);

/* game_main.h */
int move            (char **mapfinal, coordinates *Object, coordinates *Axis);
int drawresults     (char **mapfinal, coordinates *Map, int steps, int whichmap, int stepbackcounter);
char **drawmap      (char **mapfinal, coordinates *Map);
int keypressed      (char **mapfinal, coordinates *Map, coordinates *Axis, int *steps);
int searchplayer    (char **mapfinal, coordinates *Map, coordinates *Player);

/* map_creator.h */
int checker(char **maptocheck);
void create_map();
void map_creator_menu();

/* highscore.h */
void levelcomp(int steps, int stepbacks);
int gamecomp(FILE *openmap);
void savehighscore(int level, int steps, int stepbackcounter);
void highscore();

/* options.h */
void options();

/* about.h */
void about();

/* econio.h */
void clrscr( void );
void textbackground( int newcolor );
void textcolor( int newcolor );
void setcursortype( int cur );
void gotoxy( int x, int y );
int  wherex( void );
int  wherey( void );


#endif // HEADER_SOKOBAN_H_INCLUDED
