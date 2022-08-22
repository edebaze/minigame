#ifndef UNTITLED_ITEMLIST_H
#define UNTITLED_ITEMLIST_H

#include "../Item.h"


namespace objects::champions::items::enums {
    /** List of available items */
    enum class ItemList
    {
        NONE,                   // no equipment : space is free
        DEFAULT_AXE,
        DEFAULT_SWORD,
        DEFAULT_SHIELD,
        SHADOW_AXE,
        SHIELD_OF_THE_HEROES,
        PLATED_ARMOR
    };

    class ItemListUtils {
    public:
        /** get the Item object from its name */
        static Item get(ItemList itemList) {
            switch(itemList) {
                case ItemList::NONE:
                    return Item("NONE", Emplacements::ANY);
                case ItemList::DEFAULT_AXE:
                    return Item("DEFAULT_AXE", Emplacements::RIGHT_HAND).setAd(8);
                case ItemList::DEFAULT_SWORD:
                    return Item("DEFAULT_SWORD", Emplacements::RIGHT_HAND).setAd(5);
                case ItemList::DEFAULT_SHIELD:
                    return Item("DEFAULT_SHIELD", Emplacements::LEFT_HAND).setShield(50);
                case ItemList::SHADOW_AXE:
                    return Item("SHADOW_AXE", Emplacements::LEFT_HAND).setAd(15);
                case ItemList::SHIELD_OF_THE_HEROES:
                    return Item("SHIELD_OF_THE_HEROES", Emplacements::LEFT_HAND).setShield(150).setResistance(5);
                case ItemList::PLATED_ARMOR:
                    return Item("PLATED_ARMOR", Emplacements::CHEST).setHp(50).setResistance(10).setAd(-2);
                default:
                    printf("ITEM LIST ERROR !");
                    // TODO ERROR
                    return Item("", Emplacements::ANY);
            }
        };

        /** get default Champion items associated to each emplacements */
        static std::map<items::enums::Emplacements, items::Item> getDefaultItems() {
            std::map<Emplacements, Item> items = {
                    {Emplacements::HEAD, ItemListUtils::get(ItemList::NONE)},
                    {Emplacements::CHEST, ItemListUtils::get(ItemList::NONE)},
                    {Emplacements::BOOTS, ItemListUtils::get(ItemList::NONE)},
                    {Emplacements::LEFT_HAND, ItemListUtils::get(ItemList::NONE)},
                    {Emplacements::RIGHT_HAND, ItemListUtils::get(ItemList::NONE)},
            };
            return items;
        };
    };
}

#endif //UNTITLED_ITEMLIST_H
