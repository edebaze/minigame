#include "Boost.h"

Boost::Boost() = default;

int Boost::getHp() const {
    return hp;
}

Boost& Boost::setHp(int hp) {
    this->hp = hp;
    return *this;
}

int Boost::getAd() const {
    return ad;
}

Boost& Boost::setAd(int ad) {
    this->ad = ad; 
    return *this;
}

int Boost::getResistance() const {
    return resistance;
}

Boost& Boost::setResistance(int resistance) {
    this->resistance = resistance; 
    return *this;
}

int Boost::getShield() const {
    return shield;
}

Boost& Boost::setShield(int shield) {
    this->shield = shield; 
    return *this;
}

float Boost::getPercDamages() const {
    return percDamages;
}

Boost& Boost::setPercDamages(float percDamages) {
    this->percDamages = percDamages; 
    return *this;
}

float Boost::getPercResistance() const {
    return percResistance;
}

Boost& Boost::setPercResistance(float percResistance) {
    this->percResistance = percResistance; 
    return *this;
}

int Boost::getCooldownCtr() const {
    return cooldownCtr;
}

Boost& Boost::setCooldownCtr(int cooldownCtr) {
    this->cooldownCtr = cooldownCtr; 
    return *this;
}

// OPERATORS
Boost& Boost::operator+=(const Boost &boost) {
    this->hp += boost.getHp();
    this->ad += boost.getAd();
    this->resistance += boost.getResistance();
    this->shield += boost.getShield();

    // during Boosts addition, "perc[...]" values are multiplied
    this->percDamages *= boost.getPercDamages();
    this->percResistance *= boost.getPercResistance();

    return *this;
}


