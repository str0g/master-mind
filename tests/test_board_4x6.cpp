/*
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <gtest/gtest.h>
#include "../src/board_4x6.h"

class Test_Board4x6 : public ::testing::Test {
};

TEST_F(Test_Board4x6, board_to_int) {
    board4x6::Board4x6 board;
    board.board.fx[0] = 4;
    board.board.fx[1] = 3;
    board.board.fx[2] = 2;
    board.board.fx[3] = 1;

    ASSERT_EQ(board.bin, 16909060);
}

TEST_F(Test_Board4x6, board_int_to_fields) {
    board4x6::Board4x6 board;
    board.bin = 16909060;

    ASSERT_EQ(board.board.fx[0], 4);
    ASSERT_EQ(board.board.fx[1], 3);
    ASSERT_EQ(board.board.fx[2], 2);
    ASSERT_EQ(board.board.fx[3], 1);
}

TEST_F(Test_Board4x6, is_valid_yes) {
    board4x6::Board4x6 board;
    board.bin = 16909060;

    ASSERT_NO_THROW(board.board.is_valid());
}

TEST_F(Test_Board4x6, is_valid_no) {
    board4x6::Board4x6 board{0};
    ASSERT_THROW(board.board.is_valid(), std::invalid_argument);

    board.board.fx[0] = 1;
    ASSERT_THROW(board.board.is_valid(), std::invalid_argument);

    board.board.fx[1] = 1;
    ASSERT_THROW(board.board.is_valid(), std::invalid_argument);

    board.board.fx[2] = 1;
    ASSERT_THROW(board.board.is_valid(), std::invalid_argument);

    board.board.fx[3] = 1;
    ASSERT_NO_THROW(board.board.is_valid());

    board.board.fx[3] = board_colors::black;
    ASSERT_NO_THROW(board.board.is_valid());

    board.board.fx[3] += 1;
    ASSERT_THROW(board.board.is_valid(), std::invalid_argument);
}

TEST_F(Test_Board4x6, from_string) {
    auto board = board4x6::from_string("4321");
    ASSERT_EQ(board.bin, 16909060);
}

TEST_F(Test_Board4x6, to_string) {
    board4x6::Board4x6 board { .bin = 16909060 };
    auto str = board4x6::to_string(board.board);

    ASSERT_EQ(str, "4321");
}

TEST_F(Test_Board4x6, from_string_invalid) {
    ASSERT_THROW(board4x6::from_string("i1234"), std::invalid_argument);
    ASSERT_THROW(board4x6::from_string("0234"), std::invalid_argument);
    ASSERT_THROW(board4x6::from_string("1237"), std::invalid_argument);
}

TEST_F(Test_Board4x6, cmp_equal) {
    board4x6::Board4x6 left { .bin = 16909060 };
    board4x6::Board4x6 right { .bin = 16909060 };

    auto res = left.board.cmp(right.board);
    auto out = ThreeStateCheck::to_string(res);

    ASSERT_EQ(out, "1111");
}

TEST_F(Test_Board4x6, cmp_not_eq_last) {
    board4x6::Board4x6 left { .bin = 16909060 };
    board4x6::Board4x6 right = board4x6::from_string("4322");

    auto res = left.board.cmp(right.board);
    auto out = ThreeStateCheck::to_string(res);

    ASSERT_EQ(out, "1110");
}

TEST_F(Test_Board4x6, cmp_order) {
    board4x6::Board4x6 left { .bin = 16909060 };
    board4x6::Board4x6 right = board4x6::from_string("1234");

    auto res = left.board.cmp(right.board);
    auto out = ThreeStateCheck::to_string(res);

    ASSERT_EQ(out, "2222");
}

TEST_F(Test_Board4x6, cmp_order_mix) {
    board4x6::Board4x6 left { .bin = 16909060 };
    board4x6::Board4x6 right = board4x6::from_string("3531");

    auto res = left.board.cmp(right.board);
    auto out = ThreeStateCheck::to_string(res);

    //4321
    //3531
    ASSERT_EQ(out, "2001");
}


TEST_F(Test_Board4x6, cmp_order_mix2) {
    board4x6::Board4x6 left = board4x6::from_string("6251");
    board4x6::Board4x6 right = board4x6::from_string("1111");

    //std::cout << "====" << std::endl;
    auto res = left.board.cmp(right.board);
    auto out = ThreeStateCheck::to_string(res);

    /*std::cout << "-----" << std::endl;
    std::cout << (int)res[0] << std::endl;
    std::cout << (int)res[1] << std::endl;
    std::cout << (int)res[2] << std::endl;
    std::cout << (int)res[3] << std::endl;
    std::cout << "out:" << out << std::endl;*/
    ASSERT_EQ(out, "0001");
}

TEST_F(Test_Board4x6, cmp_order_mix3) {
    board4x6::Board4x6 left = board4x6::from_string("2542");
    {
        board4x6::Board4x6 right = board4x6::from_string("4631");
        auto res = left.board.cmp(right.board);
        auto out = ThreeStateCheck::to_string(res);
        ASSERT_EQ(out, "2000");
    }
    {
        board4x6::Board4x6 right = board4x6::from_string("4361");
        auto res = left.board.cmp(right.board);
        auto out = ThreeStateCheck::to_string(res);
        ASSERT_EQ(out, "2000");
    }
    {
        board4x6::Board4x6 right = board4x6::from_string("1234");
        auto res = left.board.cmp(right.board);
        auto out = ThreeStateCheck::to_string(res);
        ASSERT_EQ(out, "0202");
    }
    {
        board4x6::Board4x6 right = board4x6::from_string("2261");
        auto res = left.board.cmp(right.board);
        auto out = ThreeStateCheck::to_string(res);
        ASSERT_EQ(out, "1200");
    }
    {
        board4x6::Board4x6 right = board4x6::from_string("3322");
        auto res = left.board.cmp(right.board);
        auto out = ThreeStateCheck::to_string(res);
        ASSERT_EQ(out, "0021");
    }
    {
        board4x6::Board4x6 right = board4x6::from_string("2322");
        auto res = left.board.cmp(right.board);
        auto out = ThreeStateCheck::to_string(res);
        ASSERT_EQ(out, "1001");
    }
}