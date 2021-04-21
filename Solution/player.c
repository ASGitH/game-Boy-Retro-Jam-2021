#include "player.h"

#include "projectile.h"
#include "sprites/playerTD.h"

#include "stdio.h"

BOOLEAN has_player_been_intialized = FALSE;
// BOOLEAN has_reached_maximum_jump_height = FALSE;
BOOLEAN has_reached_limit = FALSE;
BOOLEAN will_switch_state = FALSE;

UINT8 attack_delay = 0;
UINT8 jump_delay = 0;
UINT8 jump_height = 10;
UINT8 metaSpriteInUse = 1;
UINT8 sprites_in_use = 0;
UINT8 sprites_to_use = 0;
UINT8 walkingCycleDelay = 0;

UINT16 playerPosition[2];

void initialize_player(struct player *_player)
{
    UINT8 temporary_counter = 0;
    for(; temporary_counter < 40; temporary_counter++) { set_sprite_tile(temporary_counter, 0); }
   
    has_player_been_intialized = TRUE;

    _player->index_top_left_x = 0;
    _player->index_top_left_y = 0;

    _player->isAttacking = FALSE;    
    _player->isFacingLeft = TRUE;
    _player->isFacingRight = FALSE;
    
    _player->jumping = 0;
    
    _player->player_position[0] = 80; _player->player_position[1] = 72;
    
    _player->tile_index_top_left = 0;
    _player->player_width = 16;

    set_sprite_data(0, 45, (unsigned char *)playerSprites);

    set_sprite_tile(0, 1);
    move_sprite(0, _player->player_position[0], _player->player_position[1]);

    set_sprite_tile(1, 2);
    move_sprite(1, _player->player_position[0], _player->player_position[1] + 8);

    set_sprite_tile(2, 3);
    move_sprite(2, _player->player_position[0] + 8, _player->player_position[1]);

    set_sprite_tile(3, 4);
    move_sprite(3, _player->player_position[0] + 8, _player->player_position[1] + 8);
}

// INT8 would_hit_surface(struct player *_player, UINT8 _projected_y_position)
// {
//     // if(_projected_y_position >= _player->floor_y_position) { return _player->floor_y_position; }

//     return -1;
// }

void player_attack(struct player *_player)
{
    if(_player->isAttacking == 0)
    {
        // play_fx(0);

        _player->isAttacking = 1;
        
        instantializeProjectile(_player);

        set_sprite_tile(0, 36);
        set_sprite_tile(1, 37);
        set_sprite_tile(2, 38);
        set_sprite_tile(3, 39);   
    }

    if(_player->isAttacking == 1)
    {
        if(!has_reached_limit) 
        {
            if(attack_delay != 6) { attack_delay += 1; }
            else 
            { 
                has_reached_limit = TRUE; 

                attack_delay = 0;

                set_sprite_tile(0, 41);
                set_sprite_tile(1, 42);
                set_sprite_tile(2, 43);
                set_sprite_tile(3, 44);   
            }
        }
        else 
        {
            if(attack_delay != 16) { attack_delay += 1; }
            else if(attack_delay >= 16)
            {
                has_reached_limit = FALSE;

                attack_delay = 0;

                _player->isAttacking = 0;
                _player->jumping = 0;
            }

            set_sprite_tile(0, 1);
            set_sprite_tile(1, 2);
            set_sprite_tile(2, 3);
            set_sprite_tile(3, 4);   
        }
    }
}


void player_jump(struct player *_player)
{
    if(_player->jumping == 0)
    {
        // play_fx(0);

        _player->jumping = 1;
        
        set_sprite_tile(0, 26);
        set_sprite_tile(1, 27);
        set_sprite_tile(2, 28);
        set_sprite_tile(3, 29);   
    }

    if(_player->jumping == 1)
    {
        if(!has_reached_limit) 
        {
            if(jump_height != 0)
            { 
                jump_delay += 1;

                if(jump_delay >= 2)
                {
                    jump_delay = 0;

                    jump_height -= 1;

                    _player->player_position[1] -= 2;
                }
            }
            else 
            { 
                has_reached_limit = TRUE; 

                jump_delay = 0;

                set_sprite_tile(0, 31);
                set_sprite_tile(1, 32);
                set_sprite_tile(2, 33);
                set_sprite_tile(3, 34);   
            }
        }
        else 
        {
            if(jump_height != 10)
            {
                jump_delay += 1;

                if(jump_delay >= 2)
                {
                    jump_delay = 0;

                    jump_height += 1;

                    _player->player_position[1] += 2;
                }
            }
            else
            {
                has_reached_limit = FALSE;

                jump_height = 10;

                _player->isAttacking = 0;
                _player->jumping = 0;

                set_sprite_tile(0, 1);
                set_sprite_tile(1, 2);
                set_sprite_tile(2, 3);
                set_sprite_tile(3, 4);   
            }
        }
    }
}

void player_movement(struct player *_player)
{
    if((joypad() & J_A) || _player->jumping == 1) { player_jump(_player); }
    else if(joypad() & J_B || _player->isAttacking == 1) { player_attack(_player); }

    if(_player->isAttacking != 1)
    {
        if (joypad() & J_LEFT && _player->index_top_left_x > 0 /* && !scene_collision(1, _player->tile_index_top_left, _player->index_top_left_x, _player->index_top_left_y) */) 
        { 
            _player->isFacingLeft = TRUE;
            _player->isFacingRight = FALSE;

            _player->player_position[0] -= 1; 
        }

        if (joypad() & J_RIGHT && _player->index_top_left_x < 17 /* && !scene_collision(2, _player->tile_index_top_left, _player->index_top_left_x, _player->index_top_left_y) */) 
        {
            _player->isFacingLeft = FALSE;
            _player->isFacingRight = TRUE;  

            _player->player_position[0] += 1; 
        }
    }
    

    if(/*_player->jumping == 0 && */ _player->isAttacking == 0)
    {
        if(joypad() != J_LEFT && joypad() != J_RIGHT)
        {
            set_sprite_tile(0, 1);
            set_sprite_tile(1, 2);
            set_sprite_tile(2, 3);
            set_sprite_tile(3, 4);   
        }
        else if(joypad() & J_LEFT || joypad() & J_RIGHT)
        {
            walkingCycleDelay += 1;

            if(walkingCycleDelay >= 4)
            {
                walkingCycleDelay = 0;

                metaSpriteInUse += 5;

                if(metaSpriteInUse > 25) { metaSpriteInUse = 6; }

                set_sprite_tile(0, metaSpriteInUse);
                set_sprite_tile(1, metaSpriteInUse + 1);
                set_sprite_tile(2, metaSpriteInUse + 2);
                set_sprite_tile(3, metaSpriteInUse + 3);   
            }
        }
    }

    if(!_player->isFacingLeft)
    {
        set_sprite_prop(0, get_sprite_prop(0) | S_FLIPX);
        move_sprite(0, _player->player_position[0] + 8, _player->player_position[1]);

        set_sprite_prop(1, get_sprite_prop(1) | S_FLIPX);
        move_sprite(1, _player->player_position[0] + 8, _player->player_position[1] + 8);

        set_sprite_prop(2, get_sprite_prop(2) | S_FLIPX);
        move_sprite(2, _player->player_position[0], _player->player_position[1]);

        set_sprite_prop(3, get_sprite_prop(3) | S_FLIPX);
        move_sprite(3, _player->player_position[0], _player->player_position[1] + 8);
    }
    else
    {
        set_sprite_prop(0, get_sprite_prop(0) & ~S_FLIPX);
        move_sprite(0, _player->player_position[0], _player->player_position[1]);

        set_sprite_prop(1, get_sprite_prop(1) & ~S_FLIPX);
        move_sprite(1, _player->player_position[0], _player->player_position[1] + 8);

        set_sprite_prop(2, get_sprite_prop(2) & ~S_FLIPX);
        move_sprite(2, _player->player_position[0] + 8, _player->player_position[1]);

        set_sprite_prop(3, get_sprite_prop(3) & ~S_FLIPX);
        move_sprite(3, _player->player_position[0] + 8, _player->player_position[1] + 8);
    }
}

void update_Player(struct player *_player)
{
    _player->index_top_left_x = (_player->player_position[0] - 8) / 8;
    _player->index_top_left_y = (_player->player_position[1] - 16) / 8;
    _player->tile_index_top_left = 32 * _player->index_top_left_y + _player->index_top_left_x;

    playerPosition[0] = _player->player_position[0];
    playerPosition[1] = _player->player_position[1];
}

void player_core_loop(struct player *_player)
{
    if(!has_player_been_intialized) { initialize_player(_player); }
    else`
    {
        player_movement(_player);
        
        update_Player(_player);
    }
}