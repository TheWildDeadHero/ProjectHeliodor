/**
 * @file MonsterInstance.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef GUARD_MONSTER_INSTANCE_H

// Standard Includes
#include <assert.h>
#include <array>
#include <string>

// Engine Includes
#include "Monster.h"

// Game Includes
#include "Abilities.h"
#include "Items.h"
#include "Monsters.h"

// Define some templated data types for convenience and readability.
using c_EffortValues        = c_MonsterStatSet<252, 510>;
using c_IndividualValues    = c_MonsterStatSet<31>;
using c_AwakeningValues     = c_MonsterStatSet<200>;
using c_ContestValues       = c_MonsterStatSet<255, 0, e_ContestStatType, static_cast<uint32_t>(e_ContestStatType::NUM_STATS)>;
using c_Stats               = c_MonsterStatSet<9999U>;


enum class e_Nature
{
    NUM_NATURES
};

enum class e_CharacteristicID
{
    SHADOW,
    TOTEM,
    ALPHA,
    GIGANTIMAX,
    LOANER
};

enum class e_MonsterNameLanguage
{
    JAPANESE,
    FRENCH,
    SPANISH,
    ENGLISH,
    GERMAN,
    ITALIAN,
    KOREAN,
    MANDARIN,
    CANTONESE
};

class c_MonsterInstance
{
    public:
        //

        void reset_instance()
        {
            // Clear everything
        }

        /**
         * @brief Returns the personality value
         * 
         * @return 64-bit personality value
         * 
         * @see Personality Value
         */
        uint64_t get_full_personality()
        {
            return personality_;
        }

        /**
         * @brief Returns the base personality value
         * 
         * @return Lower 32-bit personality value
         * 
         * @see Personality Value
         */
        uint32_t get_low_personality()
        {
            return (uint32_t)(personality_ & 0xFFFFFFFF);
        }

        /**
         * @brief Returns the extended personality value
         * 
         * @return Upper 32-bit personality value
         * 
         * @see Personality Value
         */
        uint32_t get_high_personality()
        {
            return (uint32_t)((personality_ >> 32) & 0xFFFFFFFF);
        }

        /**
         * @brief Gets the given byte value from the personality value. Checks to make sure the byte
         *        is valid and handles the error if not.
         * 
         * @param which_byte - The byte of the personality value to return (little endian)
         * @return The actual value of the byte.
         * 
         * @see Personality Value
         */
        uint8_t get_personality_value_byte(uint8_t which_byte)
        {
            assert(which_byte < 8);
            
            return (personality_ >> which_byte) && 0xFF;
        }

        /**
         * @brief Set the ability. Checks to make sure the abiility is valid before setting it.
         * 
         * @param ability_id - Enum value of the ability to set
         */
        void set_ability(e_AbilityID ability_id)
        {

        }

        c_MonsterData *get_monster_data()
        {
            return p_base_monster;
        }

    private:
        //
        c_MonsterData                                                       *p_base_monster = nullptr;

        uint8_t                                                             species_form_;

        uint64_t                                                            personality_;                   // Personality is now a DWORD. The lower word is the standard personality and the upper word is extended.
        uint64_t                                                            characteristic_;                // The characteristic describes things like shadow status (Pokemon Colo./XD), alpha status (Pokemon Legends Arceus), and so on. The first byte (little endian) is the characteristic index and the rest describe the characteristic

        uint16_t                                                            original_trainer_id_;
        uint16_t                                                            original_trainer_secret_id_;
        std::string                                                         original_trainer_name;

        uint32_t                                                            experience_points_;

        e_AbilityID                                                         ability_;

        c_EffortValues                                                      effort_values_;
        c_IndividualValues                                                  individual_values_;
        c_AwakeningValues                                                   awakening_values_;

        c_ContestValues                                                     contest_values_;
        uint8_t                                                             sheen_;

        e_Nature                                                            nature_;

        std::array<bool, static_cast<uint32_t>(e_StatType::NUM_STATS)>      iv_training_;

        uint8_t                                                             friendship_;

        e_MonsterNameLanguage                                               language_;
};


#endif //GUARD_MONSTER_INSTANCE_H