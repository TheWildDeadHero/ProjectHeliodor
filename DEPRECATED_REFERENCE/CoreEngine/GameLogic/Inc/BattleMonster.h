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

using c_BattleStatStages    = c_MonsterStatSet<MAX_STAT_STAGE_VALUE, 0, e_StageStatType, static_cast<uint32_t>(e_StageStatType::NUM_STATS)>;

class c_BattleMonster
{
    public:
    
        void add_experience(uint32_t experience_points);
       
    private:
        void calculate_stats();

        c_MonsterInstance *instance_data_;

        c_BattleStats stats_;
};