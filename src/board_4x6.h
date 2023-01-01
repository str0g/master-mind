/*
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef MASTER_MIND_BOARD_4X6_H
#define MASTER_MIND_BOARD_4X6_H

#include <string>
#include "3state_check.h"
#include "cheats_ifaca.h"
#include "serializer_iface.h"

namespace board_colors {
    enum {
        none = 0,
        blue = 1,
        red = 2,
        orange = 3,
        yellow = 4,
        cyan = 5,
        black = 6
    };
}
namespace board4x6 {
    union Board4x6 {
        struct Board4x6_t {
            uint8_t fx[4];
            void is_valid();
            /**
             * support for no duplicates
             * @TODO support for duplicates
             * @return correct value only for no duplicates.
             */
            ThreeStateCheck::StateCheck cmp(const Board4x6_t&);
            void random_set();
        } board;
        int bin;
    };
    Board4x6 from_string(const std::string &);
    std::string to_string(const Board4x6::Board4x6_t&);
}

class BoardManager: protected CheatsIface, public Serializer {
public:
    void new_board();
    void serialize() final;
    void deserialize() final;
    std::pair<bool, std::string> input(const std::string&);

    BoardManager() = default;

    BoardManager(const BoardManager&) = delete;
    BoardManager(BoardManager&&) = delete;
    BoardManager& operator=(const BoardManager&) = delete;
    BoardManager& operator=(BoardManager&&) = delete;

protected:
    std::string get_boards() const final;
    void change_serialization_file_location(const std::string&) final;
private:
    board4x6::Board4x6 board;
    std::string store_file {"session"};
};

#endif//MASTER_MIND_BOARD_4X6_H
