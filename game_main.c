#include "header_sokoban.h"

#define CurrentObject mapfinal[Object->x][Object->y]
#define NextObject mapfinal[Object->x+Axis->x][Object->y+Axis->y]
#define AWAY_FROM_MAP 3

/* FONTOS, a mozgatás itt történik, az algoritmus kezeli a játék fizikáját
 * majd visszatér az eseménnyel, ami történt: mozgott, nem mozgott, vagy dobozzal mozgott */
int move(char **mapfinal, coordinates *Object, coordinates *Axis)
{
    switch(NextObject)
    {
    case WALL:
        return NOT_MOVED;
        break;
    case NOTHING:
        if (CurrentObject == BOX || CurrentObject == BOX_IN_FINISHZONE)
        {
            NextObject = BOX;
            if(CurrentObject == BOX_IN_FINISHZONE) CurrentObject = FINISHZONE;
            else CurrentObject = NOTHING;
        }
        else
        {
            NextObject = PLAYER;
            if(CurrentObject == PLAYER_IN_FINISHZONE) CurrentObject = FINISHZONE;
            else CurrentObject = NOTHING;
        }
        break;
    case FINISHZONE:
        if (CurrentObject == BOX || CurrentObject == BOX_IN_FINISHZONE)
        {
            NextObject = BOX_IN_FINISHZONE;
            if (CurrentObject == BOX_IN_FINISHZONE) CurrentObject = FINISHZONE;
            else CurrentObject = NOTHING;
        }
        else
        {
            NextObject = PLAYER_IN_FINISHZONE;
            if (CurrentObject == PLAYER_IN_FINISHZONE) CurrentObject = FINISHZONE;
            else CurrentObject = NOTHING;
        }
        break;
    case BOX:
        if(CurrentObject == BOX || CurrentObject == BOX_IN_FINISHZONE) return NOT_MOVED;
    case BOX_IN_FINISHZONE:
        Object->x += Axis->x;
        Object->y += Axis->y;
        if(move(mapfinal,Object, Axis))
        {
            Object->x -= Axis->x;
            Object->y -= Axis->y;
            move(mapfinal,Object, Axis);
            return MOVED_WITH_BOX;
        }
        return NOT_MOVED;
    default:
        return NOT_MOVED;
    }

    return MOVED;
}

/* kiirja az eddigi eredményeket: hány doboz van a helyén, háy lépésnél tartunk,
 * hanyadik pályán vagyunk illetve hogy eddig hányszor léptünk vissza */
int drawresults(char **mapfinal, coordinates *Map, int steps, int whichmap, int stepbackcounter)
{
    int x,y;
    coordinates Finish = {0, 0};
    textcolor(LIGHTCOLOR);

    for(y = 0; y < Map->y; y++)
        for(x = 0; x < Map->x; x++)
        {
            if (mapfinal[y][x] == BOX)              Finish.x++;
            if (mapfinal[y][x] == BOX_IN_FINISHZONE)Finish.y++;
        }
    gotoxy(Map->x*2 + AWAY_FROM_MAP, 1);
    printf("STEPS:%3d", steps);
    gotoxy(Map->x*2 + AWAY_FROM_MAP, 3);
    if (LIGHTCOLOR == LIGHTMAGENTA) printf("BOXES IN LOVEZONES:  %d/%d", Finish.y, Finish.y + Finish.x);
    else                            printf("BOXES IN FINISHZONES:  %d/%d", Finish.y, Finish.y + Finish.x);
    gotoxy(Map->x*2 + AWAY_FROM_MAP, 5);
    if (LIGHTCOLOR == LIGHTMAGENTA) printf("LOVE-EL:%3d", whichmap + 1);
    else printf("LEVEL:%3d", whichmap + 1);
    gotoxy(Map->x*2 + AWAY_FROM_MAP, 7);
    printf("STEPBACKS USED:%3d", stepbackcounter);

    return Finish.x != 0;
}

/* FONTOS, egyszerűsége ellenére,
 * kirajzolja a pálya állását,
 * ezt használom a főmenu kirajzolásához, a játék kirajzolásához,
 * illetve a pálya készítővel készített pálya kirajzolásához */
char **drawmap(char **mapfinal, coordinates *Map)
{
    int x,y;
    srand(time(NULL));

    gotoxy(0, 0);
    for(y = 0; y < Map->y; y++)
    {
        for(x = 0; x < Map->x; x++)
        {
            switch(mapfinal[y][x])
            {
            case NOTHING:
                printf("  ");
                break;
            case WALL:
                textbackground(LIGHTCOLOR);
                textcolor(BLACK);
                switch (LIGHTCOLOR)
                {
                case LIGHTMAGENTA:
                    printf("<3");
                    break;
                case LIGHTGREEN:
                    printf("%d", rand()%90 + 10);
                    break;
                case LIGHTBLUE:
                    printf("~~");
                    break;
                case LIGHTRED:
                    printf("**");
                    break;
                case LIGHTCYAN:
                    printf("^^");
                    break;
                default:
                    printf("##");
                }
                textbackground(BLACK);
                textcolor(LIGHTCOLOR);
                break;
            case BOX:
                printf("[]");
                break;
            case FINISHZONE:
                printf("xx");
                break;
            case BOX_IN_FINISHZONE:
                printf("<>");
                break;
            case PLAYER:
                printf("oo");
                break;
            case PLAYER_IN_FINISHZONE:
                printf("00");
                break;
            default:
                textbackground(YELLOW);
                textcolor(BROWN);
                printf("ER");
                textbackground(BLACK);
                textcolor(LIGHTCOLOR);
                break;
            }
        }
        printf("\n");
    }

    return mapfinal;
}

/* FONTOS, a felhasználó által beütött billentyűket olvassa, majd visszatér
 * egy struktúrával, mely megadja merre kíván mozogni a játékos */
int keypressed(char **mapfinal, coordinates *Map, coordinates *Axis, int *steps)
{
    Axis->x = 0;
    Axis->y = 0;
    switch (getch())
    {
    case UP:
        Axis->x--;
        break;
    case DOWN:
        Axis->x++;
        break;
    case LEFT:
        Axis->y--;
        break;
    case RIGHT:
        Axis->y++;
        break;
    case ESC:
        return exitgame("Do you want to save the game ?");
    case BCKSPC:
    case CTRL_Z:
        return STEPBACK;
    case RESTART:
        return LOAD_SAVED;
    }
    return CONTINUE;
}

/* megkeresi a játékos pozícióját a pályán */
int searchplayer(char **mapfinal, coordinates *Map, coordinates *Player)
{
    for(Player->x = 0; Player->x < Map->y; Player->x++)
        for(Player->y = 0; Player->y < Map->x; Player->y++)
            if(mapfinal[Player->x][Player->y] == PLAYER || mapfinal[Player->x][Player->y] == PLAYER_IN_FINISHZONE) return 0;

    return 1;
}
