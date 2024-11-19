/**
 * @file Types.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdint.h>
#include <assert.h>

#include "Types.h"

const uint8_t none      = static_cast<uint8_t>(e_TypeMatchup::NO_EFFECT);
const uint8_t half      = static_cast<uint8_t>(e_TypeMatchup::NOT_VERY_EFFECTIVE);
const uint8_t norm      = static_cast<uint8_t>(e_TypeMatchup::EFFECTIVE);
const uint8_t doub      = static_cast<uint8_t>(e_TypeMatchup::SUPER_EFFECTIVE);

/**
 * @brief 
 * 
 */
static const uint8_t m_TypeMatchupTable[][static_cast<uint16_t>(e_TypeID::NUM_TYPES) - 1] = 
{
    /*                      (1)   (2)   (3)   (4)   (5)   (6)   (7)   (8)   (9)   (10)  (11)  (12)  (13)  (14)  (15)  (16)  (17)  (18)          (19)  (20)  (21)  (22)
    /*Normal    (1) */  {   norm, norm, norm, norm, norm, norm, norm, norm, norm, norm, norm, norm, half, none, norm, norm, half, norm,         norm, norm, norm, norm  },
    /*Fire      (2) */  {   norm, half, half, norm, doub, doub, norm, norm, norm, norm, norm, doub, half, norm, half, norm, doub, norm,         norm, norm, norm, norm  },
    /*Water     (3) */  {   norm, doub, half, norm, half, norm, norm, norm, doub, norm, norm, norm, doub, norm, half, norm, norm, norm,         norm, norm, norm, half  },
    /*Electric  (4) */  {   norm, norm, doub, half, half, norm, norm, norm, none, doub, norm, norm, norm, norm, norm, norm, norm, norm,         norm, norm, norm, norm  },
    /*Grass     (5) */
    /*Ice       (6) */
    /*Fighting  (7) */
    /*Poison    (8) */
    /*Ground    (9) */
    /*Flying    (10)*/
    /*Psychic   (11)*/
    /*Bug       (12)*/
    /*Rock      (13)*/
    /*Ghost     (14)*/
    /*Dragon    (15)*/
    /*Dark      (16)*/
    /*Steel     (17)*/
    /*Fairy     (18)*/

    /*Unknown   (19)*/  {   norm, norm, norm, norm, norm, norm, norm, norm, norm, norm, norm, norm, norm, norm, norm, norm, norm, norm,         norm, norm, norm, norm  },
    /*Bird      (20)*/
    /*Sound     (21)*/
    /*Gem       (22)*/
};

void inline check_type_validity(const uint16_t type_index)
{
    assert(0U > type_index && static_cast<uint16_t>(e_TypeID::NUM_TYPES) < type_index);
}

uint8_t get_type_matchup(const e_TypeID attack, const e_TypeID defence)
{
    const uint16_t attack_index   = static_cast<uint16_t>(attack);
    const uint16_t defence_index  = static_cast<uint16_t>(defence);

    check_type_validity(attack_index);
    check_type_validity(defence_index);

    uint8_t result;

    result = m_TypeMatchupTable[attack_index][defence_index];
    
    return result;
}