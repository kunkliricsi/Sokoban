/*
 * Partial port of Borland conio.h for Windows
 *
 *  Eric Tetz, 2001.
 *
 *  Public domain software (i.e. do whatever you want with it.
 */

#ifndef ECONIO_H
#define ECONIO_H

#include <windows.h>

enum CURSOR {
    NOCURSOR     =   0,
    SOLIDCURSOR  = 100,
    NORMALCURSOR =  20,
};

enum COLORS {
    BLACK           = 0,
    BLUE            = FOREGROUND_BLUE,
    GREEN           = FOREGROUND_GREEN,
    CYAN            = FOREGROUND_GREEN | FOREGROUND_BLUE,
    RED             = FOREGROUND_RED,
    MAGENTA         = FOREGROUND_RED   | FOREGROUND_BLUE,
    BROWN           = FOREGROUND_RED   | FOREGROUND_GREEN,
    LIGHTGRAY       = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE,
    DARKGRAY        = FOREGROUND_INTENSITY,
    LIGHTBLUE       = FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
    LIGHTGREEN      = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    LIGHTCYAN       = FOREGROUND_GREEN | FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
    LIGHTRED        = FOREGROUND_RED   | FOREGROUND_INTENSITY,
    LIGHTMAGENTA    = FOREGROUND_RED   | FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
    YELLOW          = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    WHITE           = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
};

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void clrscr( void );
void textbackground( int newcolor );
void textcolor( int newcolor );
void setcursortype( int cur );
void gotoxy( int x, int y );
int  wherex( void );
int  wherey( void );

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ECONIO_H
