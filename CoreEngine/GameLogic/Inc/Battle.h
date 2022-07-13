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
#include "BattleMonster.h"


enum class e_StageStatType
{
    ATTACK,             /**< Physical attack power */
    DEFENSE,            /**< Physical defense */
    SPECIAL_ATTACK,     /**< Special attack power */
    SPECIAL_DEFENCE,    /**< Special defense */
    ACCURACY,           /**< Accuracy */
    EVASIVENESS,        /**< Evasiveness */

    NUM_STATS           /**< Counter value */
};

enum class e_BattleType
{
    SINGLE,
    DOUBLE,
    TRIPLE,
    ROTATION,
    RAID,
    BATTLE_ROYALE
}

union u_PartySetup
{
    struct
    {
        bool slot_1 : 1;
        bool slot_2 : 1;
        bool slot_3 : 1;
        bool slot_4 : 1;
        bool slot_5 : 1;
        bool slot_6 : 1;
        bool slot_7 : 1;
        bool slot_8 : 1;
    }

    uint8_t data;
}

enum class e_BattleFlags
{
    WILD,
    TRAINER,
    ROAMER,
}

class Battle
{
    public:
        void clear() { };

    private:

    
}

#endif // GUARD_BATTLE_GENERIC_H