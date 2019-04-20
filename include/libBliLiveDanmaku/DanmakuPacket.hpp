#ifndef DANMAKUPACKET_HPP
#define DANMAKUPACKET_HPP

#include <iostream>
#include <string>
#include <format.hpp>
namespace blilive
{

// Operation Code
enum class PacketOperationCode {
    ClientHeartbeat = 2,
    PopularValue = 3,
    Command = 5,
    Auth = 7,
    ServerHeartbeart = 8,
};

class DanmakuPacket {
public:
    DanmakuPacket();
    virtual ~DanmakuPacket();
    virtual uint32_t packetSize();
    virtual blilive::PacketOperationCode operationCode();
    uint16_t mHeaderSize = 16;
    uint16_t mVersion = 1;
    uint32_t mSequence = 1;
    virtual std::string data();
    virtual std::string encode();


}; // DanmakuPacket

} //blilive

#endif // DANMAKUPACKET_HPP
