#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <gb/gb.h>

#include "player.h"

struct projectile
{
    BOOLEAN hasProjectileBeenIntialized;

    char directionOfProjectile;

    UINT8 currentProjectileLifespan;
};

extern UINT8 projectilesSpawned;

void forwardProjectile();

void initializeProjectiles();

void instantializeProjectile(struct player *);

INT8 projectileCollision(struct projectile *, UINT8);

void recycleProjectile();

// Anything that happens within the projectile, will occurr in this loop
void projectileCoreLoop();

#endif