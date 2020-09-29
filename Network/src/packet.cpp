#include "packet.h"

PacketReader::PacketReader(uint8* data, uint32 data_size) : data(data), data_size(data_size) {}

PacketReader::PacketReader(ENetPacket* packet) : reader_pos(0) {
	data = packet->data;
	data_size = (uint32)packet->dataLength;
};

bool PacketReader::reached_end() {
	return reader_pos >= data_size;
}

uint32 PacketReader::size() {
	return data_size - reader_pos;
}

std::string PacketReader::read_string(uint32 size) {
	std::string var(data + reader_pos, data + reader_pos + size);
	reader_pos += size;
	return var;
}

uint8* PacketReader::segment(uint32 size) {
	uint8* pos = data + reader_pos;
	reader_pos += size;
	return pos;
}

PacketWriter::PacketWriter(uint8 type) {
	writer << type;
}

ENetPacket* PacketWriter::to_packet() {
	std::string data = writer.str();
	return enet_packet_create(data.c_str(), data.size(), ENET_PACKET_FLAG_RELIABLE);
}