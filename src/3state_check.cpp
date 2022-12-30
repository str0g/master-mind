/*
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "3state_check.h"

namespace ThreeStateCheck {
    std::string to_string(const StateCheck& obj) {
        std::string rc;
        rc.reserve(obj.size());

        for(auto& o : obj) {
            rc.push_back(o+48);
        }
        return rc;
    }
}