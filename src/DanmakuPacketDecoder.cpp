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
               zstr::istream decompressStream(&decompressBuf);
               size_t bufferSize = 10240;
               std::unique_ptr<char> bufPtr(new char[bufferSize]);
               std::stringstream ss;
               while (true) {
                   decompressStream.read(bufPtr.get(), static_cast<std::streamsize>(bufferSize));
                   std::streamsize cnt = decompressStream.gcount();
                   if (cnt == 0) break;
                   ss.write(bufPtr.get(), cnt);
               }
               payloadData = ss.str();
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
