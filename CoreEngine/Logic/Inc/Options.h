/**
 * @file Options.h
 * @author TheWildDeadHero
 * @brief Definitions for game options
 * @version 0.1
 * @date 2022-01-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef GUARD_GAME_OPTIONS_H

/**
 * @brief Defines options for text speed.
 * 
 */
enum e_TextSpeed
{
    SLOW,
    MEDIUM,
    FAST,
    INSTANT,

    NUM_TEXT_SPEEDS
};

typedef struct s_GameOptions
{
    e_TextSpeed text_speed : NUM_TEXT_SPEEDS;

} GameOptions;

bool save_global_options();
bool save_save_options();
bool load_global_options();
bool load_save_options();

#endif // GUARD_GAME_OPTIONS