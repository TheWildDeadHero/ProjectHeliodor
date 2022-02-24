/**
 * @file LimString.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-02-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <string>

template <size_t LENGTH_LIMIT>
class LimitedString : public std::string
{
    public:
        uint32_t max_length();

        void fill(char);

        

    private:
        size_t max_length_ = LENGTH_LIMIT;
}