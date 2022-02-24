/**
 * @file MonsterStorage.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <array>

#include "MonsterInstance.h"

namespace n_MonsterStorageData
{
    const uint32_t NUM_BOXES                = 32;
    const uint32_t NUM_PLAYER_PARTIES       = 4;          // 1 active party, 1 battle-ready party, and 2 simulation parties
    const uint32_t NUM_MONSTERS_PER_BOX     = 30;
    const uint32_t NUM_MONSTERS_PER_PARTY   = 6;

    const uint32_t TOTAL_NUM_MONSTERS       = NUM_BOXES * NUM_MONSTERS_PER_BOX * NUM_PLAYER_PARTIES * NUM_MONSTERS_PER_PARTY;
}

using a_Party   = std::array<c_MonsterInstance*, n_MonsterStorageData::NUM_MONSTERS_PER_PARTY>;
using a_Box     = std::array<c_MonsterInstance*, n_MonsterStorageData::NUM_MONSTERS_PER_BOX>;

static std::array<c_MonsterInstance, n_MonsterStorageData::TOTAL_NUM_MONSTERS> all_player_monsters_;

static a_Party players_party_;

/**
 * @brief 
 * 
 */
class c_MonsterPC : public c_MonsterStorageUnit<30 * 32>
{
    public:



    private:
        char box_names_[32][18];

        const uint32_t NUM_BOXES = 32;

};

class c_MonsterParty : public c_MonsterStorageUnit<6>
{

};