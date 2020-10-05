#include "packet.h"

namespace ocode {
	PacketReader::PacketReader(uint8* data, uint32 data_size) : data(data), data_size(data_size), reader_pos(0) {}

	PacketReader::PacketReader(ENetPacket* packet) : reader_pos(0) {
		data = packet->data;
		data_size = (uint32)packet->dataLength;
	};

	bool PacketReader::reached_end() {
		return reader_pos == data_size;
	}

	const uint32 PacketReader::size() {
		return data_size - reader_pos;
	}

	PacketReader PacketReader::segment(uint32 segment_size) {
		if (reader_pos + segment_size > data_size) {
			throw std::out_of_range("Packet size error");
		}

		uint8* pos = data + reader_pos;
		reader_pos += segment_size;

		return { pos, segment_size };
	}

	PacketWriter::PacketWriter(uint8 type) : type(type) {

	}

	const uint8 PacketWriter::get_type() {
		return type;
	}

	const uint32 PacketWriter::get_size() {
		writer.seekp(0, std::ios::end);
		return (uint32)writer.tellp();
	}

	std::stringbuf* PacketWriter::get_data() {
		return writer.rdbuf();
	}

	PacketGroup::PacketGroup() {
		writer << (uint8)NetPacketType::DEFAULT;
	}

	void PacketGroup::write_packet(PacketWriter& packet) {
		writer << packet.get_type();

		uint32 size = packet.get_size();
		writer.write((const char*)&size, sizeof(uint32));

		writer << packet.get_data();
	}

	ENetPacket* PacketGroup::to_packet() {
		std::string data = writer.str();

		return enet_packet_create(data.c_str(), data.size(), ENET_PACKET_FLAG_RELIABLE);
	}
}