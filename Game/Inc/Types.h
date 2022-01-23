/**
 * @file Types.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef GUARD_MONSTER_TYPES_H

/**
 * @brief 
 * 
 */
enum e_TypeID
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

    /* USER CODE - Add custom types here */
    /* Make sure to edit the type table in the associated source file */

    // SOUND,
    // GEM,

    /* END USER CODE */

    NUM_TYPES
};

#endif //GUARD_MONSTER_TYPES_H