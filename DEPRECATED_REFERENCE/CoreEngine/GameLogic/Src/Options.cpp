/**
 * @file Options.cpp
 * @author TheWildDeadHero
 * @brief 
 * @version 0.1
 * @date 2022-01-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Options.h"

static s_GameOptions global_game_options;
static s_GameOptions save_game_options;

/**
 * @brief Saves the options that are used globally.
 * 
 * @return Whether the save was successful or not
 */
bool save_global_options()
{
    return true;
}

/**
 * @brief Saves the options and notes for individual saves.
 * 
 * @return Whether the save was successful or not
 */
bool save_save_options()
{
    return true;
}

/**
 * @brief Load the options used globally.
 * 
 * @return Whether the options were successfully loaded or not
 */
bool load_global_options()
{
    return true;
}

/**
 * @brief Load the options used for individual saves.
 * 
 * @return Whether the options were successfully loaded or not
 */
bool load_save_options()
{
    return true;
}