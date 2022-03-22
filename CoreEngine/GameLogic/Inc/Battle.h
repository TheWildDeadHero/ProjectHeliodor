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