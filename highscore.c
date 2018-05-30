#include "header_sokoban.h"

#define AWAY_FROM_MAP 4

/* kiirja hogy kész a pálya */
void levelcomp(int steps, int stepbacks)
{
    clrscr();
    printf("Level completed with %d steps and %d stepbacks\n", steps, stepbacks);
}

/* kiirja hogy vége a játéknak nincs több pálya, majd kilép */
int gamecomp(FILE *openmap)
{
    clrscr();
    textcolor(LIGHTCOLOR);
    printf("Congratulations, you have completed all the maps available\nCheck back soon for more updates, and maps");
    fclose(openmap);
    getch();
    return EXIT;
}

/* lementi a toplistába az eredményt, illetve egy nevet, ha a felhasználó szeretné */
void savehighscore(int level, int steps, int stepbackcounter)
{
    FILE *highscore;
    scoreinfo current;

    switch(exitmenu("Do you want to save your highscore ?"))
    {
    case EXIT:
        clrscr();
        current.level = level;
        current.steps = steps;
        current.stepbacks = stepbackcounter;
        printf("Comments ? [max 50]: ");
        fgets(current.name, 50, stdin);
        strtok(current.name, "\n");

        highscore = fopen("highscore.cfg", "ab");
        if (highscore == NULL) errorexit(OPENING_HIGHSCORE_WRITE);
        fwrite(&current, sizeof(scoreinfo), 1, highscore);
        fclose(highscore);
        break;
    case CONTINUE:
        break;
    }

}
/* a toplistát kezelő függvény, kiirja az eddig lementett eredményeket */
void highscore()
{
    FILE *filehighscore;
    scoreinfo current;

    filehighscore = fopen("highscore.cfg", "rb");
    if (filehighscore == NULL) errorexit(OPENING_HIGHSCORE_READ);
    clrscr();

    textcolor(LIGHTCOLOR);
    printf("\tComments\tLevel\tSteps\tStepbacks\n");
    while(fread(&current, sizeof(scoreinfo), 1, filehighscore))
        printf("\n%20s\t%3d\t%4d\t%3d", current.name, current.level + 1, current.steps, current.stepbacks);

    getch();
    clrscr();
}
