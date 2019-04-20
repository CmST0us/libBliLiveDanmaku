#include <iostream>
#include <format.hpp>
#include <json/json.h>
#include <memory>
#include <zstr.hpp>

#include "DanmakuPacket.hpp"

int main(int argc, char *argv[]) {
    auto packet = blilive::DanmakuPacket();
    packet.mVersion = 2;
    packet.mHeaderSize = 11;
    auto d = packet.encode();
    auto e = d.c_str();
    return 0;
}
