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

#include <assert.h>

#include "BaseMonster.h"
#include "Abilities.h"
#include "Items.h"
#include "Monsters.h"


enum class e_Nature
{
    NUM_NATURES
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
         * @return 32-bit personality integer
         */
        uint32_t get_personality_value()
        {
            return personality_value_;
        }

        /**
         * @brief Gets the given byte value from the personality value. Checks to make sure the byte
         *        is valid and handles the error if not.
         * 
         * @param which_byte - The byte of the personality value to return (little endian)
         * @return The actual value of the byte.
         */
        uint8_t get_personality_value_byte(uint8_t which_byte)
        {
            assert(which_byte < 4);
            
            return (personality_value_ >> which_byte) && 0xFF;
        }

        /**
         * @brief Set the ability. Checks to make sure the abiility is valid before setting it.
         * 
         * @param ability_id - Enum value of the ability to set
         */
        void set_ability(e_AbilityID ability_id)
        {

        }

        c_BaseMonster *get_base_monster()
        {
            return p_base_monster;
        }

    private:
        //
        c_BaseMonster                   *p_base_monster = nullptr;

        uint8_t                         species_form_;

        uint32_t                        personality_value_;

        uint16_t                        original_trainer_id_;
        uint16_t                        original_trainer_secret_id_;
        uint16_t                        original_trainer_name[18];

        uint32_t                        experience_points_;

        e_AbilityID                     ability_;

        c_MonsterStatSet<252, 510>      effort_values_;
        c_MonsterStatSet<31>            individual_values_;
        c_MonsterStatSet<200>           awakening_values_;

        bool                            is_egg_;
        bool                            has_hidden_ability_;

        e_Nature                        nature_;



};


#endif //GUARD_MONSTER_INSTANCE_H