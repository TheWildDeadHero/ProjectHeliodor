/**
 * @file BaseMonster.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef GUARD_BASE_MONSTER_H

// Standard Includes
#include <stdint.h>
#include <assert.h>
#include <string>
#include <array>

// Project Includes
#include "Monsters.h"
#include "Types.h"
#include "Items.h"
#include "Abilities.h"
#include "FieldEffects.h"

/**
 * @brief Enum indicies used for monster properties. Will primarily be used for bitmasking.
 * 
 */
enum class e_PropertiesID
{
    NO_PROPERTIES,      /**< No properties. Not valid except for properties mask. */

    CUTE,               /**< If the monster looks cute */
    UGLY,               /**< If the monster looks ugly */
    COOL,               /**< If the monster looks cool */
    TOUGH,              /**< If the monster looks tough */

    IS_BABY,            /**< If the monster is a baby or not */

    HAS_HANDS,          /**< If the monster can hold and use human tools or not */

    FLYER,              /**< If the monster flies */
    FLOATER,            /**< If the monster floats */
    SWIMMER,            /**< If the monster can swim in water */
    DIVER,              /**< If the monster can breathe under water */

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

/**
 * @brief Enum indices for stat types.
 * 
 */
enum class e_StatType
{
    HP,                 /**< Hit points */
    ATTACK,             /**< Physical attack power */
    DEFENSE,            /**< Physical defense */
    SPEED,              /**< Turn order */
    SPECIAL_ATTACK,     /**< Special attack power */
    SPECIAL_DEFENCE,    /**< Special defense */

    NUM_STATS           /**< Counter value */
};

/**
 * @brief 
 * 
 */
enum class e_ContestStatType
{
    CUTE,
    SMART,
    COOL,
    BEAUTIFUL,
    TOUGH,

    NUM_STATS
};

/**
 * @brief 
 * 
 */
enum class e_EggGroup
{
    NO_EGG_GROUP,

    MONSTER,
    HUMAN_LIKE,
    WATER_1,
    WATER_2,
    WATER_3,
    BUG,
    MINERAL,
    FLYING,
    AMORPHOUS,
    FIELD,
    FAIRY,
    DITTO,
    GRASS,
    DRAGON,
    NO_EGGS,
    GENDER_UNKNOWN,

    NUM_EGG_GROUPS
};

/**
 * @brief 
 * 
 */
enum class e_ExperienceGainCurve
{
    ERRATIC,            /**<   */
    FAST,               /**<   */
    MEDIUM_FAST,        /**<   */
    MEDIUM_SLOW,        /**<   */
    SLOW,               /**<   */
    FLUCTUATING         /**<   */
};

/**
 * @brief 
 * 
 * @tparam MAX_VALUE 
 */
template <uint16_t MAX_VALUE = 255, uint32_t MAX_TOTAL = 0, class e_STAT_ENUM = e_StatType, uint32_t NUM_STATS = static_cast<uint32_t>(e_StatType::NUM_STATS)>
class c_MonsterStatSet
{
    public:

        /**
         * @brief Method that adds a given value to the provided stat.
         * 
         * @param which_stat - Enum identifier to be casted to a usable index for the stat array.
         * @param value - The value to add to the current stat value
         */
        void add_value(e_STAT_ENUM which_stat, uint16_t value)
        {
            if (index_is_valid(which_stat))
                {
                uint16_t *p_stat = &stats_[static_cast<uint32_t>(which_stat)];
                uint32_t temp_sum;

                // Lob off any values that are too high.
                if (value > MAX_VALUE)
                {
                    value = MAX_VALUE;
                }

                // If a max total has been provided, check to make sure the total of the stats does
                // not exceed it.
                if (MAX_TOTAL > 0 && stat_total() + value > MAX_TOTAL)
                {
                    temp_sum = *p_stat + ((stat_total() + value) - MAX_TOTAL);
                }
                else
                {
                    temp_sum = *p_stat + value;
                }

                // Make sure that the stat value is capped at the max value.
                if (temp_sum > MAX_VALUE)
                {
                    *p_stat = MAX_VALUE;
                }
                else
                {
                    *p_stat += uint16_t(sum); // Demote the sum back to a 16-bit int.
                }
            }
        }

        /**
         * @brief Method that subtracts a given value from the provided stat.
         * 
         * @param which_stat - Enum identifier to be casted to a usable index for the stat array.
         * @param value - The value to subtract from the current stat value
         */
        void subtract_value(e_STAT_ENUM which_stat, uint16_t value)
        {
            if (index_is_valid(which_stat))
                {
                uint16_t *p_stat = &stats_[static_cast<uint32_t>(which_stat)];

                // make sure we don't underflow.
                if (value > *p_stat)
                {
                    *p_stat = 0;
                }
                else
                {
                    *p_stat -= value;
                }
            }
        }

    private:

        /**
         * @brief Convenience method that checks to see if the index is valid
         * 
         * @param which_stat - The stat enumeration
         * @return Whether the index is valid or not.
         * 
         * @note This function should not return if the index is invalid, as the game should exit
         *       after the error is handled if an invalid index is found.
         */
        bool index_is_valid(e_STAT_ENUM which_stat)
        {
            assert(static_cast<uint32_t>(which_stat) < NUM_STATS)

            return true;
        }

        /**
         * @brief Get the total of all stat values.
         * 
         * @return The numeric total.
         */
        uint32_t stat_total()
        {
            uint32_t total = 0;

            for (auto stat : stats_)
            {
                total += stat;
            }

            return total;
        }

        uint16_t stats_[NUM_STATS] = {0};
};

/**
 * @brief The Monster class holds all data 
 * 
 */
class c_MonsterData
{
    public:

        /**
         * @brief Constructs a baseline monster. Everything is set to effectively be blank.
         * 
         */
        c_MonsterData()
        {

        }

        c_MonsterData(e_MonsterID species, e_TypeID type_1, e_TypeID type_2)
        {

        }

        void load_monster_info();


    private:
        /**
         * @brief Sets the species using an unsigned integer instead of the MonsterID enum. Checks to see if
         *        the species ID is valid before setting and if not, throws an error.
         * 
         * @param species - 32-bit integer species identifier
         */
        void set_species(uint32_t species)
        {
            assert(species < static_cast<uint32_t>(e_MonsterID::NUM_MONSTERS));

            // set species
        }

        /**
         * @brief Set the species using the e_MonsterID enum. Checks to make sure the species is valid.
         * 
         * @param species - Species identifier as defined in the e_MonsterID enum
         */
        void set_species(e_MonsterID species)
        {
            assert(species < e_MonsterID::NUM_MONSTERS);

            // set species
        }

        e_MonsterID                 monster_;
        e_SpeciesID                 species_;

        std::string                 name_;

        std::array<e_TypeID, 2>     types_;

        c_MonsterStatSet<>          base_stats_;

        uint8_t                     experience_point_yield_;
        c_MonsterStatSet<16>        effort_value_yield_;

        uint8_t                     gender_ratio_;
        uint8_t                     capture_rate_;

        std::array<e_ItemID, 2>     held_items_;
        std::array<e_ItemID, 2>     hidden_held_items;
        std::array<e_ItemID, 2>     pickup_items_;

        uint8_t                     egg_cycles_;
        std::array<e_EggGroup, 2>   egg_groups_;

        uint8_t                     base_friendship_;

        std::array<e_AbilityID, 2>  abilities_;
        std::array<e_AbilityID, 2>  hidden_abilities_;

        uint32_t                    properties_mask_;
        uint32_t                    field_abilities_mask_;
};

#endif // GUARD_BASE_MONSTER_H