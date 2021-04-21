#ifndef GAME_CONFIGURATION_H
#define GAME_CONFIGURATION_H

#include <gb/gb.h>

void gameCoreLoop();

void performatdelay(UINT8);

void textLoadFont();

void textPrintCharBkgOrWin(UINT8 x, UINT8 y, char bkgOrWin, unsigned char chr);

void textPrintStringBkgOrWin(UINT8 x, UINT8 y, char bkgOrWin, unsigned char *string);

void initializeGame();

void initializeHUD();

#endif