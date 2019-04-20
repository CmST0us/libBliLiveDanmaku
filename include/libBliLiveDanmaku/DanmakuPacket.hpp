#ifndef DANMAKUPACKET_HPP
#define DANMAKUPACKET_HPP

#include <iostream>
#include <string>

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
    virtual PacketOperationCode operationCode();
    uint16_t mHeaderSize = 16;
    uint16_t mVersion = 1;
    uint32_t mSequence = 1;
    virtual std::string data();
    virtual std::string encode();


}; // DanmakuPacket

class DanmakuAuthPacket: public DanmakuPacket {
public:
    int mRoomID = 0;
    virtual PacketOperationCode operationCode() override;
    virtual std::string data() override;
}; // DanmakuAuthPacket

class DanmakuHeartbeatPacket: public DanmakuPacket {
public:
    virtual PacketOperationCode operationCode() override;
}; // DanmakuHeartbeatPacket;

class DanmakuCommandPacket: public DanmakuPacket {
public:
    struct Command {
        static const std::string RecvDanmaku;
        static const std::string SendGift;
        static const std::string Welcome;
        static const std::string WelcomeGuard;
        static const std::string SystemMessage;
        static const std::string Preparing;
        static const std::string Live;
        static const std::string WishBottle;

        // Inner Command, Not API
        static const std::string Unsupport;
    };

    DanmakuCommandPacket(std::string& jsonStr);
    virtual PacketOperationCode operationCode() override;
    std::string command();

protected:
    std::string _jsonString = "";
};


} //blilive

#endif // DANMAKUPACKET_HPP
