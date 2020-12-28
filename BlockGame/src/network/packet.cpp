#include "packet.h"

ENetPacket* PacketWriter::to_packet() {
	stream.seekg(0, stream.end);
	uint32 size = (uint32)stream.tellg();
	stream.seekg(0, stream.beg);

	uint8* buffer = new uint8[size];
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