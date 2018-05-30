#include "header_sokoban.h"

/* beállításokat lehet vele kezelni, jelenleg a témákat(színeket) lehet változtatni */
void options()
{
    int color = 0, savecolor = COLOR, savelightcolor = LIGHTCOLOR;
    COLOR = CYAN;
    LIGHTCOLOR = LIGHTCYAN;

    while(1)
    {
        gotoxy(15, 19);
        textcolor(LIGHTCOLOR);
        printf("Change Game Theme");
        gotoxy(15, 21);
        if(color == 0)  textcolor(LIGHTCOLOR);
        else textcolor(COLOR);
        printf("Moonlight   ");
        if(color == 1)  textcolor(LIGHTCOLOR);
        else textcolor(COLOR);
        printf("Ocean   ");
        if(color == 2)  textcolor(LIGHTCOLOR);
        else textcolor(COLOR);
        printf("Classic   ");
        if(color == 3)  textcolor(LIGHTCOLOR);
        else textcolor(COLOR);
        printf("Matrix   ");
        if(color == 4)  textcolor(LIGHTCOLOR);
        else textcolor(COLOR);
        printf("Bloody   ");
        if(color == 5)  textcolor(LIGHTCOLOR);
        else textcolor(COLOR);
        printf("Mariann   ");
        drawmenu();
        draw_outtermenu(OPTIONS);

        switch(getch())
        {
        case ESC:
        case BCKSPC:
            COLOR = savecolor;
            LIGHTCOLOR = savelightcolor;
        case ENTER:
            gotoxy(15, 19);
            printf("\t\t\t");
            gotoxy(15, 21);
            printf("\t\t\t\t\t\t\t\t\t\t");
            return;
        case LEFT:
            if (color == 0) color = 5;
            else color--;
            break;
        case RIGHT:
            if (color == 5) color = 0;
            else color++;
            break;
        }
        switch(color)
        {
        case 0:
            COLOR = CYAN;
            LIGHTCOLOR = LIGHTCYAN;
            break;
        case 1:
            COLOR = BLUE;
            LIGHTCOLOR = LIGHTBLUE;
            break;
        case 2:
            COLOR = DARKGRAY;
            LIGHTCOLOR = LIGHTGRAY;
            break;
        case 3:
            COLOR = GREEN;
            LIGHTCOLOR = LIGHTGREEN;
            break;
        case 4:
            COLOR = RED;
            LIGHTCOLOR = LIGHTRED;
            break;
        case 5:
            COLOR = MAGENTA;
            LIGHTCOLOR = LIGHTMAGENTA;
            break;

        }
    }
}
