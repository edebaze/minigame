#include "../Spell.h"

#ifndef UNTITLED_SPELLSLIST_H
#define UNTITLED_SPELLSLIST_H

namespace objects::champions::spells::enums {
    enum class SpellsList
    {
        CHARGE,
        STUN,
    };

    class SpellsListUtils {
    public:
        static Spell get(SpellsList spellsList) {
            switch(spellsList) {
                case SpellsList::CHARGE:
                    return Spell("charge", 3, 0.6, {Boost().setPercDamages(2).setCooldownCtr(1)}, 0);
                case SpellsList::STUN:
                    return Spell("stun", 5, 0.2, {}, 1);
                default:
                    throw std::exception();
            }
        };
    };
}

#endif //UNTITLED_SPELLSLIST_H
