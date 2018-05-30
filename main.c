#include "header_sokoban.h"

/* kirajzolja a SOKOBAN feliratot */
void drawmenu()
{
    char **menuptr, *imgptr, menuimg[] = "111101111010010111101111001100100010100101001010010100101001010010110010100001001010100100101001010010101010111101001011000100101111011110101010000101001010100100101001010010101010100101001010010100101001010010100110111101111010010111101111010010100010";
    imgptr = &menuimg[0];
    coordinates Menu = {36, 7};

    loadnewmap(&Menu, LOAD_MENU, 0, &menuptr, &imgptr, NULL, NULL);
    drawmap(menuptr, &Menu);

    free(menuptr[0]);
    free(menuptr);
}

/* kirajzolja a menupontokat, kap egy értéket
 * amely azt mutatja melyik menupontot választaná jelenleg a felhasználó
 * és azt kivilágítja, hogy látható legyen */
void draw_outtermenu(int y)
{
    gotoxy(0, 9);
    if (y == LOAD_GAME) textcolor(LIGHTCOLOR);
    else textcolor(COLOR);
    printf(" 1) Resume Game\n\n");
    if (y == NEW_GAME) textcolor(LIGHTCOLOR);
    else textcolor(COLOR);
    printf(" 2) New Game\n\n");
    if (y == MAP_CREATOR) textcolor(LIGHTCOLOR);
    else textcolor(COLOR);
    printf(" 3) Map Creator\n\n");
    if (y == HIGH_SCORE) textcolor(LIGHTCOLOR);
    else textcolor(COLOR);
    printf(" 4) HighScores\n\n");
    if (y == ABOUT) textcolor(LIGHTCOLOR);
    else textcolor(COLOR);
    printf(" 5) About\n\n");
    if (y == OPTIONS) textcolor(LIGHTCOLOR);
    else textcolor(COLOR);
    printf(" 6) Settings\n\n");
    if (y == EXIT) textcolor(LIGHTCOLOR);
    else textcolor(COLOR);
    printf(" 7) Exit\n\n");

}

/* ezzel lehet léptetni a menut, szintén megkapja
 * a jelenlegi menupont helyét, így tudja mikor ér a végére,
 * ha a felhasználó entert nyom, kiválasztja a menupontot
 * akkor visszatér a menüpont helyének értékével */
int stepmenu(int y)
{
    while(1)
    {
        draw_outtermenu(y);
        switch(getch())
        {
        case '1':
            y = LOAD_GAME;
            break;
        case '2':
            y = NEW_GAME;
            break;
        case '3':
            y = MAP_CREATOR;
            break;
        case '4':
            y = HIGH_SCORE;
            break;
        case '5':
            y = ABOUT;
            break;
        case '6':
            y = OPTIONS;
            break;
        case '7':
            y = EXIT;
            break;
        case UP:
            if (y == LOAD_GAME) y = EXIT;
            else y -= 2;
            break;
        case DOWN:
            if (y == EXIT) y = LOAD_GAME;
            else y += 2;
            break;
        case ENTER:
            return y;
        case ESC:
            y = EXIT;
            draw_outtermenu(y);
            return y;
        }
    }
}

/* a main függvény, a menupontok kiválasztása után
 * meghívja a megfelelő függvényeket */
int main()
{
    int y = LOAD_GAME;
    COLOR = CYAN;
    LIGHTCOLOR = LIGHTCYAN;
    while(1)
    {
        drawmenu();
        switch(stepmenu(y))
        {
        case NEW_GAME:
            newgame(NEW_GAME);
            y = NEW_GAME;
            break;
        case LOAD_GAME:
            newgame(LOAD_GAME);
            y = LOAD_GAME;
            break;
        case MAP_CREATOR:
            map_creator_menu();
            y = MAP_CREATOR;
            break;
        case HIGH_SCORE:
            highscore();
            y = HIGH_SCORE;
            break;
        case ABOUT:
            about();
            y = ABOUT;
            break;
        case OPTIONS:
            options();
            y = OPTIONS;
            break;
        case EXIT:
            if (exitmenu("DO YOU REALLY WANT TO EXIT ?") == EXIT) return 0;
            y = EXIT;
            break;
        }
    }

    return 0;
}
