///
/// @file abilities.hpp
///
/// @brief This file contains an enum for all ability indices.
///
/// @addtogroup Abilities
/// @{

#ifndef GUARD_CONSTANTS_BATTLE_AI_H
#define GUARD_CONSTANTS_BATTLE_AI_H

// For non-GBA environments.
#include "port_types.hpp"
#include "to_int.hpp"

namespace BattleAI
{
    /// Mangle the name
    constexpr u8 __BASE_EFFECTIVE = 40U;

    enum class Battlers : u8
    {
        // All Battle Modes
        TARGET,
        USER,

        // All battle modes where each team has more than one monster on the field
        TARGET_ALL_PARTNERS,
        USER_ALL_PARTNERS,

        // 3v3, Rotation, Horde only (only on opposide)
        TARGET_L_PARTNER,
        TARGET_R_PARTNER,
        TARGET_FAR_L_PARTNER,
        TARGET_FAR_R_PARTNER,
        USER_L_PARTNER,
        USER_R_PARTER,
        USER_FAR_L_PARTNER,
        USER_FAR_R_PARTNER,

        // Battle Royale only
        TARGET_LEFT_CORNER,
        TARGET_FAR_CORNER,
        TARGET_RIGHT_CORNER,

        // Horde Only
        USER_HOSTILE,
        USER_FRIENDLY,
        USER_ALL_HOSTILE,
        USER_ALL_FRIENDLY,        

        COUNT
    };

    enum class GetType : u8
    {
        TYPE_1_TARGET,
        TYPE_2_TARGET,
        TYPE_1_USER,
        TYPE_2_USER,
        TYPE_MOVE,

        COUNT
    };

    enum class Effectiveness : u8
    {
        x4    = __BASE_EFFECTIVE * 4U,
        x2    = __BASE_EFFECTIVE * 2U,
        x1    = __BASE_EFFECTIVE,
        x0_5  = __BASE_EFFECTIVE / 2U,
        x0_25 = __BASE_EFFECTIVE / 4U,
        x0    = __BASE_EFFECTIVE * 0U,

        COUNT = 6U
    };

    /// @todo - Implement weather in separate file with its own distinct functionality
    enum class Weather : u8
    {
        SUN,
        RAIN,
        SANDSTORM,
        HAIL,
        SNOW,
        ACID_RAIN,

        COUNT
    };

    enum class Power : u8
    {
        MOST,
        NOT_MOST,
        OTHER,

        COUNT
    };

    enum class ScriptBits : u32
    {
        CHECK_BAD_MOVE        = (1 << 0),
        TRY_TO_FAINT          = (1 << 1),
        CHECK_VIABILITY       = (1 << 2),
        SETUP_FIRST_TURN      = (1 << 3),
        RISKY                 = (1 << 4),
        PREFER_POWER_EXTREMES = (1 << 5),
        PREFER_BATON_PASS     = (1 << 6),
        DOUBLE_BATTLE         = (1 << 7),
        HP_AWARE              = (1 << 8),
        TRY_SUNNY_DAY_START   = (1 << 9),
        // 10 - 28 are not used
        ROAMING               = (1 << 29),
        SAFARI                = (1 << 30),
        FIRST_BATTLE          = (1 << 31),  // Within the valid range of an unsigned 32-bit integer

        COUNT                 = 13 /// @todo - Update when new scripts are added
    };

    /// @brief Convenience function that converts the enum value to the assigned integer value.
    ///
    /// @param which - The value of the enum to convert
    /// @return The integer value of the converted enum
    ///
    /// @note Implementation is dependent on which version of C++ used.
    ///
    constexpr auto to_int = &_to_int<Effectiveness>;

    /// @brief Convenience function that converts the enum value to the assigned integer value.
    ///
    /// @param which - The value of the enum to convert
    /// @return The integer value of the converted enum
    ///
    /// @note Implementation is dependent on which version of C++ used.
    ///
    constexpr auto to_int = &_to_int<ScriptBits>;
};

#endif // GUARD_CONSTANTS_BATTLE_AI_H