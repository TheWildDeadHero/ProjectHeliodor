/**
 * @file Battle.h
 * @author TheWildDeadHero
 * @brief 
 * @version 0.1
 * @date 2022-01-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef GUARD_BATTLE_GENERIC_H

#include <stdint.h>

#include "Moves.h"
#include "Types.h"

/**
 * @brief Enumeration of the kind of move (Physical/Special split)
 * 
 */
enum class e_MoveKind
{
    PHYSICAL,
    SPECIAL,
    STAT,

    NUM_KINDS
};

enum class e_MoveProperties
{
    NO_PROPERTIES,
    SOUND,
    ELEMENTAL,

    NUM_PROPERTIES
};

struct s_AffectMatrix
{
    uint8_t target_width_;
    uint8_t affect_width_;

    bool targets_self_;
    bool targets_allies_;
    bool targets_party_;
};

/**
 * @brief 
 * 
 */
class c_Move
{
    public:



    private:
        e_MoveID        id_;

        e_TypeID        type_;

        e_MoveKind      kind_;
        bool            properties_[static_cast<uint32_t>(e_MoveProperties::NUM_PROPERTIES) - 1];

        uint8_t power_;
        uint8_t accuracy_;
        uint8_t pp_;

        s_AffectMatrix affects_whom_;

        e_MoveEffectID effects_[8];
};

class c_BattleAction
{

}

#endif // GUARD_BATTLE_GENERIC_H