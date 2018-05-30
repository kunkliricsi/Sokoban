#include "header_sokoban.h"

#define MAX_MAP_Y 25
#define MAX_MAP_X 25

/* leellenőrzi hogy végig csinálható lenne-e a pálya
 * megnézi hány doboz illetve cél zóna van a pályán,
 * ezeknek egyenlőnek kell lenniük,
 * illetve hogy van-e egy játékos a pályán */
int checker(char **maptocheck)
{
    int i, j, boxes = 0, finishzones = 0, players = 0;

    for(i = 0; i < MAX_MAP_Y; i++)
        for(j = 0; j < MAX_MAP_X; j++)
        {
            if (maptocheck[i][j] == BOX) boxes++;
            else if (maptocheck[i][j] == FINISHZONE) finishzones++;
            else if (maptocheck[i][j] == PLAYER || maptocheck[i][j] == PLAYER_IN_FINISHZONE) players++;
        }

    return finishzones != 0 && boxes != 0 && finishzones == boxes && players == 1;
}

/* a pálya készítésére alkalmas függvény, vizsgálja a gomb nyomásokat, majd ez alapján léptet rajzol és kilép */
void create_map()
{
    FILE *savecreatedmap;
    char **maptodraw, chartowrite = WALL;
    coordinates tempmap = {0, 0}, maxmap = {MAX_MAP_X, MAX_MAP_Y};
    int i, j, k;
    clrscr();


    maptodraw = (char**)malloc(maxmap.y * sizeof(char*));
    if (maptodraw == NULL)  errorexit(TWO_DIM_ARRAY_MALLOC3);

    *maptodraw = (char*)malloc(maxmap.y * maxmap.x * sizeof(char));
    if (*maptodraw == NULL) errorexit(TWO_DIM_ARRAY_MALLOC4);

    for (i = 0; i < maxmap.y; i++)
        maptodraw[i] = *maptodraw + i * maxmap.x;
    for(j = 0; j < maxmap.y; j++)
        for(i = j * maxmap.x, k = 0; i < (j+1) * maxmap.x; i++)
            maptodraw[j][k++] = NOTHING;
    while(1)
    {
        drawmap(maptodraw, &maxmap);
        gotoxy(tempmap.x * 2, tempmap.y);
        textbackground(YELLOW);
        printf("  ");
        textbackground(BLACK);
        switch(getch())
        {
        case NOTHING:
            chartowrite = NOTHING;
            break;
        case WALL:
            chartowrite = WALL;
            break;
        case BOX:
            chartowrite = BOX;
            break;
        case FINISHZONE:
            chartowrite = FINISHZONE;
            break;
        case BOX_IN_FINISHZONE:
            chartowrite = BOX_IN_FINISHZONE;
            break;
        case PLAYER:
            chartowrite = PLAYER;
            break;
        case PLAYER_IN_FINISHZONE:
            chartowrite = PLAYER_IN_FINISHZONE;
            break;
        case ENTER:
            maptodraw[tempmap.y][tempmap.x] = chartowrite;
            break;
        case RIGHT:
            if (tempmap.x != MAX_MAP_X)  tempmap.x++;
            break;
        case UP:
            if (tempmap.y) tempmap.y--;
            break;
        case DOWN:
            if (tempmap.y != MAX_MAP_Y)  tempmap.y++;
            break;
        case LEFT:
            if (tempmap.x) tempmap.x--;
            break;
        case ESC:
            gotoxy(0, maxmap.y + 1);
            switch(exitgame("Do you want to exit and save the created map ?"))
            {
            case EXIT:
                free(*maptodraw);
                free(maptodraw);
                return;
            case EXIT_SAVED:
                if (checker(maptodraw))
                {
                    savecreatedmap = fopen("created_maps.cfg", "wt");
                    if (savecreatedmap == NULL) errorexit(OPENING_CREATEDMAP_WRITE);
                    fprintf(savecreatedmap, "%d %d ", maxmap.x, maxmap.y);
                    for(i = 0; i < maxmap.y; i++)
                        for(j = 0; j < maxmap.x; j++)
                            fprintf(savecreatedmap,"%c", maptodraw[i][j]);
                    fclose(savecreatedmap);
                    free(*maptodraw);
                    free(maptodraw);
                    return;
                }
            case CONTINUE:
                break;
            case LOAD_SAVED:
                for (i = 0; i < maxmap.y; i++)
                    maptodraw[i] = *maptodraw + i * maxmap.x;
                for(j = 0; j < maxmap.y; j++)
                    for(i = j * maxmap.x, k = 0; i < (j+1) * maxmap.x; i++)
                        maptodraw[j][k++] = NOTHING;
                tempmap.x = 0;
                tempmap.y = 0;
                break;
            }
            break;
        default:
            chartowrite = WALL;
        }
    }
}

/* a pálya készítő menüje */
void map_creator_menu()
{
    int menu = 0;
    while(1)
    {
        gotoxy(20, MAP_CREATOR);
        textcolor(LIGHTCOLOR);
        printf("Do you want to:   ");
        if (!menu) textcolor(LIGHTCOLOR);
        else textcolor(COLOR);
        printf("Load created map   ");
        textcolor(COLOR);
        printf("or   ");
        if (menu) textcolor(LIGHTCOLOR);
        else textcolor(COLOR);
        printf("Create a new map");

        switch(getch())
        {
        case LEFT:
            menu = 0;
            break;
        case RIGHT:
            menu = 1;
            break;
        case ENTER:
            clrscr();
            if (!menu)
            {
                newgame(LOAD_CREATED);
            }
            if (menu) return create_map();
        case ESC:
            gotoxy(20, MAP_CREATOR);
            printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
            return;
        }
    }
}
