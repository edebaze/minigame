#ifndef UNTITLED_CLASSTYPEUTILS_H
#define UNTITLED_CLASSTYPEUTILS_H

#pragma once

#include "../../Player.h"
#include "../../spells/enums/SpellsList.h"
#include "../../items/enums/ItemList.h"
#include "../../items/Item.h"

namespace objects::champions::classes::enums {
    class ClassTypeUtils
    {
    public:
        /**
         * get Champion with requested class (and according statistics)
         * @param classType
         * @return
         */
        Player static get(ClassType classType)
        {
            switch (classType)
            {
                case ClassType::KNIGHT:
                    return Player(
                        "KNIGHT", classType, 50, 0, 0, 0,
                        spells::enums::SpellsListUtils::get(spells::enums::SpellsList::CHARGE),
                        {
                            items::enums::ItemList::DEFAULT_SHIELD,
                            items::enums::ItemList::DEFAULT_SWORD
                        }
                    );

                case ClassType::ORC:
                    return Player(
                        "ORC", classType, 60, 0, 0, 0,
                        spells::enums::SpellsListUtils::get(spells::enums::SpellsList::STUN),
                        {
                            items::enums::ItemList::DEFAULT_AXE
                        }
                    );

                default:
                    throw std::exception();
            }
        }
    };
}

#endif //UNTITLED_CLASSTYPEUTILS_H
