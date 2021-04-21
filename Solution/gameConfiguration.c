#include "gameConfiguration.h"

#include "backgrounds/headsUpDisplayMB.h"

#include "headsUpDisplay.h"

#include "guard.h"
#include "player.h"

#include "projectile.h"

#include "rand.h"

#include "sprites/fontTD.h"

struct player playerS;

unsigned int seed = 0;

void gameCoreLoop()
{
    player_core_loop(&playerS);

    projectileCoreLoop();

    guardCoreLoop();

    updateHUD();

    performatdelay(1);
}

void initializeHUD()
{
    set_win_tiles(0, 0, 20, 2, headsUpDisplayMap);

    move_win(7, 124);
}

void performatdelay(UINT8 numloops)
{
    UINT8 i;

    for (i = 0; i < numloops; i++) { wait_vbl_done(); }
}

void textLoadFont() 
{ 
    set_bkg_data(0, 49, (unsigned char *)fontSprites); 

    UINT8 offset_x = 0;
    UINT8 offset_y = 0;

    UINT16 clearBackground = 0;

    char blankTile = ' ';

    for(clearBackground = 0; clearBackground < 360; clearBackground++)
    {
        set_bkg_tiles(offset_x, offset_y, 1, 1, (unsigned char *)blankTile);

        offset_x += 1;

        if(offset_x >= 20) { offset_x = 0; offset_y += 1; }
    }
}

void textPrintCharBkgOrWin(UINT8 x, UINT8 y, char bkgOrWin, unsigned char chr) 
{
    UINT8 tile = 46;

    if (chr >= 'a' && chr <= 'z') { tile = 1 + chr - 'a'; } 
    else if (chr >= 'A' && chr <= 'Z') { tile = 1 + chr - 'A'; } 
    else if (chr >= '0' && chr <= '9') { tile = 27 + chr - '0'; } 
    else {
        switch (chr) 
        {
            case ' ': tile = 0; break;
            case ':': tile = 41; break;
            case '!': tile = 42; break;
            case ')': tile = 45; break;
        }
    }
    
    if(bkgOrWin != 'b') { set_win_tiles(x, y, 1, 1, &tile); }
    else { set_bkg_tiles(x, y, 1, 1, &tile); }
}

void textPrintStringBkgOrWin(UINT8 x, UINT8 y, char bkgOrWin, unsigned char *string) 
{
    UINT8 offset_x = 0;
    UINT8 offset_y = 0;

    while (string[0]) 
    {
        if (string[0] == '\n') {
            offset_x = 0;
            offset_y += 1;
        } 
        else 
        {
            textPrintCharBkgOrWin(x + offset_x, y + offset_y, bkgOrWin, (unsigned char) string[0]);

            offset_x += 1;
        }

        string += 1;
    }
}

void initializeGame()
{
    textLoadFont();

    initrand(seed);

    initializeHUD();

    SHOW_BKG;
    SHOW_SPRITES;
    SHOW_WIN;

    DISPLAY_ON;
}