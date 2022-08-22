#ifndef UNTITLED_BOOST_H
#define UNTITLED_BOOST_H


class Boost {
private:
    int hp                  = 0;
    int ad                  = 0;
    int resistance          = 0;
    int shield              = 0;

    float percDamages       = 1;
    float percResistance    = 1;

public:
    Boost& operator+=(const Boost &item);

    int getHp() const;

    Boost& setHp(int hp);

    int getAd() const;

    Boost& setAd(int ad);

    int getResistance() const;

    Boost& setResistance(int resistance);

    int getShield() const;

    Boost& setShield(int shield);

    float getPercDamages() const;

    Boost& setPercDamages(float percDamages);

    float getPercResistance() const;

    Boost& setPercResistance(float percResistance);

    int getCooldownCtr() const;

    Boost& setCooldownCtr(int cooldownCtr);

public:
    int cooldownCtr         = 0;

    // CONSTRUCTOR
    Boost();

};


#endif //UNTITLED_BOOST_H
