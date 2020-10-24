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

const std::string PacketSendEvent::to_string() const {
	return std::string("PacketSendEvent: ");
}

ENetPeer* PacketSendEvent::get_peer() const {
	return peer;
}

ENetPacket* PacketSendEvent::get_packet() const {
	return packet;
}

const std::string PacketBroadcastEvent::to_string() const {
	return std::string("PacketBroadcastEvent: ");
}

const std::string PacketReciveEvent::to_string() const {
    return std::string("PacketReviceEvent: ") + std::to_string((uint8)packet.type) + std::string(packet.data, packet.data + packet.data_size);
}

ENetPeer* PacketReciveEvent::get_peer() const {
    return peer;
}

PacketReader PacketReciveEvent::get_packet() const {
    return PacketReader(packet);
}