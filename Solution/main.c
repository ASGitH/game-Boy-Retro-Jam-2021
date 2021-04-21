#include <gb/gb.h>

#include "gameConfiguration.h"

int main(){
    initializeGame();

    while (TRUE) { gameCoreLoop(); }
    
    return 0;
}