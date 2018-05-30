#include "header_sokoban.h"

/* az uj jaték kezdete függvény, megkapja melyik játék módot töltse be
 * majd betölti az ahhoz tartózó pályát, elindítja a játékot, majd
 * a játék vissza térési értéke alapján dolgozik, mely lehet
 * uj játék kezdete, kilépés, vissza lépés, kilépés mentéssel,
 * vagy anélkül, illetve a pálya újrakezdése */
int newgame(int loader)
{
    clrscr();
    char **finalmap = NULL, *startermap = NULL, *savedmap = NULL;
    coordinates Map;
    int whichmap = 0, steps = 0, stepbackenable = 0, stepbackcounter = 0;

    if (loadnewmap(&Map, loader, &whichmap, &finalmap, &startermap, &steps, &stepbackcounter) == EXIT) return EXIT;

    while(1)
    {
        switch(gamecore(finalmap, &Map, whichmap, &steps, &savedmap, stepbackcounter, &stepbackenable))
        {
        case STEPBACK:
            if(savedmap != NULL && stepbackenable != 0)
            {
                steps--;
                stepbackenable = 0;
                stepbackcounter++;
                loadnewmap(&Map, LOAD_MENU, &whichmap, &finalmap, &savedmap, &steps, &stepbackcounter);
            }
            break;
        case LOAD_SAVED:
            free(savedmap);
            savedmap = NULL;
            free(startermap);
            steps = 0;
            stepbackcounter = 0;
            if (loadnewmap(&Map, loader, &whichmap, &finalmap, &startermap, &steps, &stepbackcounter) == EXIT) return EXIT;
            break;
        case NEW_GAME:
            free(savedmap);
            savedmap = NULL;
            if (loader == LOAD_GAME) loader = NEW_GAME;
            steps = 0;
            stepbackcounter = 0;
            free(*finalmap);
            free(finalmap);
            free(startermap);
            whichmap++;
            if (loadnewmap(&Map, loader, &whichmap, &finalmap, &startermap, &steps, &stepbackcounter) == EXIT) return EXIT;
            clrscr();
            break;
        case EXIT_SAVED:
            savemap(finalmap, Map, whichmap, ++steps, stepbackcounter);
        case EXIT:
            free(savedmap);
            free(*finalmap);
            free(finalmap);
            free(startermap);
            clrscr();
            return 0;
        }
    }

    return 1;
}

/* játék kilépő függvény, egy szöveget kap melyet kiiír,
 * majd a felhasználó válasza alapján dob egy vissza térési értéket */
int exitgame(char *exitstate)
{
    int y = 0;
    printf("\n\n");

    while(1)
    {
        textcolor(LIGHTCOLOR);
        printf("\rGAME MENU:");
        printf("  ");
        textcolor(LIGHTCOLOR);
        textbackground(BLACK);
        if (y == 0)
        {
            textcolor(BLACK);
            textbackground(LIGHTCOLOR);
        }
        printf("Exit");
        textcolor(LIGHTCOLOR);
        textbackground(BLACK);
        printf("    ");
        if (y == 1)
        {
            textcolor(BLACK);
            textbackground(LIGHTCOLOR);
        }
        printf("Cancel");
        textcolor(LIGHTCOLOR);
        textbackground(BLACK);
        printf("    ");
        if (y == 2)
        {
            textcolor(BLACK);
            textbackground(LIGHTCOLOR);
        }
        printf("Restart");
        textcolor(LIGHTCOLOR);
        textbackground(BLACK);
        switch(getch())
        {
        case ENTER:
            if (y == 2)
            {
                printf("\r                                                       ");
                return LOAD_SAVED;
            }
            if (y == 1)
            {
            case ESC:
            case BCKSPC:
                printf("\r                                                       ");
                return CONTINUE;
            }
            if (y == 0)
            {
                switch(exitmenu(exitstate))
                {
                case EXIT:
                    return EXIT_SAVED;
                case DONT_EXIT:
                    return EXIT;
                case CONTINUE:
                    break;
                }
            }
            break;
        case LEFT:
            if (y == 0) y = 2;
            else y--;
            break;
        case RIGHT:
            if (y == 2) y = 0;
            else y++;
            break;
        }
    }

    return EXIT;
}

/* hasonló a játék kilépő függvényhez, annyi különbséggel hogy ez univerzálisan,
 * nem csak a játékon belül érdemes használni, mert egy igen nem kérdésre ad választ */
int exitmenu(char *exitstate)
{
    int y = 0;

    while(1)
    {
        textcolor(LIGHTCOLOR);
        printf("\r%s\t", exitstate);
        textcolor(LIGHTCOLOR);
        textbackground(BLACK);
        if (y == 0)
        {
            textcolor(BLACK);
            textbackground(LIGHTCOLOR);
        }
        printf("Yes");
        textcolor(LIGHTCOLOR);
        textbackground(BLACK);
        printf("\t");
        if (y == 1)
        {
            textcolor(BLACK);
            textbackground(LIGHTCOLOR);
        }
        printf("No");
        textcolor(LIGHTCOLOR);
        textbackground(BLACK);
        switch(getch())
        {
        case ENTER:
            printf("\r\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
            if (y == 0) return EXIT;
            if (y == 1) return DONT_EXIT;
        case ESC:
        case BCKSPC:
            printf("\r\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
            return CONTINUE;
        case LEFT:
            y = 0;
            break;
        case RIGHT:
            y = 1;
            break;
        }
        printf("\r\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
    }
    return EXIT;
}

/* hiba kezelő függvény, egy enum értéket kap
 * ha hiba van kiirja a hibakódot, majd gombnyomásra kilép */
void errorexit(int error)
{
    clrscr();
    textcolor(LIGHTCOLOR);
    printf("Error: %d[enum]", error);
    getch();
    exit(error);
}



