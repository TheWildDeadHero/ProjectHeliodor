/**
 * @file Abilities.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef GUARD_ABILITY_IDS_H


enum class e_AbilityID
{
    NO_ABILITY,



    NUM_ABILITIES
};

enum class e_PropertiesID
{
    NO_PROPERTIES,      /**< No properties. Not valid except for properties mask. */

    CUTE,               /**< If the monster looks cute */
    UGLY,               /**< If the monster looks ugly */
    COOL,               /**< If the monster looks cool */
    TOUGH,              /**< If the monster looks tough */

    IS_BABY,            /**< If the monster is a baby or not */

    HAS_HANDS,          /**< If the monster can hold and use human tools or not */

    FLYER,              /**< If the monster flies or floats */
    AQUATIC,            /**< If the monster can breathe under water */

    LIGHT_IMMUNE,       /**< If the monster is immune from light-based attacks */
    SOUND_IMMUNE,       /**< If the monster is immune from sound-based attacks */

    PHYSICAL_IMMUNE,    /**< If the monster is immune from physical attacks */
    SPECIAL_IMMUNE,     /**< If the monster is immune from special attacks */

    CONTACT_IMMUNE,     /**< If the monster is immune from moves that make contact */

    FREEZE_IMMUNE,      /**< If the monster is immune from being frozen */
    BURN_IMMUNE,        /**< If the monster is immune from being burned */
    PARALYZE_IMMUNE,    /**< If the monster is immune from being paralyzed */
    POISON_IMMUNE,      /**< If the monster is immune from being poisoned */
    SLEEP_IMMUNE,       /**< If the monster is immune from being put to sleep */

    CONFUSE_IMMUNE,     /**< If the monster is immune from being confused */
    INFATUATION_IMMUNE, /**< If the monster is immune from being infatuated */
    RAGE_IMMUNE,        /**< If the monster is immune from being enraged */

    NUM_PROPERTIES      /**< Counter for enum. Has an offset of one. */
};

#endif