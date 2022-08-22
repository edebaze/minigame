#ifndef UNTITLED_ITEM_H
#define UNTITLED_ITEM_H

#include "./enums/Emplacements.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>

namespace objects::champions::items {
    class Item {
    private:
        std::string _name;
        enums::Emplacements _emplacement = {};

        // STATS
        int _hp = 0;
        int _ad = 0;
        int _resistance = 0;
        int _shield = 0;

    public:
        Item(std::string name, enums::Emplacements emplacement);

        Item& operator+=(const Item &item);

        std::string getName();

        Item& setName(std::string name);

        enums::Emplacements getEmplacement() const;

        Item& setEmplacement(enums::Emplacements emplacement);

        int getHp() const;

        Item& setHp(int hp);

        int getAd() const;

        Item& setAd(int ad);

        int getResistance() const;

        Item& setResistance(int resistance);

        int getShield() const;

        Item& setShield(int shield);

    };
}


#endif //UNTITLED_ITEM_H
