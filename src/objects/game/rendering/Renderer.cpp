#include <variant>
#include "Renderer.h"

namespace objects::game::rendering {

    const int Renderer::MAX_CONTINUE_REPEAT = 3;
    Color::Code Renderer::color = Color::Code::RESET;

    // =================================================================================================================
    // MAIN
    void Renderer::jump_line() {
        std::cout << std::endl;
    }

    void Renderer::print(const std::string &message) {
        std::cout << Renderer::color << message << Color::RESET <<  std::endl;
    }

    void Renderer::separator(const std::string &motif, int size) {
        Renderer::print(Renderer::repeat(motif, size));
    }

    std::string Renderer::repeat(const std::string &str, int n) {
        std::string repeat;

        for (int i = 0; i < n; i++)
            repeat += str;

        return repeat;
    }

    // =================================================================================================================
    // COLOR & STYLE
    void Renderer::reset_style()
    {
        Renderer::color = Color::Code::RESET;
    }

    void Renderer::set_color(Color::Code colorCode)
    {
        Renderer::color = colorCode;
    }

    // =================================================================================================================
    // HELLO & GOODBYE
    void Renderer::greetings_message() {
        Renderer::print("Welcome in <Legends of Chaos> !");
    }

    void Renderer::victory_message() {
        Renderer::print("CONGRATULATION !!!");
        Renderer::print("This is an A-MA-ZING victory i can't imagine that someone like you even exists");
    }

    void Renderer::game_over_message() {
        Renderer::set_color(Color::Code::FG_RED);

        Renderer::print("╔═══╗");
        Renderer::print("║╔═╗║");
        Renderer::print("║║░╚╬══╦╗╔╦══╗ ╔══╦╗╔╦══╦═╗");
        Renderer::print("║║╔═╣╔╗║╚╝║║═╣ ║╔╗║╚╝║║═╣╔╝");
        Renderer::print("║╚╩═║╔╗║║║║║═╣ ║╚╝╠╗╔╣║═╣║ ");
        Renderer::print("╚═══╩╝╚╩╩╩╩══╝ ╚══╝╚╝╚══╩╝ ");

        Renderer::reset_style();

        Renderer::print("Nice try, but not nice enough... Better luck next time ?");

    }

    void Renderer::good_bye_message() {
        Renderer::print("Very well");
        Renderer::print("Thanks for playing this game ! Cya");
    }

    // =================================================================================================================
    // LEVEL MESSAGES
    bool Renderer::continue_message() {
        int ctr = 0;
        std::string choice;
        std::string firstSentence = "Well done ! This is fairly impressive, this game is such high skill !!!";

        Renderer::separator();
        while (choice != "y" && choice != "n" && ctr <= Renderer::MAX_CONTINUE_REPEAT) {
            ctr++;
            Renderer::print(firstSentence);
            Renderer::print("Do you wish to continue ?");
            Renderer::print("[y] YES   [n] NO");

            std::cin >> choice;

            firstSentence = "Sorry, i did not understood your choice";
        }

        return choice == "y";
    }

    // =================================================================================================================
    // UPGRADES
    std::variant<Boost,champions::items::Item> Renderer::choose_upgrade() {
        Renderer::print("Choose an upgrade :");
        int ctr = 1;
        int n_spaces = 0;
        const int MAX_CONTENT_LENGTH = 35;

        std::vector<std::variant<Boost,champions::items::Item>> all_upgrades = {};

        // display all boosts
        for(Boost boost : champions::upgrades::Upgrades::boosts) {
            // jump a line each 2 propositions (extra jump line on first choice intentional)
            if (ctr % 2 == 1) {
                // get to next line
                Renderer::jump_line();
                // reset n_spaces to 0 (as we will not need to dampen previous content
                n_spaces = 0;
            }

            // get content of the upgrade as string
            std::string content = "[" + std::to_string(ctr) + "] " + Renderer::display_boost_upgrade(boost);
            // calculate length to determine the number of spaces to add
            /** Note: this is a "+=" assignment as we want to use this content to dampen the previous
             * content in case of previous_content_length > MAX_CONTENT_LENGTH */
            n_spaces += MAX_CONTENT_LENGTH - content.length();
            // display content
            std::cout << content << Renderer::repeat(" ", std::max(0, n_spaces));

            all_upgrades.emplace_back(boost);
        }

        // display all boosts
        for(champions::items::enums::ItemList itemName : champions::upgrades::Upgrades::items) {
            // jump a line each 2 propositions (extra jump line on first choice intentional)
            if (ctr % 2 == 1) {
                // get to next line
                Renderer::jump_line();
                // reset n_spaces to 0 (as we will not need to dampen previous content
                n_spaces = 0;
            }

            champions::items::Item item = champions::items::enums::ItemListUtils::get(itemName);
            // get content of the upgrade as string
            std::string content = "[" + std::to_string(ctr) + "] " + Renderer::display_item_upgrade(item);
            // calculate length to determine the number of spaces to add
            n_spaces += MAX_CONTENT_LENGTH - content.length();
            // display content
            std::cout << content << Renderer::repeat(" ", std::max(0, n_spaces));

            all_upgrades.emplace_back(item);
        }

        // get the Player's choice
        int choice;
        std::cin >> choice;

        // TODO : check of choice

        return all_upgrades[choice];
    }

    std::string Renderer::display_boost_upgrade(Boost boost) {
        std::string myOut;

        if (boost.getHp() != 0) {
            myOut += std::to_string(boost.getHp()) + " hp";
        }
        if (boost.getShield() != 0) {
            myOut += std::to_string(boost.getHp()) + " shield";
        }
        if (boost.getAd() != 0) {
            myOut += std::to_string(boost.getHp()) + " attack damages";
        }
        if (boost.getResistance() != 0) {
            myOut += std::to_string(boost.getHp()) + " resistances";
        }
        if (boost.getPercDamages() != 0) {
            myOut += std::to_string(boost.getHp()) + " % damages";
        }
        if (boost.getPercResistance() != 0) {
            myOut += std::to_string(boost.getHp()) + " % resistances";
        }

        return myOut;
    }

    std::string Renderer::display_item_upgrade(champions::items::Item item) {
        return item.getName();
    }
}