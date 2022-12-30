/*
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "board_4x6.h"

#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>

namespace board4x6 {
    Board4x6 from_string(const std::string &in) {

        Board4x6 row;
        row.board.f1 = in[0] - 48;
        row.board.f2 = in[1] - 48;
        row.board.f3 = in[2] - 48;
        row.board.f4 = in[3] - 48;
        row.board.is_valid();
        return row;
    }

    std::string to_string(const Board4x6::Board4x6_t& obj) {
        return {
                static_cast<char>(obj.f1 + 48),
                static_cast<char>(obj.f2 + 48),
                static_cast<char>(obj.f3 + 48),
                static_cast<char>(obj.f4 + 48)
        };
    }

    void Board4x6::Board4x6_t::is_valid() {
        auto tester = [](uint8_t in) {
            if (in <= board_colors::none or board_colors::black < in) {
                throw std::invalid_argument("invalid row");
            }
        };
        tester(f1);
        tester(f2);
        tester(f3);
        tester(f4);
    }

    void Board4x6::Board4x6_t::random_set() {
        auto fun = []() {
            return (board_colors::none+1) + rand() % board_colors::black; // far from being random but does exactly what intended.
        };
        f1 = fun();
        f2 = fun();
        f3 = fun();
        f4 = fun();
    }

    ThreeStateCheck::StateCheck Board4x6::Board4x6_t::cmp(const Board4x6::Board4x6_t& obj) {
        ThreeStateCheck::StateCheck rc;

        auto obj_str = to_string(obj);
        auto this_str = to_string(*this);

        rc.resize(obj_str.size());

        for(auto i=0; i<this_str.size(); ++i) {
            for(auto x=0; x<obj_str.size(); ++x) {
                //std::cout << "i: " << i << " x: " << x << " this: " << this_str[i] << " obj:" << obj_str[x];
                if(i==x and this_str[i] == obj_str[x]) {
                    //std::cout << " active" << std::endl;
                    rc[i] = ThreeStateCheck::ACTIVE;
                    break;
                }
                if(rc[i]){
                    //std::cout << " ignore" << std::endl;
                    continue;
                }
                if(this_str[i] == obj_str[x]) {
                    //std::cout << " incorrect" << std::endl;
                    rc[i]= ThreeStateCheck::INCORRECT;
                    continue;
                }
                //std::cout << std::endl;
            }
        }

        return rc;
    }
}

void BoardManager::new_board() {
    board.board.random_set();
}

std::pair<bool, std::string> BoardManager::input(const std::string &in) {

    if(in.size() != 4) {
        throw std::invalid_argument("invalid size");
    }

    auto row = board4x6::from_string(in);
    auto res = this->board.board.cmp(row.board);

    if (row.bin == board.bin) {
        return {true, ThreeStateCheck::to_string(res)};
    } else {
        return {false, ThreeStateCheck::to_string(res)};
    }
}

std::string BoardManager::get_boards() const {
    return board4x6::to_string(board.board);
}

void BoardManager::change_serialization_file_location(const std::string& new_store_file) {
    store_file = new_store_file;
}

void BoardManager::serialize() {
    std::ofstream f(store_file, std::ios::binary);
    f.write(reinterpret_cast<const char*>(&board.bin), sizeof(board.bin));
    f.close();
}

void BoardManager::deserialize() {
    std::ifstream f(store_file, std::fstream::binary);
    if (!f.is_open()) {
        std::cerr << store_file << std::endl;
        throw std::runtime_error("file not found");
    }
    f.read(reinterpret_cast<char*>(&board.bin), sizeof(board.bin));
    f.close();
}