#include "actor.h"
#include "sfx.h"
#include "map.h"
#include "util.h"

int player_is_grabbing_wall_flag = 0;
int player_death_counter = 0;
int player_walk_anim_index = 0;
int player_is_being_pushed_flag = 0;
int player_hanging_on_wall_direction = 0;

int player_y_pos = 0;
int player_x_pos = 0;
int player_direction = 0;

int player_sprite_dir_frame_offset = 0;
int player_input_jump_related_flag = 0;

int player_bounce_height_counter = 0;
int player_bounce_flag_maybe = 0;

int num_bombs = 0;

int teleporter_state_maybe = 0;

int word_28F7E;
int word_28F94;
int word_2E1F8;
int word_32B88;

extern int mapwindow_x_offset;
extern int mapwindow_y_offset;

typedef enum {
    NOT_BLOCKED = 0,
    BLOCKED = 1,
    SLOPE = 2
} BlockingType;

BlockingType player_check_movement(int direction, int x_pos, int y_pos)
{
    //FIXME
    return NOT_BLOCKED;
}

void push_player()
{
    //FIXME
}

void handle_player_input_maybe()
{
    int var_4=0;
    BlockingType player_movement_status = NOT_BLOCKED;

    //si = 0;
    player_is_grabbing_wall_flag = 0;
    if(player_death_counter != 0 || teleporter_state_maybe != 0 || word_32B88 != 0 || player_walk_anim_index != 0 || word_2E1F8 != 0)
    {
        return;
    }
    word_28F94 = word_28F94 + 1;
    push_player();
    if(player_is_being_pushed_flag != 0)
    {
        player_hanging_on_wall_direction = 0;
        return;
    }
    if(player_hanging_on_wall_direction != 0)
    {
        if(player_hanging_on_wall_direction != 2)
        {
            var_4 = map_get_tile_cell(player_x_pos + 3, player_y_pos - 2);
        }
        else
        {
            var_4 = map_get_tile_cell(player_x_pos - 1, player_y_pos - 2);
        }
        if((* (& tileattr_mni_data + (var_4 >> 3)) & 0x10) != 0 && (* (tileattr_mni_data + (var_4 >> 3)) & 0x80) != 0)
        {
            if(player_check_movement(1, player_x_pos, player_y_pos + 1) == NOT_BLOCKED)
            {
                player_y_pos = player_y_pos + 1;
                si = 1;
                if(player_hanging_on_wall_direction != 2)
                {
                    var_4 = map_get_tile_cell(player_x_pos + 3, player_y_pos - 2);
                }
                else
                {
                    var_4 = map_get_tile_cell(player_x_pos - 1, player_y_pos - 2);
                }
                ax = var_4 >> 3;
                if((* (& tileattr_mni_data + ax) & 0x10) == 0)
                {
                    ax = var_4 >> 3;
                    if((* (tileattr_mni_data + ax) & 0x80) == 0)
                    {
                        player_hanging_on_wall_direction = 0;
                        si = 0;
                        goto loc_1DD63;
                    }
                }
            }
            else
            {
                player_hanging_on_wall_direction = 0;
            }
        }
        else
        {
            ax = var_4 >> 3;
            if((* (& tileattr_mni_data + ax) & 0x80) == 0)
            {
                player_hanging_on_wall_direction = 0;
            }
        }
    }
    if(player_hanging_on_wall_direction == 0)
    {
        if(bomb_key_pressed == 0)
        {
            local_bomb_key_counter = 0;
        }
        if(bomb_key_pressed != 0 && local_bomb_key_counter == 0)
        {
            local_bomb_key_counter = 2;
        }
        if(local_bomb_key_counter != 0 && local_bomb_key_counter != 1)
        {
            local_bomb_key_counter = local_bomb_key_counter - 1;
            if(local_bomb_key_counter == 1)
            {
                if(player_direction == 0)
                {
                    ax = map_get_tile_cell(player_x_pos - 1, player_y_pos - 2) >> 3;
                    top_bomb_check_flag = al & 4;
                    ax = map_get_tile_cell(player_x_pos - 2, player_y_pos - 2) >> 3;
                    ax = al & 4;
                    var_4 = ax;
                    if(num_bombs != 0 || has_had_bomb_flag != 0)
                    {
                        if(top_bomb_check_flag != 0)
                        {
                            play_sfx(0x1c);
                        }
                        else
                        {
                            if(var_4 != 0)
                            {
                                play_sfx(0x1c);
                            }
                            else
                            {
                                if(num_bombs <= 0)
                                {
                                    play_sfx(0x1c);
                                }
                                else
                                {
                                    actor_add_new(0x18, player_x_pos - 2, player_y_pos - 2);
                                    num_bombs = num_bombs - 1;
                                    display_num_bombs_left();
                                    play_sfx(0x1d);
                                }
                            }
                        }
                    }
                    else
                    {
                        has_had_bomb_flag = 1;
                        you_havent_found_any_bombs_dialog();
                    }
                }
                else
                {
                    ax = map_get_tile_cell(player_x_pos + 3, player_y_pos - 2) >> 3;
                    top_bomb_check_flag = al & 8;
                    ax = map_get_tile_cell(player_x_pos + 4, player_y_pos - 2) >> 3;
                    ax = al & 8;
                    var_4 = ax;
                    if(num_bombs == 0 && has_had_bomb_flag == 0)
                    {
                        has_had_bomb_flag = 1;
                        you_havent_found_any_bombs_dialog();
                    }
                    if(top_bomb_check_flag != 0)
                    {
                        play_sfx(0x1c);
                    }
                    else
                    {
                        if(var_4 == 0)
                        {
                            if(num_bombs > 0)
                            {
                                actor_add_new(0x18, player_x_pos + 3, player_y_pos - 2);
                                num_bombs = num_bombs - 1;
                                display_num_bombs_left();
                                play_sfx(0x1d);
                            }
                            else
                            {
                                play_sfx(0x1c);
                            }
                        }
                        else
                        {
                            play_sfx(0x1c);
                        }
                    }
                }
            }
        }
        else
        {
            bomb_key_pressed = 0;
        }
    }
    if(byte_2E182 != 0 || bomb_key_pressed == 0 || byte_2E2E4 != 0 || player_hanging_on_wall_direction != 0 || jump_key_pressed != 0 && player_input_jump_related_flag == 0)
    {
        word_2E214 = 0;
        //ax = player_check_movement(1, player_x_pos, player_y_pos + 1);
        if(is_standing_slipry_slope_left_flg == 0 || is_standing_slipry_slope_right_flg == 0)
        {
            if(is_standing_slipry_slope_right_flg != 0)
            {
                if(player_hanging_on_wall_direction == 0)
                {
                    player_x_pos = player_x_pos - 1;
                }
                if(player_check_movement(1, player_x_pos, player_y_pos + 1) == 0 && player_hanging_on_wall_direction == 0)
                {
                    player_y_pos = player_y_pos + 1;
                }
                if(player_y_pos - mapwindow_y_offset > 14)
                {
                    mapwindow_y_offset = mapwindow_y_offset + 1;
                }
                ax = player_x_pos - mapwindow_x_offset;
                if(ax < 12 && mapwindow_x_offset > 0)
                {
                    mapwindow_x_offset = mapwindow_x_offset - 1;
                }
                player_hanging_on_wall_direction = 0;
            }
            if(is_standing_slipry_slope_left_flg != 0)
            {
                if(player_hanging_on_wall_direction == 0)
                {
                    player_x_pos = player_x_pos + 1;
                }
                if(player_check_movement(1, player_x_pos, player_y_pos + 1) == 0 && player_hanging_on_wall_direction == 0)
                {
                    player_y_pos = player_y_pos + 1;
                }
                if(player_y_pos - mapwindow_y_offset > 14)
                {
                    mapwindow_y_offset = mapwindow_y_offset + 1;
                }
                ax = player_x_pos - mapwindow_x_offset;
                if(ax > 0x17)
                {
                    ax = map_width_in_tiles + 0xffffffda;
                    if(ax > mapwindow_x_offset)
                    {
                        mapwindow_x_offset = mapwindow_x_offset + 1;
                    }
                }
                player_hanging_on_wall_direction = 0;
            }
        }
        if(left_key_pressed != 0 && player_hanging_on_wall_direction == 0 && right_key_pressed == 0)
        {
            ax = player_check_movement(1, player_x_pos, player_y_pos + 1);
            di = ax;
            if(player_direction_related_32E98 != 2)
            {
                player_direction_related_32E98 = 2;
            }
            else
            {
                player_x_pos = player_x_pos - 1;
            }
            player_direction = 0;
            if(player_x_pos >= 1)
            {
                ax = player_check_movement(2, player_x_pos, player_y_pos);
                player_movement_status = ax;
                if(ax == 1)
                {
                    player_x_pos = player_x_pos + 1;
                    ax = player_check_movement(1, player_x_pos, player_y_pos + 1);
                    if(ax == 0 && player_is_grabbing_wall_flag != 0)
                    {
                        player_hanging_on_wall_direction = 2;
                        player_bounce_flag_maybe = 0;
                        player_bounce_height_counter = 0;
                        play_sfx(4);
                        byte_2E2E4 = 0;
                        byte_2E182 = 0;
                        word_2E180 = 0;
                        if(jump_key_pressed == 0)
                        {
                            player_input_jump_related_flag = 0;
                        }
                        else
                        {
                            player_input_jump_related_flag = 1;
                        }
                    }
                }
            }
            else
            {
                player_x_pos = player_x_pos + 1;
            }
            if(player_movement_status != 2)
            {
                if(di == 2)
                {
                    ax = player_check_movement(1, player_x_pos, player_y_pos + 1);
                    if(ax == 0)
                    {
                        byte_2E2E4 = 0;
                        byte_2E182 = 0;
                        player_y_pos = player_y_pos + 1;
                    }
                }
            }
            else
            {
                player_y_pos = player_y_pos - 1;
            }
        }
        if(right_key_pressed != 0 && player_hanging_on_wall_direction == 0 && left_key_pressed == 0)
        {
            di = player_check_movement(1, player_x_pos, player_y_pos + 1);
            if(player_direction_related_32E98 != 3)
            {
                player_direction_related_32E98 = 3;
            }
            else
            {
                player_x_pos = player_x_pos + 1;
            }
            player_direction = 0x17;
            ax = map_width_in_tiles - 4;
            if(ax >= player_x_pos)
            {
                player_movement_status = player_check_movement(3, player_x_pos, player_y_pos);
                if(player_movement_status == 1)
                {
                    player_x_pos = player_x_pos - 1;
                    ax = player_check_movement(1, player_x_pos, player_y_pos + 1);
                    if(ax == 0 && player_is_grabbing_wall_flag != 0)
                    {
                        player_hanging_on_wall_direction = 3;
                        player_bounce_flag_maybe = 0;
                        player_bounce_height_counter = 0;
                        play_sfx(4);
                        byte_2E182 = 0;
                        byte_2E2E4 = 0;
                        word_2E180 = 0;
                        if(jump_key_pressed == 0)
                        {
                            player_input_jump_related_flag = 0;
                        }
                        else
                        {
                            player_input_jump_related_flag = 1;
                        }
                    }
                }
            }
            else
            {
                player_x_pos = player_x_pos - 1;
            }
            if(player_movement_status != 2)
            {
                if(di == 2)
                {
                    ax = player_check_movement(1, player_x_pos, player_y_pos + 1);
                    if(ax == 0)
                    {
                        byte_2E2E4 = 0;
                        word_2E180 = 0;
                        player_y_pos = player_y_pos + 1;
                    }
                }
            }
            else
            {
                player_y_pos = player_y_pos - 1;
            }
        }
        if(player_hanging_on_wall_direction != 0 && player_input_jump_related_flag != 0 && jump_key_pressed == 0)
        {
            player_input_jump_related_flag = 0;
        }
        if(player_bounce_height_counter != 0 || jump_key_pressed != 0 && byte_2E2E4 == 0 && player_input_jump_related_flag == 0 || player_hanging_on_wall_direction != 0 && jump_key_pressed != 0 && player_input_jump_related_flag == 0)
        {
            if(player_bounce_flag_maybe != 0 && player_bounce_height_counter > 0)
            {
                player_bounce_height_counter = player_bounce_height_counter - 1;
                if(player_bounce_height_counter < 10)
                {
                    word_2E1DE = 0;
                }
                if(player_bounce_height_counter > 1)
                {
                    player_y_pos = player_y_pos - 1;
                }
                if(player_bounce_height_counter > 13)
                {
                    player_bounce_height_counter = player_bounce_height_counter - 1;
                    if(player_check_movement(0, player_x_pos, player_y_pos) != 0)
                    {
                        word_2E1DE = 0;
                    }
                    else
                    {
                        player_y_pos = player_y_pos - 1;
                    }
                }
                var_4 = 0;
                if(player_bounce_height_counter == 0)
                {
                    byte_2E182 = 0;
                    player_bounce_flag_maybe = 0;
                    word_2E180 = 0;
                    word_2E1DE = 0;
                    player_input_jump_related_flag = 1;
                }
            }
            else
            {
                if(player_hanging_on_wall_direction == 2)
                {
                    if(left_key_pressed == 0)
                    {
                        if(right_key_pressed != 0)
                        {
                            player_direction = 0x17;
                        }
                    }
                    else
                    {
                        player_hanging_on_wall_direction = 0;
                    }
                }
                if(player_hanging_on_wall_direction == 3)
                {
                    if(right_key_pressed == 0)
                    {
                        if(left_key_pressed != 0)
                        {
                            player_direction = 0;
                        }
                    }
                    else
                    {
                        player_hanging_on_wall_direction = 0;
                    }
                }
                if(player_hanging_on_wall_direction == 0)
                {
                    player_y_pos = player_y_pos + * ((al << 1) + word_28F80);
                }
                if(byte_2E182 == 0 && player_check_movement(0, player_x_pos, player_y_pos + 1) != 0)
                {
                    player_y_pos = player_y_pos + 1;
                }
                player_bounce_flag_maybe = 0;
                var_4 = 1;
            }
            player_hanging_on_wall_direction = 0;
            ax = player_check_movement(0, player_x_pos, player_y_pos);
            if(ax == 0)
            {
                if(var_4 != 0 && byte_2E182 == 0)
                {
                    play_sfx(2);
                }
            }
            else
            {
                if(byte_2E182 > 0 || player_bounce_flag_maybe != 0)
                {
                    loc_1E420:
                    play_sfx(5);
                }
                player_bounce_height_counter = 0;
                player_bounce_flag_maybe = 0;
                ax = player_check_movement(0, player_x_pos, player_y_pos + 1);
                if(ax != 0)
                {
                    player_y_pos = player_y_pos + 1;
                }
                player_y_pos = player_y_pos + 1;
                byte_2E2E4 = 1;
                if(jump_key_pressed != 0)
                {
                    player_input_jump_related_flag = 1;
                }
                word_2E180 = 0;
                word_2E1DE = 0;
            }
            if(player_bounce_flag_maybe == 0)
            {
                ax = ax & 0xff00 | byte_2E182;
                byte_2E182 = byte_2E182 + 1;
                if(al > 6)
                {
                    byte_2E2E4 = 1;
                    if(jump_key_pressed != 0)
                    {
                        player_input_jump_related_flag = 1;
                    }
                    word_2E180 = 0;
                }
            }
        }
        if(player_hanging_on_wall_direction == 0)
        {
            if(byte_2E2E4 != 0 && jump_key_pressed != 0)
            {
                player_input_jump_related_flag = 1;
            }
            if((jump_key_pressed == 0 || player_input_jump_related_flag != 0) && byte_2E2E4 == 0)
            {
                byte_2E2E4 = 1;
                word_2E180 = 0;
            }
            if(byte_2E2E4 != 0 && player_bounce_flag_maybe == 0)
            {
                player_y_pos = player_y_pos + 1;
                ax = player_check_movement(1, player_x_pos, player_y_pos);
                if(ax != 0)
                {
                    if(word_2E180 != 0)
                    {
                        play_sfx(3);
                    }
                    byte_2E2E4 = 0;
                    player_y_pos = player_y_pos - 1;
                    byte_2E182 = 0;
                    if(jump_key_pressed == 0)
                    {
                        player_input_jump_related_flag = 0;
                    }
                    else
                    {
                        player_input_jump_related_flag = 1;
                    }
                    word_2E180 = 0;
                }
                if(word_2E180 > 3)
                {
                    player_y_pos = player_y_pos + 1;
                    mapwindow_y_offset = mapwindow_y_offset + 1;
                    ax = player_check_movement(1, player_x_pos, player_y_pos);
                    if(ax != 0)
                    {
                        play_sfx(3);
                        byte_2E2E4 = 0;
                        player_y_pos = player_y_pos - 1;
                        mapwindow_y_offset = mapwindow_y_offset - 1;
                        byte_2E182 = 0;
                        if(jump_key_pressed == 0)
                        {
                            player_input_jump_related_flag = 0;
                        }
                        else
                        {
                            player_input_jump_related_flag = 1;
                        }
                        word_2E180 = 0;
                    }
                }
                if(word_2E180 < 0x19)
                {
                    word_2E180 = word_2E180 + 1;
                }
            }
            if(byte_2E2E4 != 0 && word_2E180 == 1 && player_bounce_flag_maybe == 0)
            {
                player_y_pos = player_y_pos - 1;
            }
        }
    }
    else
    {
        if(left_key_pressed == 0)
        {
            if(right_key_pressed == 0)
            {
                if(player_direction_related_32E98 != 2)
                {
                    if(player_direction_related_32E98 == 3)
                    {
                        word_2E214 = 3;
                    }
                }
                else
                {
                    word_2E214 = 2;
                }
            }
            else
            {
                player_direction_related_32E98 = 3;
                word_2E214 = 3;
                player_direction = 0x17;
            }
        }
        else
        {
            player_direction_related_32E98 = 2;
            word_2E214 = 2;
            player_direction = 0;
        }
    }
    if (word_2E214 == 0) goto loc_1E5DC;

// node 0001e5cd-0001e5d9 #insn=3 use={} def={} in={si} out={si} pred={ 1DC0F} JUMP target=0001e8d8
    word_28F7E = 0;
    player_sprite_dir_frame_offset = 14;
    goto loc_1E8D8;

// node 0001e5dc-0001e5e1 #insn=2 use={} def={} in={ax, si, al, dl} out={ax, si, al, dl} pred={ 1DC0F} CONDJUMP target=0001e615 follow=0001e6bd
    loc_1E5DC:
    if ((up_key_pressed != 0 || down_key_pressed != 0) && left_key_pressed == 0 && right_key_pressed == 0 && byte_2E2E4 == 0 && jump_key_pressed == 0) goto loc_1E615;

// node 0001e615-0001e6a9 #insn=6 use={} def={} in={} out={} pred={ 1E5DC} FALLTHROUGH follow=0001e96f
    loc_1E615:
    word_28F7E = 0;
    if(up_key_pressed != 0 && player_is_teleporting_flag == 0 && word_32EAC == 0)
    {
        if(mapwindow_y_offset > 0 && player_y_pos - mapwindow_y_offset < 0x11)
        {
            mapwindow_y_offset = mapwindow_y_offset - 1;
        }
        if(si != 0)
        {
            mapwindow_y_offset = mapwindow_y_offset + 1;
        }
        if(player_hanging_on_wall_direction == 0)
        {
            player_sprite_dir_frame_offset = 5;
        }
        else
        {
            player_sprite_dir_frame_offset = 11;
        }
        return ax;
    }
    if(down_key_pressed == 0)
    {
        return ;
    }
    if(mapwindow_y_offset + 3 < player_y_pos)
    {
        mapwindow_y_offset = mapwindow_y_offset + 1;
        if((si != 0 || is_standing_slipry_slope_left_flg != 0 || is_standing_slipry_slope_right_flg != 0) && mapwindow_y_offset + 3 < player_y_pos)
        {
            mapwindow_y_offset = mapwindow_y_offset + 1;
        }
    }
    if(player_hanging_on_wall_direction == 0)
    {
        player_sprite_dir_frame_offset = 6;
    }
    else
    {
        player_sprite_dir_frame_offset = 12;
    }

// node 0001e6bd-0001e6c2 #insn=2 use={} def={} in={} out={} pred={ 1E5DC} FALLTHROUGH follow=0001e8d8
    loc_1E6BD:
    if(player_hanging_on_wall_direction != 2)
    {
        if(player_hanging_on_wall_direction != 3)
        {
            if((byte_2E2E4 == 0 || player_bounce_flag_maybe != 0) && (byte_2E182 <= 6 || byte_2E2E4 != 0))
            {
                if((jump_key_pressed == 0 || player_input_jump_related_flag != 0) && player_bounce_flag_maybe == 0)
                {
                    if(al == right_key_pressed)
                    {
                        ax = _rand();
                        bx = 0x32;
                        var_4[1] = dl;
                        player_sprite_dir_frame_offset = 4;
                        if(left_key_pressed == 0 && right_key_pressed == 0 && byte_2E2E4 == 0)
                        {
                            word_28F7E = word_28F7E + 1;
                            if(word_28F7E <= 0x64 || word_28F7E >= 0x6e)
                            {
                                if(word_28F7E <= 0x8b || word_28F7E >= 0x96)
                                {
                                    if(word_28F7E == 0xb4)
                                    {
                                        player_sprite_dir_frame_offset = 0x13;
                                    }
                                    else
                                    {
                                        if(word_28F7E == 0xb5)
                                        {
                                            player_sprite_dir_frame_offset = 0x14;
                                        }
                                        else
                                        {
                                            if(word_28F7E != 0xb6)
                                            {
                                                if(word_28F7E != 0xb7)
                                                {
                                                    if(word_28F7E != 0xb8)
                                                    {
                                                        if(word_28F7E == 0xb9)
                                                        {
                                                            word_28F7E = 0;
                                                        }
                                                    }
                                                    else
                                                    {
                                                        player_sprite_dir_frame_offset = 0x13;
                                                    }
                                                }
                                                else
                                                {
                                                    player_sprite_dir_frame_offset = 0x14;
                                                }
                                            }
                                            else
                                            {
                                                player_sprite_dir_frame_offset = 0x15;
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    player_sprite_dir_frame_offset = 6;
                                }
                            }
                            else
                            {
                                player_sprite_dir_frame_offset = 5;
                            }
                        }
                        if(player_sprite_dir_frame_offset != 5 && player_sprite_dir_frame_offset != 6 && (var_4[1] == 0 || var_4[1] == 0x1f))
                        {
                            loc_1E89B:
                            player_sprite_dir_frame_offset = 0x12;
                            goto loc_1E8D8;
                        }
                    }
                    else
                    {
                        if(byte_2E2E4 == 0)
                        {
                            word_28F7E = 0;
                            if((word_28F94 & 1) != 0)
                            {
                                if((player_sprite_dir_frame_offset & 1) != 0)
                                {
                                    play_sfx(0x13);
                                }
                                player_sprite_dir_frame_offset = player_sprite_dir_frame_offset + 1;
                            }
                            if(player_sprite_dir_frame_offset > 3)
                            {
                                player_sprite_dir_frame_offset = 0;
                            }
                        }
                    }
                }
                else
                {
                    word_28F7E = 0;
                    player_sprite_dir_frame_offset = 7;
                    if(player_bounce_flag_maybe != 0 && word_2E1DE != 0)
                    {
                        player_sprite_dir_frame_offset = 0x16;
                    }
                    if(player_bounce_height_counter < 3 && player_bounce_flag_maybe != 0)
                    {
                        player_sprite_dir_frame_offset = 8;
                    }
                }
            }
            else
            {
                word_28F7E = 0;
                if(player_bounce_flag_maybe != 0 || byte_2E2E4 != 0 || byte_2E182 <= 6)
                {
                    if(word_2E180 < 10 || word_2E180 >= 0x19)
                    {
                        if(word_2E180 != 0x19)
                        {
                            if(byte_2E2E4 != 0)
                            {
                                player_sprite_dir_frame_offset = 8;
                            }
                            else
                            {
                                player_sprite_dir_frame_offset = 7;
                            }
                        }
                        else
                        {
                            player_sprite_dir_frame_offset = 0x10;
                            word_32EB2 = 1;
                        }
                    }
                    else
                    {
                        player_sprite_dir_frame_offset = 13;
                    }
                }
                else
                {
                    player_sprite_dir_frame_offset = 8;
                }
            }
        }
        else
        {
            word_28F7E = 0;
            if(left_key_pressed == 0)
            {
                player_sprite_dir_frame_offset = 9;
            }
            else
            {
                player_sprite_dir_frame_offset = 10;
            }
        }
    }
    else
    {
        word_28F7E = 0;
        if(right_key_pressed != 0)
        {
            player_sprite_dir_frame_offset = 10;
        }
        else
        {
            player_sprite_dir_frame_offset = 9;
        }
    }

// node 0001e8d8-0001e962 #insn=5 use={} def={} in={} out={} pred={ 1E5CD 1E6BD} FALLTHROUGH follow=0001e96f
    loc_1E8D8:
    if(player_y_pos - mapwindow_y_offset > 14)
    {
        mapwindow_y_offset = mapwindow_y_offset + 1;
    }
    if(si == 0 || player_y_pos - mapwindow_y_offset <= 14)
    {
        if(player_bounce_height_counter > 10 && player_y_pos - mapwindow_y_offset < 7 && mapwindow_y_offset > 0)
        {
            mapwindow_y_offset = mapwindow_y_offset - 1;
        }
        if(player_y_pos - mapwindow_y_offset < 7 && mapwindow_y_offset > 0)
        {
            mapwindow_y_offset = mapwindow_y_offset - 1;
        }
    }
    else
    {
        mapwindow_y_offset = mapwindow_y_offset + 1;
    }
    if(player_x_pos - mapwindow_x_offset > 0x17 && map_width_in_tiles + 0xffffffda > mapwindow_x_offset && map_stride_bit_shift_amt > 5)
    {
        mapwindow_x_offset = mapwindow_x_offset + 1;
        return ax;
    }
    if(player_x_pos - mapwindow_x_offset < 12 && mapwindow_x_offset > 0)
    {
        mapwindow_x_offset = mapwindow_x_offset - 1;
        return ax;
    }

// node 0001e96f-0001e972 #insn=4 use={} def={si, di} in={} out={} pred={ 1E615 1E8D8} RETURN
    loc_1E96F:
    /* pop  */
    /* pop  */
    return ;
}