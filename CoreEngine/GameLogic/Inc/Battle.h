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
#include "Weather.h"
#include "Types.h"


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

enum class e_BattleLayout
{
    SINGLE,
    DOUBLE,
    TRIPLE,
    ROTATION,
    RAID,
    BATTLE_ROYALE,
    HORDE,
    ONE_ON_TWO,
    TWO_ON_FOUR
};

enum class e_BattleType
{
    WILD,
    TRAINER,
    RANDOM_TRAINER,
    CONTEST,
    SAFARI,
    CATCHING_CONTEST,
};

enum class e_BattleFlags
{
    ROAMER,
    ALLOW_SOS,
    ALLOW_FLEE,
    TRANSFORMED,
    INVERSE,
};

struct s_BattleData
{
    uint16_t time;
    uint16_t environment;
    WeatherType weather;
};

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
    };

    uint8_t data;
};

class Battle
{
    public:
        void clear() { };

    private:

    
};

#endif // GUARD_BATTLE_GENERIC_H