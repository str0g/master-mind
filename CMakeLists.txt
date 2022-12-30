# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/

cmake_minimum_required(VERSION 3.21)
project(master_mind)

set(CMAKE_CXX_STANDARD 17)

aux_source_directory(src SRC)

add_executable(${PROJECT_NAME} main.cpp ${SRC})

function(custom_test test_name)
    add_executable(${test_name} ../tests/${test_name}.cpp ${SRC})
    target_link_libraries(${test_name} -lgtest -lgtest_main)
    add_test(${test_name} ${test_name})
endfunction()

custom_test(test_board_4x6)
custom_test(test_3state_check)
custom_test(test_board_manager)
