#include <format.hpp>
#include "DanmakuPacket.hpp"

blilive::DanmakuPacket::DanmakuPacket() {

}

blilive::DanmakuPacket::~DanmakuPacket() {

}

std::string blilive::DanmakuPacket::encode() {
    format::byte_array array;
    auto data = this->data();
    array.write(this->packetSize())
         .write(this->mHeaderSize)
         .write(this->mVersion)
         .write(static_cast<uint32_t>(this->operationCode()))
         .write(this->mSequence)
         .write(data);
    return array.get_data();
}

uint32_t blilive::DanmakuPacket::packetSize() {
    return static_cast<uint32_t>(this->mHeaderSize + this->data().size());
}

blilive::PacketOperationCode blilive::DanmakuPacket::operationCode() {
    return blilive::PacketOperationCode::ClientHeartbeat;
}

std::string blilive::DanmakuPacket::data() {
    return std::string();
}
