#pragma once

#include "enet/enet.h"

#include "packet.h"

#include "netclient.h"

#include "netserver.h"

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