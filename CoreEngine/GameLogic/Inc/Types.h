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
    NO_TYPE,        /**< No Type - None-type indicator */

    NORMAL,         /**< Normal Type        */
    FIRE,           /**< Fire Type          */
    FIGHTING,       /**< Fighting Type      */
    WATER,          /**< Water Type         */
    FLYING,         /**< Flying Type        */
    GRASS,          /**< Grass Type         */
    POISON,         /**< Poison Type        */
    ELECTRIC,       /**< Electric Type      */
    GROUND,         /**< Groud Type         */
    PSYCHIC,        /**< Psychic Type       */
    ROCK,           /**< Rock Type          */
    ICE,            /**< Ice Type           */
    BUG,            /**< Bug Type           */
    DRAGON,         /**< Dragon Type        */
    GHOST,          /**< Ghost Type         */
    DARK,           /**< Dark Type          */
    STEEL,          /**< Steel Type         */
    FAIRY,          /**< Fairy Type         */

    UNKOWN,         /**< Unknown Type - Special type for certain moves */

    BIRD,           /**< Bird Type - Beta move type. Effectively the same as Flying. */
    SOUND,          /**< Sound Type - Custom type for user implementations. */
    GEM,            /**< Gem Type - Custom type for Crystal Onix. Implements said weakness/resistance table.
                         USING THIS FOR AN ATTACK TYPE IS NOT SUPPORTED!! */

    /* USER CODE - Add custom types here */
    /* Make sure to edit the type table in the associated source file!! */

    /* END USER CODE */

    NUM_TYPES       /**< Num Type - Type counter */
};

#endif //GUARD_MONSTER_TYPES_H