/**
 * @file PokemonIDs.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef GUARD_MONSTER_IDS_H

/**
 * @brief 
 * 
 */
enum class e_MonsterID
{
    NO_MONSTER,                 /**< No monster */

    /* USER CODE - Add custom monsters here */

    /* END USER CODE */

    NUM_MONSTERS                /**< Counter for the number of monsters in this enum. Has an offset of 1 for NO_MONSTER.*/
};

/**
 * @brief 
 * 
 */
enum class e_SpeciesID
{
    NO_SPECIES,                 /**< No species */

    /* USER CODE - Add custom monsters here */

    /* END USER CODE */

    NUM_SPECIES                 /**< Counter for the number of unique species in this enum. Has an offset of 1 for NO_SPECIES.*/
};

#endif // GUARD_MONSTER_IDS_H