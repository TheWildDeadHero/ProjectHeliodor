/**
 * @file Types.h
 * @author TheWildDeadHero
 * @brief This file contains ann declarations of in relation to types.
 * @version 0.1
 * @date 2022-01-23
 * 
 * @copyright Copyright (c) 2022
 * 
 * @note When using this engine, edit this file (as well as the associated source file) in
 *       order to add new types. In order to maintain compatibility, only add types where
 *       indicated in the code.
 * 
 */

#ifndef GUARD_MONSTER_TYPE_IDS_H

/**
 * @brief Enumerator that keeps track of the types in the game.
 * 
 */
enum class e_TypeID
{
    NO_TYPE,

    NORMAL,
    FIRE,
    FIGHTING,
    WATER,
    FLYING,
    GRASS,
    POISON,
    ELECTRIC,
    GROUND,
    PSYCHIC,
    ROCK,
    ICE,
    BUG,
    DRAGON,
    GHOST,
    DARK,
    STEEL,
    FAIRY,
    UNKOWN,

    SOUND,
    GEM,

    /* USER CODE - Add custom types here */
    /* Make sure to edit the type table in the associated source file */

    /* END USER CODE */

    NUM_TYPES
};

#endif //GUARD_MONSTER_TYPES_H