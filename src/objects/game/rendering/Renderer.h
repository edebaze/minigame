#ifndef UNTITLED_RENDERER_H
#define UNTITLED_RENDERER_H

#include <string>
#include <iostream>
#include <vector>
#include <variant>
#include "./enums/Colors.h"
#include "../../champions/upgrades/Upgrade.h"

/**
 * Rendering class : handle displaying of the information to the console
 */
namespace objects::game::rendering {
    class Renderer {
    public:
        static const int MAX_CONTINUE_REPEAT;
        static Color::Code color;

        // =============================================================================================================
        // MAIN
        static void jump_line();
        static void print(const std::string &message);
        static void separator(const std::string& motif="=", int size = 50);
        static std::string repeat(const std::string& str, int n);

        // =============================================================================================================
        // COLOR & STYLE
        static void set_color(Color::Code color);
        static void reset_style();

        // =============================================================================================================
        // HELLO & GOODBYE
        static void greetings_message();
        static void victory_message();
        static void game_over_message();
        static void good_bye_message();

        // =============================================================================================================
        // LEVEL MESSAGES
        static bool continue_message();

        // =============================================================================================================
        // UPGRADES
        static champions::upgrades::Upgrade choose_upgrade();
        static std::string display_boost_upgrade(Boost boost);
        static std::string display_item_upgrade(champions::items::Item item);

    };
}


#endif //UNTITLED_RENDERER_H
