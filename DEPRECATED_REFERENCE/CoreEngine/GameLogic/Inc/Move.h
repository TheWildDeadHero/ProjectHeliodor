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
#include <array>
#include <string>

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
    HEAL_STATUS,
    INFLICT_CONDITION,
    HEAL_CONDITION,
    CHANGE_PRIORITY,
    CHANGE_FIELD,
    CHANGE_WEATHER,
    CHANGE_GRAVITY,
    PREVENT_PHYSICAL_DAMAGE,
    PREVENT_SPECIAL_DAMAGE,
    PREVENT_ALL_DAMAGE,
    PREVENT_STAT_DECREASE,
    PREVENT_STAT_INCREASE,
    RESET_STAT_CHANGES,
    SET_TRAP,
    SET_SUBSTITUE,
    SET_FUTURE_ATTACK,
    SET_FUTURE_RECOVER,
    SET_FUTURE_STATUS,
    SET_FUTURE_CONDITION,
    CHANGE_RESISTANCE,
    CHANGE_WEAKNESS,
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
    CHANGE_PARTY_MEMBER_SELECT,
    CHANGE_PARTY_MEMBER_RANDOM,
    CHANGE_PARTY_MEMBER_NEXT,
    CHANGE_CRIT_CHANCE,
    SET_TARGET,
    CHANGE_WEATHER,
    CHANGE_FIELD,
    CHANGE_GRAVITY,
    CHANGE_MONSTER,
    CHANGE_FORM,
    TRANSFORM,
    CALL_FOR_HELP,
    FLEE,
    FORFEIT,

    NUM_EFFECTS
};

enum class e_MoveEffectLogic
{
    NOT_APPLICABLE,

    ABOVE,
    ABOVE_OR_IS,
    BELOW,
    BELOW_OR_IS,
    IS,
    IS_NOT,

    NUM_LOGIC
};

/**
 * @brief 
 * 
 */
enum class e_MoveEffectRequirementID
{
    NO_REQUIREMENT,

    LEVEL,
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
    USED_TYPE_MOVE,
    NUM_TURNS_ELAPSED,
    HAS_FRIENDSHIP_LEVEL,
    IS_GENDER,
    IS_USING_MOVE,
    IS_MONSTER,

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
    SLEEP,

    NUM_STATUS_IDS
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

    NUM_CONDITION_IDS
};

/**
 * @brief Enumeration of the kind of move (Physical/Special split)
 * 
 */
enum class e_MoveEffectKind
{
    UNUSED,

    PHYSICAL,
    SPECIAL,
    STAT,
    SECONDARY_EFFECT,

    NUM_KINDS
};

/**
 * @brief 
 * 
 */
enum class e_MoveProperties
{
    NO_PROPERTIES,

    SOUND,
    ELEMENTAL,
    MAKES_CONTACT,

    NUM_PROPERTIES
};

/**
 * @brief 
 * 
 */
enum class e_MovePriorityFlags
{
    STANDARD_PRIORITY,

    ALWAYS_LAST,
    ALWASY_FIRST,
    AFTER_PRIMARY_EFFECT,
    BEFORE_PRIMARY_EFFECT,
    BEFORE_SWITCH,

    NUM_PRIORITY_FLAGS
};

/**
 * @brief 
 * 
 */
union u_MoveEffectData
{
    uint16_t num_points;
    uint8_t percent;
    uint8_t num_stages;
    uint8_t num_turns;
    e_StatusIDs status;
    e_ConditionIDs condition;

};

/**
 * @brief 
 * 
 */
struct s_MoveEffectRequirementInfo
{
    e_MoveEffectRequirementID requirement_;
    e_MoveEffectLogic logic_;
    
    u_MoveEffectData data_;

    bool check_target_;                             /**< Determines whether to check the
                                                     *   target of the effect or the user
                                                     */
};

/**
 * @brief 
 * 
 */
struct s_MovePriorityInfo
{
    uint8_t priority_;

    e_MovePriorityFlags flag_;

    static const uint8_t priority_offset_;
};

/**
 * @brief The fundamental idea here is to capture all possible targeting combinations
 *  using a relatively simple data structure. This begets the need for a bunch
 *  of flags and bespoke, explicit logic.
 * 
 *  Target Width    - How far away a monster can target with the attack.
 *  Affect Wdith    - How far away from the target the effect spreads (splash).
 *  Targets Allies  - Targets the player's monsters and any AI-controlled monsters
 *                    on the player's team.
 *  Targets Party   - Targets Pokemon in the player's party
 *  Targets Enemies - Targets any enemy monsters.
 * 
 */
struct s_MoveAffectInfo
{
    enum
    {
        SELF,        
        ALLIES,
        PARTY,
        ENEMIES,

        NUM_TARGET_TYPES
    };

    uint8_t target_width_;
    uint8_t affect_width_;

    bool targets_[NUM_TARGET_TYPES];

    bool random_target_;
};

/**
 * @brief 
 * 
 */
struct s_MoveEffect
{
    e_TypeID                        type_;
    e_MoveEffectKind                kind_;

    uint8_t                         effect_chance_;

    uint32_t                        properties_mask_;
    uint32_t                        priority_;

    u_MoveEffectData                data_1_;

    s_MoveAffectInfo                affects_whom_;
    s_MoveEffectRequirementInfo     requirement_;
};

/**
 * @brief 
 * 
 */
struct s_MoveData
{
    e_MoveID        id_;
    std::string     name_;

    uint8_t         base_pp_;

    std::array<e_MoveEffectID, 8U> effects_;

    e_MoveEffectID *primary_effect_;

    uint8_t num_secondary_effects_;       
};

/**
 * @brief 
 * 
 */
class c_BattleMove
{
    s_MoveData  *p_move_data_;
    uint8_t     num_pp_ups_;
    uint8_t     pp_left_;
};