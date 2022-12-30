/*
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <gtest/gtest.h>
#include "../src/3state_check.h"

class Test_ThreeStateCheck : public ::testing::Test {
};

TEST_F(Test_ThreeStateCheck, StateCheck_to_string) {
    ThreeStateCheck::StateCheck obj {ThreeStateCheck::ACTIVE,ThreeStateCheck::INCORRECT,ThreeStateCheck::ACTIVE,ThreeStateCheck::ACTIVE};
    auto out = ThreeStateCheck::to_string(obj);
    ASSERT_EQ(out, "1211");
}