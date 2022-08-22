#include "Item.h"

#include <utility>

namespace objects::champions::items {
    Item::Item(std::string name, enums::Emplacements emplacement)
        : _name(std::move(name)), _emplacement(emplacement) {}


    std::string Item::getName()  {
        return _name;
    }

    Item& Item::setName(std::string name) {
        _name = std::move(name);
        return *this;
    }

    enums::Emplacements Item::getEmplacement() const {
        return _emplacement;
    }

    Item& Item::setEmplacement(enums::Emplacements emplacement) {
        _emplacement = emplacement;
        return *this;
    }

    int Item::getHp() const {
        return _hp;
    }

    Item& Item::setHp(int hp) {
        _hp = hp;
        return *this;
    }

    int Item::getAd() const {
        return _ad;
    }

    Item& Item::setAd(int ad) {
        _ad = ad;
        return *this;
    }

    int Item::getResistance() const {
        return _resistance;
    }

    Item& Item::setResistance(int resistance) {
        _resistance = resistance;
        return *this;
    }

    int Item::getShield() const {
        return _shield;
    }

    Item& Item::setShield(int shield) {
        _shield = shield;
        return *this;
    }

    // OPERATORS
    Item& Item::operator+=(const Item &item) {
        this->_hp += item.getHp();
        this->_ad += item.getAd();
        this->_resistance += item.getResistance();
        this->_shield += item.getShield();
    }
}