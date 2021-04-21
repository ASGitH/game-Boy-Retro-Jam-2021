#include "guard.h"

#include "gameConfiguration.h"

#include "player.h"

#include "rand.h"

#include "sprites/guardTD.h"

#include "stdio.h"

struct guard guards[1];

BOOLEAN haveGuardsBeenInitialized = FALSE;

UINT8 guardDelayTimer = 0;
UINT8 guardLoopCounter = 0;
UINT8 guardReacationTimer = 0;
UINT8 guardMetaSpriteInUse = 53;
UINT8 guardsArrayLength = 1;

BOOLEAN guardInitialization()
{
    haveGuardsBeenInitialized = TRUE;

    set_sprite_data(47, 32, guardSprites);

    UINT8 loopCounter = 0;

    for(loopCounter = 0; loopCounter < guardsArrayLength; loopCounter++)
    {
        guards[loopCounter].directionIsFacing = 0;

        guards[loopCounter].hasDetectedPlayer = FALSE;
        guards[loopCounter].hasGuardBeenHit = FALSE;
        guards[loopCounter].hasGuardBeenIntialized = TRUE;
        guards[loopCounter].isAttacking = FALSE;
        guards[loopCounter].isChasingPlayer = FALSE;
        guards[loopCounter].isFacingLeft = TRUE;
        guards[loopCounter].isFacingRight = FALSE;

        guards[loopCounter].jumping = 0;

        guards[loopCounter].indexTopLeftX = 0;
        guards[loopCounter].indexTopLeftY = 0;
        guards[loopCounter].tileIndexTopLeft = 0;

        guards[loopCounter].guardPosition[0] = 120;
        guards[loopCounter].guardPosition[1] = 72;
    }

    set_sprite_tile(8, 48);
    move_sprite(8, guards[loopCounter].guardPosition[0], guards[loopCounter].guardPosition[1]);

    set_sprite_tile(9, 49);
    move_sprite(9, guards[loopCounter].guardPosition[0] + 8, guards[loopCounter].guardPosition[1]);

    set_sprite_tile(10, 50);
    move_sprite(10, guards[loopCounter].guardPosition[0], guards[loopCounter].guardPosition[1] + 8);

    set_sprite_tile(11, 51);
    move_sprite(11, guards[loopCounter].guardPosition[0] + 8, guards[loopCounter].guardPosition[1] + 8);

    return TRUE;
}

BOOLEAN guardDetection(struct guard *_guard, UINT8 distance)
{
    if(playerPosition[0] - _guard->guardPosition[0] < distance && !_guard->isFacingLeft) { _guard->hasDetectedPlayer = TRUE; }
    else if(_guard->guardPosition[0] - playerPosition[0] < distance && _guard->isFacingLeft) { _guard->hasDetectedPlayer = TRUE; }
    else if(_guard->guardPosition[0] - playerPosition[0] > distance && playerPosition[0] - _guard->guardPosition[0] > distance) { _guard->hasDetectedPlayer = FALSE; _guard->isChasingPlayer = FALSE; }

    if(!_guard->isChasingPlayer)
    {
        if(!_guard->hasDetectedPlayer) { guardReacationTimer = 0; set_sprite_tile(12, 0); }
        else
        {
            guardReacationTimer += 1;

            set_sprite_tile(12, 78);
            move_sprite(12, _guard->guardPosition[0] + 4, _guard->guardPosition[1] - 8);

            if(guardReacationTimer >= 64) 
            { 
                _guard->isChasingPlayer = TRUE;

                guardReacationTimer = 0; 

                set_sprite_tile(12, 0);
            }
        }
    }

    return _guard->hasDetectedPlayer;
}

void guardAttack(struct guard *);

void guardMovement(struct guard *_guard)
{
    guardDelayTimer += 1;

    if(!_guard->hasDetectedPlayer) 
    { 
        if(guardDelayTimer >= 64)
        {
            _guard->directionIsFacing = randw() % 2;

            guardDelayTimer = 0;

            if(_guard->directionIsFacing != 0)
            {
                _guard->isFacingLeft = FALSE;
                _guard->isFacingRight = TRUE;
            }
            else 
            {
                _guard->isFacingLeft = TRUE;
                _guard->isFacingRight = FALSE;
            }   
        }

        set_sprite_tile(8, 48);
        set_sprite_tile(9, 49);
        set_sprite_tile(10, 50);
        set_sprite_tile(11, 51);
    }
    else if(_guard->hasDetectedPlayer && _guard->isChasingPlayer)
    {
        if(guardDelayTimer >= 8 && _guard->guardPosition[0] != playerPosition[0])
        {
            guardDelayTimer = 0;

            if(guardMetaSpriteInUse > 62) { guardMetaSpriteInUse = 53; }
            
            set_sprite_tile(8, guardMetaSpriteInUse);
            set_sprite_tile(9, guardMetaSpriteInUse + 1);
            set_sprite_tile(10, guardMetaSpriteInUse + 2);
            set_sprite_tile(11, guardMetaSpriteInUse + 3);

            guardMetaSpriteInUse += 5;

            if(_guard->guardPosition[0] < playerPosition[0]) 
            { 
                _guard->guardPosition[0] += 1; 

                _guard->isFacingLeft = FALSE;
                _guard->isFacingRight = TRUE;
            }
            else 
            { 
                _guard->guardPosition[0] -= 1; 
            
                _guard->isFacingLeft = TRUE;
                _guard->isFacingRight = FALSE;
            } 
        }
    }

    if(!_guard->isFacingLeft)
    {
        set_sprite_prop(8, get_sprite_prop(8) | S_FLIPX);
        move_sprite(8, _guard->guardPosition[0] + 8, _guard->guardPosition[1]);

        set_sprite_prop(9, get_sprite_prop(9) | S_FLIPX);
        move_sprite(9, _guard->guardPosition[0], _guard->guardPosition[1]);

        set_sprite_prop(10, get_sprite_prop(10) | S_FLIPX);
        move_sprite(10, _guard->guardPosition[0] + 8, _guard->guardPosition[1] + 8);

        set_sprite_prop(11, get_sprite_prop(11) | S_FLIPX);
        move_sprite(11, _guard->guardPosition[0], _guard->guardPosition[1] + 8);
    }
    else
    {
        set_sprite_prop(8, get_sprite_prop(8) & ~S_FLIPX);
        move_sprite(8, _guard->guardPosition[0], _guard->guardPosition[1]);

        set_sprite_prop(9, get_sprite_prop(9) & ~S_FLIPX);
        move_sprite(9, _guard->guardPosition[0] + 8, _guard->guardPosition[1]);

        set_sprite_prop(10, get_sprite_prop(10) & ~S_FLIPX);
        move_sprite(10, _guard->guardPosition[0], _guard->guardPosition[1] + 8);

        set_sprite_prop(11, get_sprite_prop(11) & ~S_FLIPX);
        move_sprite(11, _guard->guardPosition[0] + 8, _guard->guardPosition[1] + 8);
    }
}

void guardCoreLoop()
{
    UINT8 guardLoopCounter = 0;

    if(!haveGuardsBeenInitialized) { guardInitialization(); }

    for(guardLoopCounter = 0; guardLoopCounter < guardsArrayLength; guardLoopCounter++)
    {
        guardDetection(&guards[guardLoopCounter], 64);
        guardMovement(&guards[guardLoopCounter]);
    }
}