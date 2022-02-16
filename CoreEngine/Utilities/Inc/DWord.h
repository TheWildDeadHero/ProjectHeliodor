/**
 * @file DWord.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-02-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef GUARD_DWORD_H

// System Includes
#include <stdint.h>

/**
 * @brief 
 * 
 */
class c_DWord
{
    public:
        c_DWord();
        c_DWord(uint64_t);
        c_DWord(uint32_t, uint32_t);
        c_DWord(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);

        ~c_DWord();

        c_DWord& operator = (const c_DWord &other);
        c_DWord& operator = (const uint64_t &other);

        c_DWord& operator ++ ();

        c_DWord& operator << (const uint32_t shift_val);
        c_DWord& operator >> (const uint32_t shift_val);

    private:
        union
        {
            uint64_t value_;

            struct
            {
                uint32_t upper_word_;
                uint32_t lower_word_;
            };
    
            struct
            {
                uint8_t byte_7_;
                uint8_t byte_6_;
                uint8_t byte_5_;
                uint8_t byte_4_;
                uint8_t byte_3_;
                uint8_t byte_2_;
                uint8_t byte_1_;
                uint8_t byte_0_;
            };
        };
};

#endif // GUARD_DWORD_H