#include "headsUpDisplay.h"

#include "gameConfiguration.h"

BOOLEAN hasTimerRanOut = FALSE;

char lifeCounter = '3';
char timerMinuteCounter = '3';
char timerSecondOnesCounter = '0';
char timerSecondTensCounter = '0';

UINT8 delayTimer = 0;

// unsigned char *unsignedCharTimerSecondCounter = (unsigned char *)"60";

void updateHUD()
{
    delayTimer += 1;

    if(delayTimer >= 60) 
    { 
        // lifeCounter -= 1; 
        
        if(lifeCounter == '0') { lifeCounter = '3'; }

        if(!hasTimerRanOut)
        {
            if(timerSecondOnesCounter != '0') { timerSecondOnesCounter -= 1; }
            else 
            { 
                if(timerMinuteCounter == '0' && timerSecondOnesCounter == '0' && timerSecondTensCounter == '0') { hasTimerRanOut = TRUE; }
                else
                {
                    timerSecondOnesCounter = '9'; 

                    if(timerSecondTensCounter != '0') { timerSecondTensCounter -= 1; }
                    else 
                    { 
                        timerSecondTensCounter = '5'; 
                    
                        if(timerMinuteCounter != '0') { timerMinuteCounter -= 1; }
                    } 
                }
            }
        }

        delayTimer = 0; 
    }

    textPrintCharBkgOrWin(2, 1, 'w', lifeCounter);
    textPrintCharBkgOrWin(9, 1, 'w', timerMinuteCounter);
    textPrintCharBkgOrWin(12, 1, 'w', timerSecondOnesCounter);
    textPrintCharBkgOrWin(11, 1, 'w', timerSecondTensCounter);
}