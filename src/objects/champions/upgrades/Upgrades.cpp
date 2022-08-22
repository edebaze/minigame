#include "Upgrades.h"

namespace objects::champions::upgrades {
    static std::vector<items::enums::ItemList> items = {
            items::enums::ItemList::PLATED_ARMOR,
            items::enums::ItemList::SHADOW_AXE,
            items::enums::ItemList::SHIELD_OF_THE_HEROES,
    };

    static std::vector<Boost> boosts = {
            Boost().setHp(25),
            Boost().setHp(15).setAd(5),
            Boost().setAd(10),
            Boost().setResistance(5),
    };
}