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

#ifndef GUARD_MONSTER_TYPE_IDS_H

/**
 * @brief 
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