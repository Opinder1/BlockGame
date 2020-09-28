#pragma once

#include "typedef.h"

#include <string>
#include <cstdio>

#include "enet/enet.h"

struct Packet {
	uint8 type;
	void* data;
	size_t data_size;

	ENetPacket* to_enet_packet();

	std::string to_string();
};

class PacketWriter {
private:
	size_t writer_pos;

public:
	Packet* packet;
};

class PacketReader {
private:
	uint64 reader_pos;

public:
	Packet* packet;

	PacketReader(Packet* packet);

	std::string read(uint64 size) {
		std::string var((char*)packet->data + reader_pos, (char*)packet->data + reader_pos + size);
		reader_pos += size;
		return var;
	}

	template<class Type>
	Type read() {
		Type var = *(Type*)((char*)packet->data + reader_pos);
		reader_pos += sizeof(Type);
		return var;
	}
};