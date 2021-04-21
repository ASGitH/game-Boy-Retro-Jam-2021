#include "projectile.h"

#include "sprites/miscellaneous.h"

struct projectile projectiles[3];

BOOLEAN haveProjectilesBeenInitialized = FALSE;

UINT8 projectileLifespan = 64;
UINT8 projectilesSpawned = 0;
UINT8 selectedProjectile = 0;

void forwardProjectile()
{   
    for(selectedProjectile = 0; selectedProjectile < 3; selectedProjectile++)
    {
        if(projectiles[selectedProjectile].hasProjectileBeenIntialized == TRUE)
        {
            if(projectiles[selectedProjectile].directionOfProjectile != 'l') { scroll_sprite(4 + selectedProjectile, -1, 0); }
            else { scroll_sprite(4 + selectedProjectile, 1, 0); }
        }
    }
}

void initializeProjectiles()
{
    if(!haveProjectilesBeenInitialized)
    {
        for(selectedProjectile = 0; selectedProjectile < 3; selectedProjectile++) { projectiles[selectedProjectile].hasProjectileBeenIntialized = FALSE; }

        haveProjectilesBeenInitialized = TRUE;

        set_sprite_data(45, 2, miscellaneousSprites);
    }
}

void instantializeProjectile(struct player *_player)
{
    for(selectedProjectile = 0; selectedProjectile < 3; selectedProjectile++)
    {
        if(projectiles[selectedProjectile].hasProjectileBeenIntialized == FALSE)
        {
            set_sprite_tile(4 + selectedProjectile, 46);
    
            projectiles[selectedProjectile].currentProjectileLifespan = 0;

            projectiles[selectedProjectile].hasProjectileBeenIntialized = TRUE;

            if(!_player->isFacingLeft) 
            { 
                move_sprite(4 + selectedProjectile, _player->player_position[0] + 16, _player->player_position[1] + 4);
            
                projectiles[selectedProjectile].directionOfProjectile = 'l';
            }
            else
            { 
                move_sprite(4 + selectedProjectile, _player->player_position[0] - 8, _player->player_position[1] + 4); 
            
                projectiles[selectedProjectile].directionOfProjectile = 'r';
            }
            
            projectilesSpawned += 1;

            break;
        }
    }
}

INT8 projectileCollision(struct projectile *_projectile, UINT8);

void recycleProjectile()
{
    for(selectedProjectile = 0; selectedProjectile < 3; selectedProjectile++)
    {
        if(projectiles[selectedProjectile].hasProjectileBeenIntialized == TRUE)
        {
            if(projectiles[selectedProjectile].currentProjectileLifespan + 1 <= projectileLifespan) { projectiles[selectedProjectile].currentProjectileLifespan += 1; }
            else 
            {
                projectilesSpawned -= 1;

                projectiles[selectedProjectile].hasProjectileBeenIntialized = FALSE;

                set_sprite_tile(4 + selectedProjectile, 45); 
            }
        }
    }
}

// Anything that happens within the projectile, will occurr in this loop
void projectileCoreLoop()
{
    forwardProjectile();

    initializeProjectiles();

    recycleProjectile();
}