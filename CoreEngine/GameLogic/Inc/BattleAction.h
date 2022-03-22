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

#include <stdint.h>

class c_BattleAction
{
    public:

        static c_BattleAction* get_first_action()
        {
            return p_first_action_;
        }

        static void add_action(c_BattleAction);

        static void clear_playlist();
       

    private:

        // Keep track of the first 
        static c_BattleAction    *p_first_action_;

        c_BattleAction           *next_ = nullptr;

        e_BattleActionID         which_action_;

        

};