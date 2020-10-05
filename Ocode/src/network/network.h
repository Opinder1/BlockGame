#pragma once

#include <enet/enet.h>

#include "nethost.h"

#include "packet.h"

namespace ocode {

    class ENetInit {
    public:
        inline ENetInit() {
            if (enet_initialize() == 0) {
                initialised = true;
            }
        }

        inline ~ENetInit() {
            enet_deinitialize();
        }

        inline static bool initialised = false;
    };

    inline ENetInit instance;
}