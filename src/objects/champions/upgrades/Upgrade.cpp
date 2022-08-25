#include "Upgrade.h"

namespace objects::champions::upgrades {
    Upgrade::Upgrade(Boost boost): _boost(boost), _item(std::nullopt) {}
    Upgrade::Upgrade(items::Item item): _boost(std::nullopt), _item(item) {}
    Upgrade::Upgrade(items::enums::ItemList item): _boost(std::nullopt) {
        this->setItem(item);
    }

    Upgrade& Upgrade::setBoost(Boost boost) {
        this->_boost = boost;
        this->_item = std::nullopt;
        return *this;
    }

    Upgrade& Upgrade::setItem(const items::Item& item) {
        this->_item = item;
        this->_boost = std::nullopt;
        return *this;
    }

    Upgrade& Upgrade::setItem(items::enums::ItemList item) {
        this->_item = items::enums::ItemListUtils::get(item);
        this->_boost = std::nullopt;
        return *this;
    }

    std::optional<items::Item> Upgrade::getItem() {
        return this->_item;
    }

    std::optional<Boost> Upgrade::getBoost() {
        return this->_boost;
    }

    std::vector<Upgrade> get_upgrades()
    {
        return {
                Upgrade(Boost().setHp(25)),
                Upgrade(Boost().setHp(15).setAd(5)),
                Upgrade(Boost().setAd(10)),
                Upgrade(Boost().setResistance(5)),
                Upgrade(items::enums::ItemList::PLATED_ARMOR),
                Upgrade(items::enums::ItemList::SHADOW_AXE),
                Upgrade(items::enums::ItemList::SHIELD_OF_THE_HEROES),
        };
    }
}



