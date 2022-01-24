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

#include <stdint.h>

/**
 * @brief Defines options for text speed.
 * 
 */
enum class e_TextSpeed
{
    SLOW,
    MEDIUM,
    FAST,
    INSTANT,

    NUM_TEXT_SPEEDS
};

struct s_GameOptions
{
    e_TextSpeed text_speed : static_cast<uint8_t>(e_TextSpeed::NUM_TEXT_SPEEDS);

    bool nuzlocke_challenge_;
    bool nuzlocke_fail_game_over_;
};

bool save_global_options();
bool save_save_options();
bool load_global_options();
bool load_save_options();

#endif // GUARD_GAME_OPTIONS