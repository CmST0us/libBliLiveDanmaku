#include <format.hpp>
#include <zstr.hpp>
#include "DanmakuPacketDecoder.hpp"

void blilive::DanmakuPacketDecoder::dispatch(std::string& data) {
   format::byte_array array(data);
   try {
       while (array.get_bytes_available() > 0) {
           auto packetSize = array.read_uint32();
           auto headerSize = array.read_uint16();
           auto version = array.read_uint16();
           auto operationCode = array.read_uint32();
           auto sequence = array.read_uint32();
           auto rawPayloadData = array.read_data(packetSize - headerSize);

           bool isCompressedPayload = version == 2;
           std::string payloadData;

           if (isCompressedPayload) {
               // 压缩数据

               std::stringbuf b;
               b.sputn(rawPayloadData.c_str(), static_cast<std::streamsize>(rawPayloadData.size()));
               zstr::istreambuf decompressBuf(&b);
               size_t decompressedSize = static_cast<size_t>(decompressBuf.in_avail());
               if (decompressedSize == 0) {
                   continue;
               }

               std::unique_ptr<char> bufPtr(new char[decompressedSize]);
               memset(static_cast<void *>(bufPtr.get()), 0, decompressedSize);
               decompressBuf.sgetn(bufPtr.get(), static_cast<std::streamsize>(decompressedSize));
               payloadData = std::string(bufPtr.get(), decompressedSize);
               this->dispatch(payloadData);
           } else {
               // 非压缩数据
               payloadData = rawPayloadData;
               if (operationCode == static_cast<int>(blilive::PacketOperationCode::Command)) {
                   this->dispatchCommandPayload(payloadData);
               }
           }
       }
   } catch (format::error e) {
        std::cout<<"[Decoder][Error]: decode error "<<static_cast<int>(e);
   }
}

void blilive::DanmakuPacketDecoder::dispatchCommandPayload(std::string &data) {
    auto commandPacket = blilive::DanmakuCommandPacket(data);
    auto command = commandPacket.command();
    if (command == blilive::DanmakuCommandPacket::Command::RecvDanmaku) {
        auto danmuPacket = new blilive::DanmakuCommandDanmuMessagePacket(data);
        if (this->mCommandMessageHandler != nullptr) {
            this->mCommandMessageHandler(danmuPacket, command);
        }
    }
}
