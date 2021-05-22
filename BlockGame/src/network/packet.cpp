#include "packet.h"

ENetPacket* PacketWriter::to_packet() {
	stream.seekg(0, stream.end);
	glm::uint32 size = (glm::uint32)stream.tellg();
	stream.seekg(0, stream.beg);

	glm::uint8* buffer = new glm::uint8[size];
	stream.read((char*)buffer, size);

	ENetPacket* enet_packet = enet_packet_create(buffer, size, ENET_PACKET_FLAG_RELIABLE | ENET_PACKET_FLAG_NO_ALLOCATE);

	enet_packet->userData = buffer;
	enet_packet->freeCallback = [](ENetPacket* packet) {
		delete packet->userData;
	};

	return enet_packet;
}

bool PacketReader::reached_end() {
	return reader_pos == packet.data_size;
}