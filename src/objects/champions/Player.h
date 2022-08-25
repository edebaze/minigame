#pragma once
#include <string>
#include <utility>
#include <iostream>
#include <map>
#include <cmath>

#include "classes/enums/ClassType.h"
#include "items/enums/Emplacements.h"
#include "items/enums/ItemList.h"
#include "items/Item.h"
#include "spells/Spell.h"
#include "spells/Boost.h"
#include "../game/rendering/Renderer.h"

namespace objects::champions {

    class Player
    {
    private:
        std::string _playerName;                // name of the player
        classes::enums::ClassType _classType;   // class of the Player (Knight, Orc...)
        bool _isAuto;                           // is the player automated ? (allow Player to make decision)

        // BASE COMBAT ATTRIBUTES
        int _baseHp;                            // base hit points of the player
        int _baseAd;                            // base fix attack damages of the player
        int _baseResistance;                    // base fix resistance that reduces damages taken
        int _baseShield;                        // base shield value of the player (which act as hp)

        // ITEMS
        std::map<items::enums::Emplacements, items::Item> stuff = items::enums::ItemListUtils::getDefaultItems();

    public:
        int _hp = 0;                            // current hp of the Player
        int _ad = 0;                            // current ad of the Player
        int _resistance = 0;                    // current resistance of the Player
        int _shield = 0;                        // current shield of the Player

        // BOOST & EFFECTS
        std::vector<Boost> boostStack = {};
        int stunCooldown = 0;                   // count down of Player's remaining stunned turns

        // LEVEL & POWERS
        int powerPoints = 0;                    // at the end of a fight, the Player gains powerPoints that can be used for upgrades

        // SPELLS
        spells::Spell spell;                    // special ability of the Champion (dependent of the class)

        // =============================================================================================================
        // [CONSTRUCTOR]
        explicit Player(
                std::string playerName,
                classes::enums::ClassType classType,
                int baseHp,
                int baseAd,
                int baseResistance,
                int baseShield,
                spells::Spell spell,
                std::vector<items::enums::ItemList> items = {},
                bool isAuto = true
        );

        // =============================================================================================================
        // [RESET & LEVELS]
        /** reset Player's stats (set to base stats) */
        void reset();
        /** level the Player up. Add generic stats if Player is automated (cf: isAuto) otherwise enhance prompt choice */
        void level_up();

        // =============================================================================================================
        // [FINAL STATS] : current value of each stats with Boosts & Items
        /** get final hp which is current_hp (this->_hp) + hp boost */
        int get_final_hp();
        /** get final AD (Attack Damages) which is (current_ad (this->_ad) + ad boost) * ad percentage boost */
        int get_final_ad();
        /** get final shield of the player (current shield + items + boosts) */
        int get_final_shield();
        /** return an Item that contains combined stats of every Items in the stuff */
        items::Item get_all_items_stats();
        /** return a Boost that contains combined stats of each Player's Boosts */
        Boost get_all_boosts_stats();

        // =============================================================================================================
        // [SPELLS & EFFECTS]
        /** cast a spell on a target player */
        void cast(spells::Spell &spell, Player &target);
        /** subtract 1 turn cooldown for spells and boosts */
        void sub_cooldown();
        /** subtract 1 turn cooldown for boosts */
        void sub_cooldown_boosts();

        // =============================================================================================================
        // [ATTACK FUNCTIONS]
        /** hit a chosen target for N damages */
        static void hit(Player& target, int damages);
        /** make this Player attack a chosen target : apply bonus fix and percentage damages */
        void attack(Player& target);
        /** this Player gets hit for N damages : apply fix and percentage resistances */
        void get_hit(int damages);

        // =============================================================================================================
        // [STATE ATTRIBUTES]
        /** is this player dead ? */
        bool is_dead();
        /** is this player currently stun ? */
        [[nodiscard]] bool is_stun() const;

        // =============================================================================================================
        // [ITEMS]
        /** equip one or many items */
        void equip(items::Item item);
        void equip(const std::vector<items::Item>& items);
        void equip(items::enums::ItemList item);
        void equip(const std::vector<items::enums::ItemList>& items);

        // =============================================================================================================
        // [GETTERS & SETTERS]
        [[nodiscard]] std::string getPlayerName() const;
        Player& setPlayerName(std::string playerName) ;
        bool getIsAuto() const;
        Player& setIsAuto(bool isAuto);
        spells::Spell& getSpell();

        // =============================================================================================================
        // UPGRADES
        void apply_upgrade(upgrades::Upgrade upgrade);
    };

}