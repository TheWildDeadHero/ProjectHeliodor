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
enum class e_TypeID : uint16_t
{
    NO_TYPE,        /**< No Type - None-type indicator */

    NORMAL,         /**< Normal Type        */
    FIRE,           /**< Fire Type          */
    WATER,          /**< Water Type         */
    ELECTRIC,       /**< Electric Type      */
    GRASS,          /**< Grass Type         */
    ICE,            /**< Ice Type           */
    FIGHTING,       /**< Fighting Type      */
    POISON,         /**< Poison Type        */
    GROUND,         /**< Groud Type         */
    FLYING,         /**< Flying Type        */
    PSYCHIC,        /**< Psychic Type       */
    BUG,            /**< Bug Type           */
    ROCK,           /**< Rock Type          */
    GHOST,          /**< Ghost Type         */
    DRAGON,         /**< Dragon Type        */
    DARK,           /**< Dark Type          */
    STEEL,          /**< Steel Type         */
    FAIRY,          /**< Fairy Type         */

    UNKNOWN,        /**< Unknown Type - Special type for certain moves */

    BIRD,           /**< Bird Type - Beta move type. Effectively the same as Flying. */
    SOUND,          /**< Sound Type - Custom type for user implementations. */
    GEM,            /**< Gem Type - Custom type for Crystal Onix. Implements said weakness/resistance table.
                         USING THIS FOR AN ATTACK TYPE IS NOT SUPPORTED!! */

    NUM_TYPES       /**< Num Type - Type counter */
};

enum class e_TypeMatchup : uint8_t
{
    NO_EFFECT           = 0U,
    NOT_VERY_EFFECTIVE  = 4U,
    EFFECTIVE           = 8U,
    SUPER_EFFECTIVE     = 16U
};

#endif //GUARD_MONSTER_TYPES_H