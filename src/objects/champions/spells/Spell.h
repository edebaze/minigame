#ifndef UNTITLED_SPELL_H
#define UNTITLED_SPELL_H

#include <string>
#include <vector>
#include "Boost.h"

namespace objects::champions::spells {
    class Spell {
    public:
        const std::string name;         // name of the spell
        const int cooldown;             // spell cool down (> 0)
        float percSuccess;              // Spell's percentage of success (between 0 and 1)
        int stunDuration = 0;           // number of rounds the target will be stun
        std::vector<Boost> boosts = {}; // vector of stat Boosts

        int cooldownCtr = 0;            // counter of the spells current cooldown (remaining rounds before using it again)

        Spell(std::string name, int cooldown, float percSuccess, std::vector<Boost> boosts, int stunDuration);

        /**
         * remove n turns from this spell cooldown counter
         * @param n : number of turn to remove from counter
         */
        void sub_cooldown(int n=1);
    };

}

#endif //UNTITLED_SPELL_H
