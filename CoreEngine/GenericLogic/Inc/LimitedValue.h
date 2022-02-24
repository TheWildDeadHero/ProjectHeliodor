/**
 * @file LimitedValue.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-02-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdint.h>

template <typename NUMERIC_TYPE, NUMERIC_TYPE MIN_VALUE, NUMERIC_TYPE MAX_VALUE, bool RING_TYPE>
class LimitedValue
{
    public:
        LimitedValue();
        LimitedValue(NUMERIC_TYPE);

        ~LimitedValue();

    private:
        NUMERIC_TYPE value_;
};