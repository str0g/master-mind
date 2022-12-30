/*
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef MASTER_MIND_3STATE_CHECK_H
#define MASTER_MIND_3STATE_CHECK_H

#include <vector>
#include <string>

namespace ThreeStateCheck {
    enum three_state_check_t {
        NONE = 0,
        ACTIVE = 0x1,
        INCORRECT = 0x2,
    };

    using StateCheck = std::vector<three_state_check_t>;
    std::string to_string(const StateCheck&);
}

#endif//MASTER_MIND_3STATE_CHECK_H
