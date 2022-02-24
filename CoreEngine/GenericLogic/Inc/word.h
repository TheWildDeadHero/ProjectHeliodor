/**
 * @file Word.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-02-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdint.h>

template <typename TYPE>
class __WordABC
{
    public:

        virtual uint8_t* at_byte(uint32_t);
        
        virtual uint8_t byte(uint32_t);
        virtual uint8_t bit(uint32_t);

        virtual void insert_byte(uint32_t, uint8_t);
        virtual void insert_bit(uint32_t, uint8_t);

        virtual void clear_byte(uint32_t);

        virtual void flip_byte(uint32_t);
        virtual void flip_bit(uint32_t);
        virtual void flip_many_bits(uint32_t, uint32_t);

        virtual uint8_t operator () (uint32_t);
        virtual uint8_t operator () (uint32_t, uint32_t);

    protected:
        size_t num_bytes_ = sizeof(TYPE);
};

class word8_t : public __WordABC<uint8_t>
{
    public:

    private:

        // Anonymous data definition
        union
        {
            uint8_t data_;

            struct
            {
                uint8_t bit_7  : 1;
                uint8_t bit_6  : 1;
                uint8_t bit_5  : 1;
                uint8_t bit_4  : 1;
                uint8_t bit_3  : 1;
                uint8_t bit_2  : 1;
                uint8_t bit_1  : 1;
                uint8_t bit_0  : 1;
            };
        };
        
};

class word16_t : public __WordABC
{
    public:

    private:

        // Anonymous data definition
        union
        {
            uint16_t data_;

            struct
            {
                uint8_t bytes[sizeof(uint16_t)];
            };

            struct
            {
                uint8_t byte_1;
                uint8_t byte_0;
            };

            struct
            {
                uint8_t bit_15 : 1;
                uint8_t bit_14 : 1;
                uint8_t bit_13 : 1;
                uint8_t bit_12 : 1;
                uint8_t bit_11 : 1;
                uint8_t bit_10 : 1;
                uint8_t bit_9  : 1;
                uint8_t bit_8  : 1;
                uint8_t bit_7  : 1;
                uint8_t bit_6  : 1;
                uint8_t bit_5  : 1;
                uint8_t bit_4  : 1;
                uint8_t bit_3  : 1;
                uint8_t bit_2  : 1;
                uint8_t bit_1  : 1;
                uint8_t bit_0  : 1;
            };
        };
        
};

class word32_t : public __WordABC
{
    public:

    private:

        // Anonymous data definition
        union
        {
            uint32_t data_;

            struct
            {
                uint8_t byte_3;
                uint8_t byte_2;
                uint8_t byte_1;
                uint8_t byte_0;
            };

            struct
            {
                uint8_t bit_15 : 1;
                uint8_t bit_14 : 1;
                uint8_t bit_13 : 1;
                uint8_t bit_12 : 1;
                uint8_t bit_11 : 1;
                uint8_t bit_10 : 1;
                uint8_t bit_9  : 1;
                uint8_t bit_8  : 1;
                uint8_t bit_7  : 1;
                uint8_t bit_6  : 1;
                uint8_t bit_5  : 1;
                uint8_t bit_4  : 1;
                uint8_t bit_3  : 1;
                uint8_t bit_2  : 1;
                uint8_t bit_1  : 1;
                uint8_t bit_0  : 1;
            };
        };
        
};