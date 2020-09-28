#include "packet.h"

PacketReader::PacketReader(Packet* packet) {
	this->packet = packet;

	this->reader_pos = 0;
}

std::string Packet::to_string() {
	char buffer[100];
	sprintf_s(buffer, 100, "Packet: %u %.*s", type, (int)data_size, (char*)data);
	return buffer;
}

ENetPacket* Packet::to_enet_packet() {
	return enet_packet_create(data, data_size, ENET_PACKET_FLAG_RELIABLE);
}