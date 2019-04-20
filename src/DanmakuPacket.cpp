#include <format.hpp>
#include <json/json.h>
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

#pragma mark - Danmaku Auth Pack
blilive::PacketOperationCode blilive::DanmakuAuthPacket::operationCode() {
    return blilive::PacketOperationCode::Auth;
}

std::string blilive::DanmakuAuthPacket::data() {
    Json::Value root;
    root["uid"] = Json::Int(0);
    root["roomid"] = Json::Int(this->mRoomID);
    root["protover"] = Json::Int(2);
    root["platform"] = Json::StaticString("web");
    root["clientver"] = Json::StaticString("1.4.0");
    return root.toStyledString();
}

#pragma mark - Danmaku Heartbeat Packet
blilive::PacketOperationCode blilive::DanmakuHeartbeatPacket::operationCode() {
    return blilive::PacketOperationCode::ClientHeartbeat;
}

#pragma mark - Danmaku Command Packet
const std::string blilive::DanmakuCommandPacket::Command::RecvDanmaku("DANMU_MSG");
const std::string blilive::DanmakuCommandPacket::Command::SendGift("SEND_GIFT");
const std::string blilive::DanmakuCommandPacket::Command::Welcome("WELCOME");
const std::string blilive::DanmakuCommandPacket::Command::WelcomeGuard("WELCOME_GUARD");
const std::string blilive::DanmakuCommandPacket::Command::SystemMessage("SYS_MSG");
const std::string blilive::DanmakuCommandPacket::Command::Preparing("PREPARING");
const std::string blilive::DanmakuCommandPacket::Command::Live("LIVE");
const std::string blilive::DanmakuCommandPacket::Command::WishBottle("WISH_BOTTLE");

// Inner Command, Not API
const std::string blilive::DanmakuCommandPacket::Command::Unsupport("_Unsupport");

blilive::DanmakuCommandPacket::DanmakuCommandPacket(std::string& jsonStr) {
    this->_jsonString = jsonStr;
}

blilive::PacketOperationCode blilive::DanmakuCommandPacket::operationCode() {
    return blilive::PacketOperationCode::Command;
}

std::string blilive::DanmakuCommandPacket::command() {
    Json::CharReaderBuilder b;
    Json::CharReader *jsonReader(b.newCharReader());
    Json::Value jsonRoot;
    JSONCPP_STRING errs;
    const char *pStr = this->_jsonString.c_str();
    bool success = jsonReader->parse(pStr, pStr + strlen(pStr), &jsonRoot, &errs);
    delete jsonReader;
    if (!success) {
        return blilive::DanmakuCommandPacket::Command::Unsupport;
    }
    return jsonRoot["cmd"].asString();
}
