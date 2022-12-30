/*
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <gtest/gtest.h>
#include "../src/board_4x6.h"
#include <unordered_map>
#include <filesystem>

std::string g_tests_session {"session_test"};

class Test_BoardManager : public ::testing::Test {
    void SetUp() {
        std::filesystem::remove(g_tests_session);
    }
};

TEST_F(Test_BoardManager, board_init_test) {
    BoardManager bm;
    bm.new_board();

    std::unordered_map<std::string, bool> map;
    for(int i=0; i<10; i++) {
        auto board = Cheats::get_boards(reinterpret_cast<CheatsIface&>(bm));
        try {
            map.at(board);
            ASSERT_TRUE(false);
        } catch (std::out_of_range) {
            map[board] = i;
            bm.new_board();
        }
    }
}

TEST_F(Test_BoardManager, store_load_board) {
    std::string exp;
    {
        BoardManager bm;
        Cheats::change_serialization_file_location(reinterpret_cast<CheatsIface &>(bm), g_tests_session);
        bm.new_board();
        exp = Cheats::get_boards(reinterpret_cast<CheatsIface &>(bm));
        bm.serialize();
        bm.new_board();
        ASSERT_NE(Cheats::get_boards(reinterpret_cast<CheatsIface &>(bm)), exp);

        bm.deserialize();
        ASSERT_EQ(Cheats::get_boards(reinterpret_cast<CheatsIface &>(bm)), exp);
    }
    {
        BoardManager bm;
        Cheats::change_serialization_file_location(reinterpret_cast<CheatsIface &>(bm), g_tests_session);
        bm.deserialize();
        ASSERT_EQ(Cheats::get_boards(reinterpret_cast<CheatsIface &>(bm)), exp);
    }
}