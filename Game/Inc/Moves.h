/**
 * @file Moves.h
 * @author TheWildDeadHero
 * @brief This file contains all user-mad declarations for moves.
 * @version 0.1
 * @date 2022-01-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef GUARD_MOVE_IDS_H

/**
 * @brief Enumerator used for move IDs.
 * 
 */
enum class e_MoveID
{
    NO_MOVE,

    /* USER CODE - Add custom moves here */

    /* END USER CODE */

    NUM_MOVES
};

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

    /* USER CODE - Add custom moves here */

    /* END USER CODE */

    NUM_EFFECTS
};

enum class e_EffectLogic
{
    ABOVE,
    BELOW,
    AT
};

/**
 * @brief 
 * 
 */
enum class e_EffectRequirement
{
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

    /* USER CODE - Add custom effect requirements here */

    /* END USER CODE */

    NUM_REQUIREMENTS
};

#endif