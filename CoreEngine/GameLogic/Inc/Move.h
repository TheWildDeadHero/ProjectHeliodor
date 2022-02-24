/**
 * @file Move.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdint.h>
#include <assert.h>

#include "Moves.h"
#include "Types.h"

/**
 * @brief 
 * 
 */
enum class e_MoveEffectID
{
    NO_EFFECT,

    INFLICT_DAMAGE,
    RECOVER,
    INCREASE_STATS,
    DECREASE_STATS,
    INFLICT_STATUS,
    INFLICT_CONDITION,
    CHANGE_FIELD,
    CHANGE_WEATHER,
    CHANGE_GRAVITY,
    PREVENT_PHYSICAL_DAMAGE,
    PREVENT_SPECIAL_DAMAGE,
    PREVENT_STAT_DECREASE,
    PREVENT_STAT_INCREASE,
    RESET_STAT_CHANGES,
    SET_TRAP,
    SET_SUBSTITUE,
    SET_FUTURE_ATTACK,
    SET_FUTURE_RECOVER,
    SET_FUTURE_STATUS,
    SET_FUTURE_CONDITION,
    AVOID_RESISTANCE,
    AVOID_WEAKNESS,
    ADD_RESISTANCE,
    ADD_WEAKNESS,
    LEAVE_ONE_HP,
    MAKE_TIRED,
    REMOVE_TYPE,
    ADD_TYPE,
    ONE_HIT_KNOCKOUT,
    ONLY_ALLOW_PHYSICAL_ATTACKS,
    ONLY_ALLOW_SPECIAL_ATTACKS,
    ONLY_ALLOW_STATUS_ATTACKS,
    RANDOM_ATTACK,
    RANDOM_FOE_ATTACK,
    RANDOM_PARTY_ATTACK,
    TRANSFORM,
    FLEE,
    CHANGE_PARTY_MEMBER_SELECT,
    CHANGE_PARTY_MEMBER_RANDOM,
    CHANGE_PARTY_MEMBER_NEXT,
    CHANGE_CRIT_CHANCE,
    SET_TARGET,

    NUM_EFFECTS
};

enum class e_EffectLogic
{
    NOT_APPLICABLE,

    ABOVE,
    BELOW,
    AT,

    NUM_LOGIC
};

/**
 * @brief 
 * 
 */
enum class e_EffectRequirement
{
    NO_REQUIREMENT,

    LEVEL,
    OPPONENT_LEVEL,
    STAT_VALUE,
    HAS_CONDITION,
    HAS_STATUS,
    HAS_MOVE,
    HAS_ABILITY,
    IS_TYPE,
    HAS_WEAKNESS,
    HAS_RESISTANCE,
    FIELD_IS,
    TRAP_IS_SET,
    IS_GRAVITY,
    IS_WEATHER,
    IS_SEASON,
    IS_DARK,
    IS_TIME_OF_DAY,
    USED_MOVE,
    NUM_TURNS_ELAPSED,

    NUM_REQUIREMENTS
};

/**
 * @brief 
 * 
 */
enum class e_StatusIDs
{
    PARALYZE,
    FREEZE,
    BURN,
    FROST_BITE,
    POISON,
    HEAVY_POISON,
    SLEEP
};

/**
 * @brief 
 * 
 */
enum class e_ConditionIDs
{
    CONFUSED,
    INFATUATED,
    ENRAGED,
    DROWSY,
};

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
    MAKES_CONTACT,

    NUM_PROPERTIES
};

struct s_AffectMatrix
{
    /* The fundamental idea here is to capture all possible targeting combinations
    *  using a relatively simple data structure. This begets the need for a bunch
    *  of flags and bespoke, explicit logic.
    * 
    *  Target Width - How far away a monster can target with the attack.
    *  Affect Wdith - How far away from the target the effect spreads (splash).
    *  Targets Allies - Targets the player's monsters and any AI-controlled monsters
    *                   on the player's team.
    *  Targets Party - Targets Pokemon in the player's party
    *  Targets Enemies - Targets any enemy monsters.
    */
    uint8_t target_width_;
    uint8_t affect_width_;

    bool targets_allies_;
    bool targets_party_;
    bool target_enemies_;
};

/**
 * @brief 
 * 
 */
class c_MoveData
{
    public:



    private:
        e_MoveID        id_;

        uint8_t         pp_;

        e_MoveEffectID effects_[8];
};

class c_MoveEffect
{
    public:
        void set_properties(uint32_t mask)
        {
            // Check to make sure the mask is valid.
            assert(mask >> static_cast<uint32_t>(e_MoveProperties::NUM_PROPERTIES) == 0);

            properties_mask_ = mask;
        }

    private:
        e_TypeID        type_;
        e_MoveKind      kind_;

        uint32_t        properties_mask_;

        uint8_t         power_;

        s_AffectMatrix  affects_whom_;
};

class c_BattleMove
{
    c_MoveData  *p_move_data_;
    uint8_t     num_pp_ups_;
    uint8_t     pp_left_;
};