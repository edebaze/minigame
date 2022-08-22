#ifndef UNTITLED_GAMEMASTER_H
#define UNTITLED_GAMEMASTER_H

#include "../../champions/Player.h"
#include <vector>

namespace objects::game::engine {
    class GameMaster
    {
    public:
        static const int MAX_ROUND_SECURITY     = 50;
        static const int MAX_CONTINUE_REPEAT    = 3;
        const int MAX_LEVEL                     = 5;
        int level;
        int round;
        int currentPlayerIndex = 0;

        std::vector<champions::Player> players = {};

        // =============================================================================================================
        // CONSTRUCTOR
        GameMaster(std::vector<champions::Player> players);

        // =============================================================================================================
        // MAIN FUNCTIONS
        void run();
        void end_game(bool victory) const;

        // =============================================================================================================
        // LEVEL MANAGING
        bool next_level();
        bool play_level();
        static bool end_level();

        // =============================================================================================================
        // ROUND MANAGING
        void next_round();
        void end_round();
        void switch_current_player();
        void display_round();
        bool is_round_over();

        // =============================================================================================================
        // PLAYER / TARGET SELECTION
        champions::Player& current_player();
        champions::Player& current_target();
    };
}


#endif //UNTITLED_GAMEMASTER_H
