#ifndef PLAYER_H
#define PLAYER_H

#include <gb/gb.h>

struct player
{
    BOOLEAN isAttacking;
    BOOLEAN isFacingLeft;
    BOOLEAN isFacingRight;

    // Is the player currently jumping
    BYTE jumping;

    UINT8 player_width;
    UINT8 player_height;

    UINT16 index_top_left_x;
    UINT16 index_top_left_y;
    UINT16 tile_index_top_left;

    // Will keep track of the player's current position on screen
    UINT16 player_position[2];
};

extern BOOLEAN has_player_been_intialized;

extern UINT8 directionPlayerIsFacing;

extern UINT16 playerPosition[2];

void initialize_player(struct player *);

// INT8 would_hit_surface(struct player *, UINT8);

void player_attack(struct player *);

void player_jump(struct player *);

void player_movement(struct player *);

void update_Player(struct player *);

// Anything that happens within the player, will occurr in this loop
void player_core_loop(struct player *);

#endif