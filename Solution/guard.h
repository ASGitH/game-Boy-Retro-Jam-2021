#ifndef GUARD_H
#define GUARD_H

#include <gb/gb.h>

struct guard
{
    BOOLEAN hasDetectedPlayer;
    BOOLEAN hasGuardBeenHit;
    BOOLEAN hasGuardBeenIntialized;
    BOOLEAN isAttacking;
    BOOLEAN isChasingPlayer;
    BOOLEAN isFacingLeft;
    BOOLEAN isFacingRight;

    BYTE jumping;

    UINT8 directionIsFacing;

    UINT16 indexTopLeftX;
    UINT16 indexTopLeftY;
    UINT16 tileIndexTopLeft;

    UINT16 guardPosition[2];
};

extern struct guard guards[1];

extern UINT8 guardLoopCounter;

BOOLEAN guardInitialization();

BOOLEAN guardDetection(struct guard *, UINT8 distance);

void guardAttack(struct guard *);

void guardMovement(struct guard *);

void guardCoreLoop();

#endif