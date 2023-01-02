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
#include <cstring>

namespace board4x6 {
    Board4x6 from_string(const std::string &in) {
        Board4x6 row;
        auto *ptr = row.board.fx;
        *ptr = in[0] - 48;
        *(++ptr) = in[1] - 48;
        *(++ptr) = in[2] - 48;
        *(++ptr) = in[3] - 48;
        row.board.is_valid();
        return row;
    }

    std::string to_string(const Board4x6::Board4x6_t &obj) {
        auto *ptr = obj.fx;
        return {
                static_cast<char>(*ptr + 48),
                static_cast<char>(*(++ptr) + 48),
                static_cast<char>(*(++ptr) + 48),
                static_cast<char>(*(++ptr) + 48)};
    }

    void Board4x6::Board4x6_t::is_valid() {
        auto tester = [](uint8_t in) {
            if (in <= board_colors::none or board_colors::black < in) {
                throw std::invalid_argument("invalid row");
            }
        };
        auto *ptr = fx;
        tester(*ptr++);
        tester(*ptr++);
        tester(*ptr++);
        tester(*ptr);
    }

    void Board4x6::Board4x6_t::random_set() {
        auto fun = []() {
            return (board_colors::none + 1) + rand() % board_colors::black;// far from being random but does exactly what intended.
        };
        auto *ptr = fx;
        *ptr = fun();
        *(++ptr) = fun();
        *(++ptr) = fun();
        *(++ptr) = fun();
    }

    ThreeStateCheck::StateCheck Board4x6::Board4x6_t::cmp(const Board4x6::Board4x6_t &obj) {
        ThreeStateCheck::StateCheck rc;

        auto tab_init = [](unsigned char* out_tab, size_t out_size, const unsigned char* in_tab, size_t in_size) {
            std::memset(out_tab, 0, out_size);
            for(int i=0; i<in_size; ++i) {
                out_tab[in_tab[i]] += 1;
            }
            for(int i=0; i<out_size; ++i) {
                if(not out_tab[i]) {
                    out_tab[i] = 0xff;
                }
            }
        };

        unsigned char none = 0xff;

        unsigned char this_tab[board_colors::black+1];
        tab_init(this_tab, sizeof(this_tab), fx, sizeof(fx));

        unsigned char obj_tab[sizeof(this_tab)];
        tab_init(obj_tab, sizeof(obj_tab), obj.fx, sizeof(obj.fx));

        auto get_index = [](const unsigned char* fx, unsigned char num, int offset=0) {
            auto *fxx = fx + offset;
            auto *end = fx + sizeof(Board4x6::Board4x6_t::fx);
            do {
                if(*fxx == num) return fxx - fx;
            } while(++fxx < end);
            throw std::out_of_range("");
        };

        auto active_or_incorrect = [&](unsigned char val, int cnt){
            int index = 0;
            int index_obj = 0;
            do {
                try {
                    index = get_index(fx, val, index);
                    if(fx[index] == obj.fx[index]) {
                        rc[index++] = ThreeStateCheck::ACTIVE;
                        index_obj = index;
                    } else {
                        index_obj = get_index(obj.fx, val, index_obj);
                        rc[index_obj++] = ThreeStateCheck::INCORRECT;
                        ++index;
                    }
                } catch (const std::out_of_range& e) {
                    //ignore
                }
            } while (cnt--);
        };

        auto size = sizeof(fx);
        rc.resize(size);

        for(int i=board_colors::blue; i<=board_colors::black; ++i) {
            if(this_tab[i] == none and obj_tab[i] != none) continue;
            if (this_tab[i] == none and obj_tab[i] == none) continue;
            if (this_tab[i] != none and obj_tab[i] == none) continue;
            auto res = this_tab[i] - obj_tab[i];
            if(res) {
                if(res < 0) {
                    res *= -1;
                }
                active_or_incorrect(i, res);
            } else {
                auto cnt = this_tab[i];
                active_or_incorrect(i, cnt);
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