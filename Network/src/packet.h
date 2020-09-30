 #pragma once

#include "typedef.h"

#include <string>
#include <sstream>

#include "enet/enet.h"

namespace Packet {
	enum Type {
		DEFAULT, SSL_TO, SSL_FROM
	};
}

class PacketReader {
private:
	uint8* data;
	uint32 data_size;

	uint32 reader_pos;

public:
	PacketReader(uint8* data, uint32 data_size);
	PacketReader(ENetPacket* packet);
	PacketReader(const PacketReader&) = delete;

	bool reached_end();
	uint32 size();

	template<class Type>
	Type read() {
		Type var = *(Type*)(data + reader_pos);
		reader_pos += sizeof(Type);
		return var;
	}

	std::string read_string(uint32 size);

	uint8* segment(uint32 size);
};

class PacketWriter {
private:
	std::stringstream writer;

public:
	PacketWriter(uint8 type);
	PacketWriter(const PacketWriter&) = delete;

	template<class Type>
	void write(Type&& data) {
		writer << data;
	}

	ENetPacket* to_packet();
};