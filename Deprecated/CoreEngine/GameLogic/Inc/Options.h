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

/**
 * @brief Defines battle style options.
 * 
 */
enum class e_BattleStyle
{
    SHIFT,                      /**< Ask the player if they want to swap Pokemon after defeating a foe */
    SET,                        /**< Don't let the player swap Pokemon after defeating a foe */
    ALWAYS_SHIFT                /**< Always bring the player to the Pokemon party screen after defeating a foe */
};

/**
 * @brief This struct keeps track of various game options. Note that only 1 + NUM_SAVE_FILES should ever exist for this
 *        struct.
 * 
 */
struct s_GameOptions
{
    e_TextSpeed text_speed;
    e_BattleStyle battle_style;

    bool nuzlocke_challenge_;
    bool nuzlocke_fail_game_over_;

    uint8_t shiny_rate_;
    uint8_t pokerus_rate_;

    bool enable_memories_;              // Determines whether to display the last four major actions of the player
                                        // when loading a game save or not. Note that this does not stop the game
                                        // from recording said memories.

    bool reset_opening_tutorial_;       // Determines whether to enable the opening tutorial or not

    bool reset_target_if_faint_;        // Determines if a monster retargets their move when the original target faints.
    bool use_move_if_no_target_;        // Determines if a Pokemon still uses their move if the target faints.
    bool pickup_missed_throws_;         // Determine whether to pickup Pokeballs that have missed the Pokemon or been blocked by trainers.
    bool pickup_broken_pokeballs_;      // Determines whether to use the Pokeball Pieces mechanic or not.
};

bool save_global_options();
bool save_save_options();
bool load_global_options();
bool load_save_options();

#endif // GUARD_GAME_OPTIONS