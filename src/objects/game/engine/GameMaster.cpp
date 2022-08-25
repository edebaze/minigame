#include "GameMaster.h"
#include "../rendering/Renderer.h"

#include <utility>
#include <boost/algorithm/string.hpp>

namespace objects::game::engine {
    // ================================================================================
    // CONSTRUCTOR
    GameMaster::GameMaster(std::vector<champions::Player> players)
    {
        GameMaster::round = 0;
        this->level = 1;
        this->players = std::move(players);
        this->currentPlayerIndex = -1;
    }

    // ================================================================================
    // GAME MANAGING
    void GameMaster::run()
    {
        bool isContinue = true;
        bool isVictory;

        while(isContinue) {
            // display level
            this->start_level();

            // play the level
            isVictory = this->play_level();

            // check if the player has failed or if this level was last level
            if (! isVictory || this->level == GameMaster::MAX_LEVEL) {
                break;
            }

            // handle end of a level (ask player if he wants to continue, level_up...)
            isContinue = this->next_level();
        }

        this->end_game(isVictory);
    }

    void GameMaster::end_game(bool victory) const
    {
        rendering::Renderer::separator();

        if (victory) {
            // Player was victorious on previous level which was the highest level : VICTORY MESSAGE
            if (this->level == GameMaster::MAX_LEVEL) {
                rendering::Renderer::victory_message();
                return;
            }

            // Player was victorious on previous level but decided to stop
            return rendering::Renderer::good_bye_message();
        }

        // Player wasn't victorious on previous level : GAME OVER MESSAGE
        rendering::Renderer::game_over_message();
    }

    // =================================================================================================================
    // LEVEL MANAGEMENT
    /** contains all actions that happens at the very start of the level (just before level loop) */
    void GameMaster::start_level()
    {
        // reset GameMaster rounds and Players (hp, buffs... etc)
        this->round = 0;
        for (champions::Player &player : this->players) {
            player.reset();
        }

        // DISPLAY : new level
        game::rendering::Renderer::jump_line();
        game::rendering::Renderer::separator("*");
        game::rendering::Renderer::print("Level " + std::to_string(this->level));
    }

    /** contains all actions that happens while the level is not finished */
    bool GameMaster::play_level()
    {
        while (this->round < GameMaster::MAX_ROUND_SECURITY) {
            this->next_round();

            // skip player's turn if stunned
            if (this->current_player().is_stun()) {
                std::cout << this->current_player().getPlayerName()  << " is stunned : skip turn"  << std::endl;
                continue;
            }

            // cast spell on target
            this->current_player().cast(this->current_player().getSpell(), this->current_target());
            // attack target
            this->current_player().attack(this->current_target());

            // GAME OVER
            if (this->is_round_over()) {
                return ! this->players.at(0).is_dead();
            }

            this->end_round();
        }

        rendering::Renderer::print("WARNING : infinite loop !");   // TODO : error message
        throw std::exception();
    }

    /** Contains all actions that occurred at the end of a level :
     *      - ask Player if he wants to continue
     *      - increase level
     *      - level_up Player (make him choose an Upgrade)
     * */
    bool GameMaster::next_level()
    {
        // ask player if he wants to continue
        if (! rendering::Renderer::continue_message()) {
            return false;
        }

        // increase game level
        this->level++;

        // make Players level up (prompt choice for an Upgrade)
        for (champions::Player &player : this->players) {
            player.level_up();
        }

        return true;
    }

    // =================================================================================================================
    // ROUND MANAGEMENT
    /** NEW ROUND STARTS */
    void GameMaster::next_round()
    {
        // new round
        GameMaster::round++;

        // switch current player and current target
        this->switch_current_player();

        // display new round to the prompt
        this->display_round();
    }

    /** ROUND ENDS */
    void GameMaster::end_round()
    {
        // apply one turn cooldown reduction on the current player (spells, effects...)
        this->current_player().sub_cooldown();
    }

    /** switch current player and current target */
    void GameMaster::switch_current_player()
    {
        this->currentPlayerIndex++;							// increment index of the current player
        this->currentPlayerIndex %= this->players.size();	// reset to 0 if >= max number of players
    }

    void GameMaster::display_round()
    {
        std::cout << std::endl << "Round " << this->round << " : " << this->current_player().getPlayerName() << std::endl;
    }

    champions::Player& GameMaster::current_player()
    {
        return this->players[this->currentPlayerIndex];
    }

    champions::Player& GameMaster::current_target()
    {
        int targetIndex;
        targetIndex = (this->currentPlayerIndex + 1) % this->players.size();
        return this->players.at(targetIndex);
    }

    bool GameMaster::is_round_over()
    {
        for (champions::Player& player : this->players)
        {
            // game stops if a player is dead
            if (player.is_dead()) {
                return true;
            }
        }
        return false;
    }
}