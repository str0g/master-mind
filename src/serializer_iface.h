/*
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef MASTER_MIND_SERIALIZER_IFACE_H
#define MASTER_MIND_SERIALIZER_IFACE_H

#include <string>

class Serializer {
public:
    virtual void serialize() = 0;
    virtual void deserialize() = 0;
    virtual ~Serializer() = default;
};

#endif//MASTER_MIND_SERIALIZER_IFACE_H
