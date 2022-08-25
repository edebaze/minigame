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
    /**
     * Make Player choose an upgrade with prompt :
     *  This function should be in Player object which would grand access to Stuff. Therefore, i would be able to not
     *  present items that the Player already possesses.
     * @return
     */
    champions::upgrades::Upgrade Renderer::choose_upgrade() {
        Renderer::print("Choose an upgrade :");
        int ctr = 1;
        int n_spaces = 0;
        const int MAX_CONTENT_LENGTH = 35;

        std::vector<champions::upgrades::Upgrade> all_upgrades = champions::upgrades::get_upgrades();

        // display all boosts
        for(champions::upgrades::Upgrade upgrade : all_upgrades) {
            // jump a line each 2 propositions (extra jump line on first choice intentional)
            if (ctr % 2 == 1) {
                // get to next line
                Renderer::jump_line();
                // reset n_spaces to 0 (as we will not need to dampen previous content
                n_spaces = 0;
            }

            // get content of the upgrade as string
            std::string content = "[" + std::to_string(ctr) + "] ";
            if (upgrade.getBoost().has_value()) {
                content +=  Renderer::display_boost_upgrade(upgrade.getBoost().value());
            }
            if (upgrade.getItem().has_value()) {
                content +=  Renderer::display_item_upgrade(upgrade.getItem().value());
            }

            // calculate length to determine the number of spaces to add
            /** Note: this is a "+=" assignment as we want to use this content to dampen the previous
             * content in case of previous_content_length > MAX_CONTENT_LENGTH */
            n_spaces += MAX_CONTENT_LENGTH - content.length();
            // display content
            std::cout << content << Renderer::repeat(" ", std::max(0, n_spaces));
            ctr++;
        }

        Renderer::jump_line();

        // get the Player's choice
        int choice;
        std::cin >> choice;
        // choice - 1 : because choices starts at 1
        choice -= 1;

        // check choice
        int choiceCtr = 0;
        while(choice < 0 && choice > all_upgrades.size() && choiceCtr < 3) {
            Renderer::print("Sorry, i did not understood your answer, please choose again");
            std::cin >> choice;
            choice -= 1;
            choiceCtr += 1;
        }

        return all_upgrades[choice];
    }

    std::string Renderer::display_boost_upgrade(Boost boost) {
        std::string myOut;

        if (boost.getHp() != 0) {
            if (! myOut.empty()) myOut += " | ";
            myOut += std::to_string(boost.getHp()) + " hp";
        }
        if (boost.getShield() != 0) {
            if (! myOut.empty()) myOut += " | ";
            myOut += std::to_string(boost.getShield()) + " shield";
        }
        if (boost.getAd() != 0) {
            if (! myOut.empty()) myOut += " | ";
            myOut += std::to_string(boost.getAd()) + " attack damages";
        }
        if (boost.getResistance() != 0) {
            if (! myOut.empty()) myOut += " | ";
            myOut += std::to_string(boost.getResistance()) + " resistances";
        }
        if (boost.getPercDamages() != 1) {
            if (! myOut.empty()) myOut += " | ";
            myOut += std::to_string(boost.getPercDamages()) + "% damages";
        }
        if (boost.getPercResistance() != 1) {
            if (! myOut.empty()) myOut += " | ";
            myOut += std::to_string(boost.getPercResistance()) + "% resistances";
        }

        return myOut;
    }

    std::string Renderer::display_item_upgrade(champions::items::Item item) {
        return item.getName();
    }
}