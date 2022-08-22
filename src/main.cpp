#include <iostream>
#include <vector>
#include "objects/champions/classes/enums/ClassTypeUtils.h"
#include "objects/champions/classes/enums/ClassType.h"
#include "objects/game/engine/GameMaster.h"

using namespace objects::champions;
using namespace objects::champions::classes::enums;
using namespace objects::game::engine;

int main()
{
    // ============================================================================
    // INSTANTIATION
    // ---------------------------------------
    // PLAYERS
    std::vector<Player> players = {
        ClassTypeUtils::get(ClassType::KNIGHT),
        ClassTypeUtils::get(ClassType::ORC)
    };

    // ---------------------------------------
    // GAME MASTERING
    GameMaster GM(players);
    GM.run();
}



