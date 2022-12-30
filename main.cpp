/*
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <iostream>
#include "src/board_4x6.h"

void help() {
    std::cout <<
            "q - quit\n"
            "n - new game\n"
            "s - save and quit\n"
            "l - load\n"
            "Input 4 numbers in range 1-6"
    << std::endl;
}

int main() {
    help();

    BoardManager bm;

    bm.new_board();

    bool loop = true;
    std::string input;
    while(loop) {
        std::cin >> input;
        switch (input[0]) {
            case 'q':
                loop = false;
                std::cout << "board was: " << Cheats::get_boards(reinterpret_cast<CheatsIface&>(bm)) << std::endl;
                break;
            case 'n':
                bm.new_board();
                std::cout << "new game" << std::endl;
                break;
            case 'c':
                std::cout << "board is: " << Cheats::get_boards(reinterpret_cast<CheatsIface&>(bm)) << std::endl;
                break;
            case 's':
                std::cout << "saved and quit" << std::endl;
                bm.serialize();
                loop = false;
                break;
            case 'r':
                bm.deserialize();
                std::cout << "game has been restored" << std::endl;
                break;
            default:
                try {
                    auto rc = bm.input(input);
                    if(rc.first) {
                        std::cout << "victory" << std::endl;
                        loop = false;
                    } else {
                        std::cout << rc.second << std::endl;
                    }
                } catch (const std::invalid_argument& e) {
                    //ignore
                }
        }
    }

    return 0;
}
