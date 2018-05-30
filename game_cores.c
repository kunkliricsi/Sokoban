#include "header_sokoban.h"

/* a pálya betoltő függvény, feltölti a játékhoz szükkséges váltózokat a megfelelő adattal
 * a megadott játékmódtól függően */
int loadnewmap(coordinates *Map, int loader, int *whichmap, char ***mapfinal, char **mapstart, int *steps, int *stepbackcounter)
{
    int i,j,k;
    if (loader != LOAD_MENU)
    {
        FILE *openmap;

        if (loader == NEW_GAME)
        {
            openmap = fopen("maps.cfg", "rt");
            if (openmap == NULL) errorexit(OPENING_MAPS);
        }
        if (loader == LOAD_GAME)
        {
            openmap = fopen("loaded_map.cfg", "rt");
            fscanf(openmap, "%d %d %d", whichmap, steps, stepbackcounter);
            if (openmap == NULL) errorexit(OPENING_LOADED_MAPS);
        }
        if (loader == LOAD_CREATED)
        {
            openmap = fopen("created_maps.cfg", "rt");
            if (openmap == NULL) errorexit(OPENING_CREATED_MAPS);
            *whichmap = 0;
        }
        for (i = 0; i <= *whichmap; i++)
        {
            if (fscanf(openmap, "%d %d", &Map->x, &Map->y) != 2) return gamecomp(openmap);
            *mapstart = (char *)malloc(Map->y * Map->x * sizeof(char) + 1);
            if (*mapstart == NULL) errorexit(ONE_DIM_ARRAY_MALLOC);
            fscanf(openmap, "%s", *mapstart);
            if (loader == LOAD_GAME) break;
        }
        fclose(openmap);
    }
    if (loader != LOAD_SAVED)
    {
        *mapfinal = (char**)malloc(Map->y * sizeof(char*));
        if (*mapfinal == NULL)
            errorexit(TWO_DIM_ARRAY_MALLOC1);

        **mapfinal = (char*)malloc(Map->y * Map->x * sizeof(char));
        if (**mapfinal == NULL)
            errorexit(TWO_DIM_ARRAY_MALLOC2);
    }


    for (i = 0; i < Map->y; i++)
        (*mapfinal)[i] = **mapfinal + i * (Map->x);
    for(j = 0; j < Map->y; j++)
        for(i = j * (Map->x), k = 0; i < (j+1) * (Map->x); i++)
            (*mapfinal)[j][k++] = (*mapstart)[i];

    return 0;
}

/* a játékot kezelő függvény, kezeli a
 * kirajzolást, a billentyűzet beolvasását,
 * a sikeres pálya megoldást, a visszalépést,
 * a player obbjektum keresését, a toplistát
 * és a objektumok mozgatásáért felelős függvényt */
int gamecore(char **mapfinal, coordinates *Map, int whichmap, int *steps, char **savedmap, int stepbackcounter, int *stepbackenable)
{
    coordinates Player, Axis;
    int moved = MOVED;

    while(drawresults(mapfinal, Map, *steps, whichmap, stepbackcounter))
    {
        drawmap(mapfinal, Map);
        switch (keypressed(mapfinal, Map, &Axis, steps))
        {
        case STEPBACK:
            return STEPBACK;
        case EXIT_SAVED:
            return EXIT_SAVED;
        case EXIT:
            return EXIT;
        case LOAD_SAVED:
            return LOAD_SAVED;
        }
        free(*savedmap);
        save_stepback(savedmap, mapfinal, *Map);
        searchplayer(mapfinal, Map, &Player);
        if (moved = move(mapfinal, &Player, &Axis))
        {
            (*steps)++;
            *stepbackenable = 1;
        }
    }
    drawmap(mapfinal, Map);
    Sleep(300);
    levelcomp(*steps, stepbackcounter);
    savehighscore(whichmap, *steps, stepbackcounter);

    return NEW_GAME;
}

/* lementi az eddig módosított pálya állását fájlba */
int savemap(char **maptosave, coordinates Map, int whichmap, int steps, int stepbackcounter)
{
    int i, j;
    FILE *savefile;
    savefile = fopen("loaded_map.cfg", "wt");
    if (savefile == NULL) errorexit(SAVING_TO_LOADED_MAPS);
    fprintf(savefile, "%d %d %d %d %d ", whichmap, steps, stepbackcounter, Map.x, Map.y);
    for(i = 0; i < Map.y; i++)
        for(j = 0; j < Map.x; j++)
            fprintf(savefile, "%c", maptosave[i][j]);

    fclose(savefile);

    return 0;
}

/* lementi a pálya előző lépésének állását a visszalépéshez */
void save_stepback(char **savedmap, char **maptosave, coordinates Map)
{
    int i,j,k;

    *savedmap = (char*)malloc(Map.x * Map.y * sizeof(char));
    if (*savedmap == NULL) errorexit(SAVING_MAP_LIST_MALLOC);

    for (i = 0, k = 0; i < Map.y; i++)
        for(j = 0; j < Map.x; j++, k++)
            (*savedmap)[k] = maptosave[i][j];
}
