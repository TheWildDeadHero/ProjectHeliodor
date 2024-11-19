///
/// @file apprentice.hpp
///
/// @brief This file contains enums for all Battle Frontier apprentice
/// options.
///
/// @addtogroup BattleFrontier
/// @{

#ifndef GUARD_CONSTANTS_APPRENTICE_H
#define GUARD_CONSTANTS_APPRENTICE_H

// For non-GBA environments.
#include "port_types.hpp"
#include "to_int.hpp"

namespace Apprentice
{
    /// @todo - Placeholders while I find the values of these defines
    #define MULTI_PARTY_SIZE    (0U)
    #define FRONTIER_LVL_50     (0U)
    #define FRONTIER_LVL_OPEN   (0U)

    constexpr u8 NUM_APPRENTICES            = 16U;
    constexpr u8 SPECIES_COUNT              = 10U;

    constexpr u8 NUM_WHICH_MON_QUESTIONS    = MULTI_PARTY_SIZE;
    constexpr u8 NUM_WHICH_MOVE_QUESTIONS   = 5U;
    constexpr u8 MAX_QUESTIONS              = NUM_WHICH_MON_QUESTIONS + NUM_WHICH_MOVE_QUESTIONS + 2U;

    constexpr u8 LVL_MODE_50                = FRONTIER_LVL_50 + 1U;
    constexpr u8 LVL_MODE_OPEN              = FRONTIER_LVL_OPEN + 1U;

    enum class Function : u8
    {
        GAVE_LVL_MODE,
        SET_LVL_MODE,
        SET_ID,
        SHUFFLE_SPECIES,
        RANDOMIZE_QUESTIONS,
        ANSWERED_QUESTION,
        IS_FINAL_QUESTION,
        MENU,
        PRINT_MSG,
        RESET,
        CHECK_GONE,
        GET_QUESTION,
        GET_NUM_PARTY_MONS,
        SET_PARTY_MON,
        INIT_QUESTION_DATA,
        FREE_QUESTION_DATA,
        BUFFER_STRING,
        SET_MOVE,
        SET_LEAD_MON,
        OPEN_BAG,
        TRY_SET_HELD_ITEM,
        SAVE,
        SET_GFX_SAVED,
        SET_GFX,
        SHOULD_LEAVE,
        SHIFT_SAVED
    };

    enum class Message : u8
    {
        PLEASE_TEACH,
        REJECT,
        WHICH_LVL_MODE,
        THANKS_LVL_MODE,
        WHICH_MON_FIRST,
        THANKS_MON_FIRST,
        WHICH_MON,
        THANKS_MON,
        WHICH_MOVE,
        THANKS_MOVE,
        WHAT_HELD_ITEM,
        PICK_WIN_SPEECH,
        THANKS_HELD_ITEM,
        HOLD_NOTHING,
        THANKS_NO_HELD_ITEM,
        THANKS_WIN_SPEECH,
        ITEM_ALREADY_SUGGESTED
    };

    enum class Question : u8
    {
        WHICH_FIRST,
        WHICH_MON,
        WHICH_MOVE,
        WHAT_ITEM,
        WIN_SPEECH
    };
    /// @todo - Make 2nd set of Question ID consts redundant - See apprentice.h

    enum class Ask : u8
    {
        WHICH_LEVEL,
        THREE_SPECIES,
        TWO_SPECIES,
        MOVES,
        GIVE,
        YES_NO
    };

    enum class Buff : u8
    {
        SPECIES_1,
        SPECIES_2,
        SPECIES_3,
        MOVE_1,
        MOVE_2,
        ITEM,
        NAME,
        WIN_SPEECH,
        LEVEL,
        LEAD_MON_SPECIES
    };

    /// @brief Convenience functions to static convert the various appprentice enums to integer values
    ///
    /// @param[in] id - The Ability ID enum to convert
    /// @return A u16 ability ID integer
    ///
    /// @todo - Remove if unneeded
    ///
    constexpr auto to_int = &_to_int<Function>;
    constexpr auto to_int = &_to_int<Message>;
    constexpr auto to_int = &_to_int<Question>;
    constexpr auto to_int = &_to_int<Ask>;
    constexpr auto to_int = &_to_int<Buff>;
};

#endif // GUARD_CONSTANTS_APPRENTICE_H