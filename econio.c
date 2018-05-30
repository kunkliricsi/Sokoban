/* Az infoc-n található econio függvények összessége */

#include "header_sokoban.h"

static WORD bgcolor = BLACK << 4;
static WORD fgcolor = WHITE;

#define STDOUT GetStdHandle(STD_OUTPUT_HANDLE)

void gotoxy( int x, int y )
{
  COORD dwCursorPosition;
  dwCursorPosition.X = (SHORT) x;
  dwCursorPosition.Y = (SHORT) y;
  SetConsoleCursorPosition (STDOUT, dwCursorPosition);
}

int wherex( void )
{
  CONSOLE_SCREEN_BUFFER_INFO coninfo;
  GetConsoleScreenBufferInfo (STDOUT, &coninfo);
  return coninfo.dwCursorPosition.X;
}

int wherey( void )
{
  CONSOLE_SCREEN_BUFFER_INFO coninfo;
  GetConsoleScreenBufferInfo (STDOUT, &coninfo);
  return coninfo.dwCursorPosition.Y;
}

void textbackground( int newcolor )
{
  bgcolor = (WORD) (newcolor << 4);
  SetConsoleTextAttribute (STDOUT, fgcolor | bgcolor);
}

void textcolor( int newcolor )
{
  fgcolor = (WORD) newcolor;
  SetConsoleTextAttribute (STDOUT, fgcolor | bgcolor);
}

void setcursortype( int cur )
{
  CONSOLE_CURSOR_INFO CursorInfo;
  CursorInfo.dwSize = cur;
  CursorInfo.bVisible = cur != NOCURSOR;
  SetConsoleCursorInfo (STDOUT, &CursorInfo);
}

void clrscr( void )
{
  HANDLE hstdout = STDOUT;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  if (GetConsoleScreenBufferInfo (hstdout, &csbi))
  {
    COORD coordScreen = { 0, 0 };
    DWORD cCharsWritten;
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter (hstdout, ' ', dwConSize, coordScreen, &cCharsWritten);
    FillConsoleOutputAttribute (hstdout, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
    SetConsoleCursorPosition   (hstdout, coordScreen);
  }
}


