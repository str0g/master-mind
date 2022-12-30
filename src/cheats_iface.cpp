/*
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "cheats_ifaca.h"

std::string Cheats::get_boards(const CheatsIface& obj) {
    return obj.get_boards();
}

void Cheats::change_serialization_file_location(CheatsIface& obj, const std::string& new_store_session) {
    obj.change_serialization_file_location(new_store_session);
}