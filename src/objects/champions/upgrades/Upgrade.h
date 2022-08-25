//
// Created by edebazelaire on 25/08/22.
//

#ifndef UNTITLED_UPGRADE_H
#define UNTITLED_UPGRADE_H

#include <optional>
#include "../spells/Boost.h"
#include "../items/enums/ItemList.h"

namespace objects::champions::upgrades {
    class Upgrade {
        std::optional<Boost> _boost;
        std::optional<items::Item> _item;

    public:
        explicit Upgrade(Boost);
        explicit Upgrade(items::Item);
        explicit Upgrade(items::enums::ItemList);

        Upgrade& setBoost(Boost boost);
        Upgrade& setItem(const items::Item& item);
        Upgrade& setItem(items::enums::ItemList item);

        std::optional<Boost> getBoost();
        std::optional<items::Item> getItem();
    };

    std::vector<Upgrade> get_upgrades();
}



#endif //UNTITLED_UPGRADE_H
