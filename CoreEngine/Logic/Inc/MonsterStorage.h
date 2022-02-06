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

#include "MonsterInstance.h"

template <uint16_t NUM_MONSTERS>
class c_MonsterStorageUnit
{
    public:

    void select_monster(uint16_t which_monster)
    {

    }


    protected:
        c_MonsterInstance monsters_[NUM_MONSTERS];

        const uint16_t MAX_MONSTER_INDEX = NUM_MONSTERS;
};

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