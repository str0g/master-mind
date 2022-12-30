/*
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef MASTER_MIND_CHEATS_IFACA_H
#define MASTER_MIND_CHEATS_IFACA_H

#include <string>

class CheatsIface;

class Cheats {
public:
    static std::string get_boards(const CheatsIface&);
    static void change_serialization_file_location(CheatsIface&, const std::string&);
};

class CheatsIface {
public:
    virtual ~CheatsIface() = default;
protected:
    virtual std::string get_boards() const = 0;
    virtual void change_serialization_file_location(const std::string&) = 0;

    friend Cheats;
};

#endif//MASTER_MIND_CHEATS_IFACA_H
