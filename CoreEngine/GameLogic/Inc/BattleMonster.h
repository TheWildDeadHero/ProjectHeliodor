/**
 * @file BattleMonster.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "MonsterInstance.h"
#include "Battle.h"

static const uint8_t MAX_STAT_STAGE_VALUE = 7U;

using c_BattleStats         = c_MonsterStatSet<9999U>;
using c_BattleStatStages    = c_MonsterStatSet<MAX_STAT_STAGE_VALUE, 0, e_StageStatType, static_cast<uint32_t>(e_StageStatType::NUM_STATS)>;

class c_BattleMonster
{
    public:
       
    private:
       c_MonsterInstance *instance_data_;

       c_BattleStats stats_;
};