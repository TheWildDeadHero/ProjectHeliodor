///
/// @file abilities.hpp
///
/// @brief This file contains an enum for all ability indices.
///
/// @addtogroup Abilities
/// @{

#ifndef GUARD_CONSTANTS_ABILITIES_H
#define GUARD_CONSTANTS_ABILITIES_H

// For non-GBA environments.
#include "port_types.hpp"
#include "to_int.hpp"

/// @brief Enum for ability ID numbers.
namespace Abilities
{
    enum class IDs : u16
    {
        // Gen III Abilities
        NONE,
        STENCH,
        DRIZZLE,
        SPEED_BOOST,
        BATTLE_ARMOR,
        STURDY,
        DAMP,
        LIMBER,
        SAND_VEIL,
        STATIC,
        VOLT_ABSORB,
        WATER_ABSORB,
        OBLIVIOUS,
        CLOUD_NINE,
        COMPOUND_EYES,
        INSOMNIA,
        COLOR_CHANGE,
        IMMUNITY,
        FLASH_FIRE,
        SHIELD_DUST,
        OWN_TEMPO,
        SUCTION_CUPS,
        INTIMIDATE,
        SHADOW_TAG,
        ROUGH_SKIN,
        WONDER_GUARD,
        LEVITATE,
        EFFECT_SPORE,
        SYNCHRONIZE,
        CLEAR_BODY,
        NATURAL_CURE,
        LIGHTNING_ROD,
        SERENE_GRACE,
        SWIFT_SWIM,
        CHLOROPHYLL,
        ILLUMINATE,
        TRACE,
        HUGE_POWER,
        POISON_POINT,
        INNER_FOCUS,
        MAGMA_ARMOR,
        WATER_VEIL,
        MAGNET_PULL,
        SOUNDPROOF,
        RAIN_DISH,
        SAND_STREAM,
        PRESSURE,
        THICK_FAT,
        EARLY_BIRD,
        FLAME_BODY,
        RUN_AWAY,
        KEEN_EYE,
        HYPER_CUTTER,
        PICKUP,
        TRUANT,
        HUSTLE,
        CUTE_CHARM,
        PLUS,
        MINUS,
        FORECAST,
        STICKY_HOLD,
        SHED_SKIN,
        GUTS,
        MARVEL_SCALE,
        LIQUID_OOZE,
        OVERGROW,
        BLAZE,
        TORRENT,
        SWARM,
        ROCK_HEAD,
        DROUGHT,
        ARENA_TRAP,
        VITAL_SPIRIT,
        WHITE_SMOKE,
        PURE_POWER,
        SHELL_ARMOR,
        CACOPHONY,
        AIR_LOCK,

        // Gen IV Abilities
        TANGLED_FEET,
        MOTOR_DRIVE,
        RIVALRY,
        STEADFAST,
        SNOW_CLOAK,
        GLUTTONY,
        ANGER_POINT,
        UNBURDEN,
        HEATPROOF,
        SIMPLE,
        DRY_SKIN,
        DOWNLOAD,
        IRON_FIST,
        POISON_HEAL,
        ADAPTABILITY,
        SKILL_LINK,
        HYDRATION,
        SOLAR_POWER,
        QUICK_FEET,
        NORMALIZE,
        SNIPER,
        MAGIC_GUARD,
        NO_GUARD,
        STALL,
        TECHNITIAN,
        LEAF_GUARD,
        KLUTZ,
        MOLD_BREAKER,
        SUPER_LUCK,
        AFTERMATH,
        ANTICIPATION,
        FOREWARN,
        UNAWARE,
        TINTED_LENS,
        FILTER,
        SLOW_START,
        SCRAPPY,
        STORM_DRAIN,
        ICE_BODY,
        SOLID_ROCK,
        SNOW_WARNING,
        HONEY_GATHER,
        FRISK,
        RECKLESS,
        MULTITYPE,
        FLOWER_GIFT,
        BAD_DREAMS,

        // Gen V Abilities
        PICKPOCKET,
        SHEER_FORCE,
        CONTRARY,
        UNNERVE,
        DEFIANT,
        DEFEATIST,
        CURSED_BODY,
        HEALER,
        FRIEND_GUARD,
        WEAK_ARMOR,
        HEAVY_ARMOR,
        LIGHT_METAL,
        MULTISCALE,
        TOXIC_BOOST,
        FLARE_BOOST,
        HARVEST,
        TELEPATHY,
        MOODY,
        OVERCOAT,
        POISON_TOUCH,
        REGENERATOR,
        BIG_PECKS,
        SAND_RUSH,
        WONDER_SKIN,
        ANALYTIC,
        ILLUSION,
        IMPOSTER,
        INFILTRATOR,
        MUMMY,
        MOXIE,
        JUSTIFIED,
        RATTLED,
        MAGIC_BOUNCE,
        SAP_SIPPER,
        PRANKSTER,
        SAND_FORCE,
        IRON_BARBS,
        ZEN_MODE,
        VICTORY_STAR,
        TURBOBLAZE,
        TERAVOLT,

        // Gen VI Abilities
        AROMA_VEIL,
        FLOWER_VEIL,
        CHEEK_POUCH,
        PROTEAN,
        FUR_COAT,
        MAGICIAN,
        BULLETPROOF,
        COMPETITIVE,
        STRONG_JAW,
        REFRIGERATE,
        SWEET_VEIL,
        STANCE_CHANGE,
        GALE_WINGS,
        MEGA_LAUNCHER,
        GRASS_PELT,
        SYMBIOSIS,


        // Gen VII Abilities

        // Gen VIII Abilities

        // Gen IX Abilities

        // Custom Abilities

        // Abilities counter member
        ABILITIES_COUNT,
    };

    /// @brief Convenience function to static convert an ability ID enum to an integer value
    ///
    /// @param[in] id - The Ability ID enum to convert
    /// @return A u16 ability ID integer
    ///
    /// @todo - Remove if unneeded
    ///
    constexpr auto to_int = &_to_int<IDs>;
};

#endif // GUARD_CONSTANTS_ABILITIES_H
/// @}