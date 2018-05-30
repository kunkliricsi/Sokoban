#include "header_sokoban.h"

/* információkat ír ki a játékról, a készítőről, és egyéb hasznos adatokat */
void about()
{
    clrscr();

    textcolor(LIGHTCOLOR);
    printf("This game was made by Kunkli Richard, for a school project in november of 2015.\n"
           "\nInstructions:\n"
           "\n\t 1) Movement:\t\t- Move your character with w(up), a(left), s(down), d(right)\n"
           "\n\t 2) Special Moves:\t- To Step backwards, press 'Ctrl + z', which moves you back one step.\n"
           "                    \t\t- To Restart the game, you can press 'r' or hit Esc and select Restart.\n"
           "\n\t 3) In-game menu:\t- Press Esc to enter the in-game menu, which brings you to three options.\n"
           "                    \t\t\to Save and Exit, which saves your last progress, then quits.\n"
           "                    \t\t\to Cancel, so you continue playing.\n"
           "                    \t\t\to Restart, which restarts the last map.\n"
           "\n\t 4) Goal:       \t- The goal of the game is to push all boxes into the finish zones,\n"
           "                    \t\twith as few steps and stepbacks as you can.\n"
           "\n\t 5) Setting:\t\t- In the settings menu, you can change the color of the game to:\n\t\t\t\t(");
    textcolor(LIGHTCYAN);
    printf(" Cyan, ");
    textcolor(LIGHTBLUE);
    printf("Blue, ");
    textcolor(LIGHTGRAY);
    printf("Gray, ");
    textcolor(LIGHTGREEN);
    printf("Green, ");
    textcolor(LIGHTRED);
    printf("Red, ");
    textcolor(LIGHTMAGENTA);
    printf("Magenta ");
    textcolor(LIGHTCOLOR);
    printf(")\nModels:\n"
           "\t Player:\t\too\n"
           "\t Box:\t\t\t[]\n"
           "\t Finishzone:\t\txx\n"
           "\t Player in finishzone:\t00\n"
           "\t Box in finishzone\t<>\n"
           "\t Wall:\t\t\t");
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
        printf("÷÷");
        break;
    case LIGHTCYAN:
        printf("^^");
        break;
    default:
        printf("##");
    }
    textbackground(BLACK);
    textcolor(LIGHTCOLOR);

    getch();
    clrscr();
}
