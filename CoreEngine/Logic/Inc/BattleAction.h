/**
 * @file BattleAction.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

class c_BattleAction
{
    public:

        static c_BattleAction* get_first_action()
        {
            return p_first_action_;
        }
       

    private:

        // Keep track of the first 
        static c_BattleAction    *p_first_action_;

        c_BattleAction           *next_ = nullptr;

};