#include "Player.h"

#include <utility>


namespace objects::champions {
    // =================================================================================================================
    // CONSTRUCTOR & GETTERS / SETTERS
    Player::Player(
            std::string playerName,
            classes::enums::ClassType classType,
            int baseHp,
            int baseAd,
            int baseResistance,
            int baseShield,
            spells::Spell spell,
            std::vector<items::enums::ItemList> items,
            bool isAuto
    ) : _playerName(std::move(playerName)), _classType(classType), _baseHp(baseHp), _baseAd(baseAd),
        _baseResistance(baseResistance), _baseShield(baseShield), spell(std::move(spell)), _isAuto(isAuto)
    {
        this->reset();
        this->equip(items);
    };

    // =================================================================================================================
    // RESET & LEVELS
    void Player::reset()
    {
        // RESET STATS
        this->_hp           = this->_baseHp;
        this->_ad           = this->_baseAd;
        this->_resistance   = this->_baseResistance;
        this->_shield       = this->_baseShield;

        // RESET COOLDOWNS
        this->boostStack = {};
        this->spell.cooldownCtr = 0;
        this->stunCooldown = 0;
    }

    void Player::level_up()
    {
        // AUTO LEVEL UP (for bot)
        if (this->getIsAuto()) {
            this->_baseHp += 15;
            this->_baseAd += 3;
            return;
        }

        champions::upgrades::Upgrade upgrade = game::rendering::Renderer::choose_upgrade();
        this->apply_upgrade(upgrade);
    }

    // =================================================================================================================
    // [GETTERS & SETTERS]
    std::string Player::getPlayerName() const { return this->_playerName; }
    Player& Player::setPlayerName(std::string playerName) {
        this->_playerName = std::move(playerName);
    }
    bool Player::getIsAuto() const { return this->_isAuto; }
    Player& Player::setIsAuto(bool isAuto) {
        this->_isAuto = isAuto;
        return *this;
    }
    spells::Spell& Player::getSpell() { return this->spell; }

    // =================================================================================================================
    // [SPELLS & EFFECTS]
    /**
     * Cast this spell on a target player
     *      - check if spell is on cooldown (true -> exit)
     *      - try success (cf: this->percSuccess)
     *      - apply spell effects
     *      - TODO : apply damages (if this feature is implemented)
     *      - set spell on cooldown (cf: this->cooldownCtr)
     * @param target
     */
    void Player::cast(spells::Spell &spell, Player &target)
    {
        // do not cast if cooldown is not over
        if (spell.cooldownCtr > 0) {
            std::cout << "unable to use spell " << spell.name << " : cooldown  " << spell.cooldownCtr << std::endl;
            return;
        }

        // set cooldown counter to base spell cooldown
        spell.cooldownCtr = spell.cooldown;

        std::cout << "casting " << spell.name << " on " << target.getPlayerName() << " : ... ";

        // check if spell is a success
        float spellProb = (float) rand() / RAND_MAX;
        printf ("(%f)", spellProb);

        if (spellProb > spell.percSuccess) {
            std::cout << " MISSED"  << std::endl;
            return;
        }

        // cast spell on target
        std::cout << " SUCCESS !"  << std::endl;

        // add spell boosts to player's boost stack
        this->boostStack.insert(this->boostStack.end(), spell.boosts.begin(), spell.boosts.end());

        // apply stun
        this->stunCooldown = std::max(this->stunCooldown, spell.stunDuration);
    }

    /** subtract 1 turn to each cooldowns (stun, boosts, spells...) */
    void Player::sub_cooldown()
    {
        // subtract one turn cooldown to the spell
        this->spell.sub_cooldown();
        // subtract one turn cooldown to all boosts in the boost stack
        this->sub_cooldown_boosts();
        // subtract cooldown to the stun effect
        this->stunCooldown = std::max(this->stunCooldown - 1, 0);
    }

    /** remove 1 turn cooldown to each boosts in the boostStack. Remove boosts with cooldownCtr at 0 */
    void Player::sub_cooldown_boosts()
    {
        // init new boost stack
        std::vector<Boost> myBoostStack = {};
        for (Boost boost : this->boostStack) {
            boost.cooldownCtr -= 1;
            // keep boost in boostStack if cooldown > 0
            if (boost.cooldownCtr > 0) {
                myBoostStack.push_back(boost);
            }
        }

        // set new boost stack
        this->boostStack = myBoostStack;
    }

    // =================================================================================================================
    // [ATTACK FUNCTIONS]
    void Player::attack(Player& target) {
        Player::hit(target, this->get_final_ad());
    }

    void Player::hit(Player& target, int damages)
    {
        target.get_hit(damages);
    }

    void Player::get_hit(int damages)
    {
        // subtract _resistance from damages (set min to 0 to avoid unwanted healing)
        int finalDamages = std::max(0, damages - this->_resistance);

        std::cout << this->_playerName << " was hit for " << finalDamages << " damages";

        if (this->get_final_shield() > 0) {
            this->_shield -= finalDamages;

            // if damages goes over _shield value
            if (this->get_final_shield() < 0) {
                // set finalDamages to over damages
                finalDamages = std::abs(this->get_final_shield());
                // add difference to the _shield value (-> final_shield = 0)
                this->_shield += finalDamages;
            } else {
                // no over damages -> finalDamages is 0
                finalDamages = 0;
            }
        }

        // hp can go down below 0 since boosts and items can give bonus hp. But if Boosts / Items are removed, the player will die
        this->_hp = this->_hp - finalDamages;

        // quick display of action
        std::cout << " - remaining health (shield) : " << this->get_final_hp() << " (+" << this->get_final_shield() << ")" << std::endl;

        if (this->is_dead())
        {
            std::cout << this->_playerName + " is dead" << std::endl;
        }
    }

    // =================================================================================================================
    // [ITEMS]
    void Player::equip(items::Item item)
    {
        this->stuff.find(item.getEmplacement())->second = item;
    }

    void Player::equip(const std::vector<items::Item>& items)
    {
        for ( const auto& item : items ) {
            this->equip(item);
        }
    }

    void Player::equip(items::enums::ItemList item)
    {
        this->equip(items::enums::ItemListUtils::get(item));
    }

    void Player::equip(const std::vector<items::enums::ItemList>& items)
    {
        for ( auto item : items ) {
            this->equip(item);
        }
    }

    // =================================================================================================================
    // FINAL STATS GETTER
    /** get final hp which is current_hp (this->_hp) + hp boost */
    int Player::get_final_hp()
    {
        auto hp = this->_hp;
        for (Boost boost : this->boostStack) {
            hp += boost.getHp();
        }
        return hp;
    }

    /** get final AD (Attack Damages) which is (current_ad (this->_ad) + ad boost) * ad percentage boost */
    int Player::get_final_ad()
    {
        // CURRENT STATS of the Player's items combined
        items::Item allItemsStats = this->get_all_items_stats();

        // CURRENT STATS of the Player's boosts combined
        Boost allBoostsStats = this->get_all_boosts_stats();

        return (int) std::rint( (float)(this->_ad + allItemsStats.getAd() + allBoostsStats.getAd()) * allBoostsStats.getPercDamages());
    }

    /** get final shield of the player (current shield + items + boosts) */
    int Player::get_final_shield()
    {
        // CURRENT STATS of the Player's items combined
        items::Item allItemsStats = this->get_all_items_stats();

        // CURRENT STATS of the Player's boosts combined
        Boost allBoostsStats = this->get_all_boosts_stats();

        return this->_shield + allItemsStats.getShield() + allBoostsStats.getShield();
    }

    /**
     * return an Item that contains combined stats of every Items in the stuff
     * @return Item
     */
    items::Item Player::get_all_items_stats()
    {
        // create empty item that will contain combined stats
        items::Item allStatsItem("", items::enums::Emplacements::ANY);

        // go through each emplacement of the stuff to get the item
        for (auto const& [emplacement, item] : this->stuff) {
            allStatsItem += item;
        }

        return allStatsItem;
    }

    /**
     * return a Boost that contains combined stats of each Player's Boosts
     * @return
     */
    Boost Player::get_all_boosts_stats()
    {
        // create empty item that will contain combined stats
        Boost allStatsBoost;

        // go through each emplacement of the stuff to get the item
        for (Boost boost : this->boostStack) {
            allStatsBoost += boost;
        }

        return allStatsBoost;
    }

    // =================================================================================================================
    // UPGRADES
    void Player::apply_upgrade(upgrades::Upgrade upgrade) {
        if (upgrade.getBoost().has_value()) {
            Boost boost = upgrade.getBoost().value();
            this->_baseHp += boost.getHp();
            this->_baseAd += boost.getAd();
            this->_baseResistance += boost.getResistance();
            this->_baseShield += boost.getShield();
        }

        if (upgrade.getItem().has_value()) {
            this->equip(std::move(upgrade.getItem().value()));
        }
    }

    // =================================================================================================================
    // STATE
    bool Player::is_dead()
    {
        return this->get_final_hp() <= 0;
    }

    bool Player::is_stun() const
    {
        return this->stunCooldown > 0;
    }

}

