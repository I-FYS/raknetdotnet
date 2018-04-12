#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <winsock2.h>

#define NETCODE_CONNCOOKIELULZ 0x6969
#define NETGAME_VERSION 4057

#include "PacketEnumerations.h"
#include "RakNetworkFactory.h"
#include "RakClientInterface.h"
#include "NetworkTypes.h"
#include "BitStream.h"
#include "StringCompressor.h"

#include "samp_netencr.h"
#include "samp_auth.h"
#include "SAMPRPC.h"
#include "SAMP_VER.h"