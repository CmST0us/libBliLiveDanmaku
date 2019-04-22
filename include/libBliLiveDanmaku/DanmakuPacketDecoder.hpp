#ifndef DANMAKUPACKETDECODER_HPP
#define DANMAKUPACKETDECODER_HPP

#include <functional>
#include "DanmakuPacket.hpp"

namespace blilive {

class DanmakuPacketDecoder
{
public:
    DanmakuPacketDecoder();
    DanmakuPacketDecoder(const DanmakuPacketDecoder&) = delete;
    const DanmakuPacketDecoder& operator=(const DanmakuPacketDecoder&) = delete;

    using DanmakuPacketDecoderCommandMessageHandler = std::function<void(DanmakuCommandPacket *, std::string command)>;

    DanmakuPacketDecoderCommandMessageHandler mCommandMessageHandler{nullptr};
    void dispatch(const std::string& _data);
private:
    void dispatchCommandPayload(const std::string& data);
}; // DanmakuPacketDecoder

}


#endif // DANMAKUPACKETDECODER_HPP
