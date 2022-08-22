#ifndef UNTITLED_UPGRADES_H
#define UNTITLED_UPGRADES_H

#include <iostream>
#include <vector>
#include "../items/enums/ItemList.h"
#include "../spells/Boost.h"

namespace objects::champions::upgrades {
    class Upgrades {
    public:
        static std::vector<items::enums::ItemList> items;
        static std::vector<Boost> boosts;
    };
}

#endif //UNTITLED_UPGRADES_H
