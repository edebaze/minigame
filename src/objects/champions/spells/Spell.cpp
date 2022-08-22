#include "Spell.h"
#include <utility>

namespace objects::champions::spells {
    Spell::Spell(std::string name, int cooldown, float percSuccess, std::vector<Boost> boosts, int stunDuration)
        : name(std::move(name)), cooldown(cooldown), percSuccess(percSuccess), boosts(std::move(boosts)), stunDuration(stunDuration)
        {}

    /**
     * remove n turns from this spell cooldown counter
     * @param n : number of turn to remove from counter
     */
    void Spell::sub_cooldown(int n)
    {
        this->cooldownCtr = std::max(this->cooldownCtr - n, 0);
    }
}