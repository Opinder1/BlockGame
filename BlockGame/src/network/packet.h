#pragma once

#include <ocode.h>

#include <enet/enet.h>
#include <sstream>

enum class PacketType : glm::uint8 {
    UNENCRYPTED,
    SSL_FROM,
    SSL_TO
};

struct Packet {
    PacketType type;
    glm::uint8* data;
    glm::uint32 data_size;
};

class PacketWriter {
	friend struct PacketSendEvent;
	friend struct PacketBroadcastEvent;

private:
	PacketType type;

	std::stringstream stream;

	ENetPacket* to_packet();

public:
	PacketWriter(const PacketWriter&) = delete;
	PacketWriter(PacketType type) : type(type) {
		write(type);
	}

	template<class Type>
	void write(Type&& data) {
		stream.write((char*)&data, sizeof(Type));
	}

	template<class Type>
	void write(Type* data, glm::uint32 size) {
		stream.write((char*)data, sizeof(Type) * size);
	}

	template<class Type>
	void write_string(std::basic_string<Type>&& data) {
		write((glm::uint32)data.size());
		write(data.data(), (glm::uint32)data.size());
	}
};

class PacketReader {
private:
	const Packet& packet;

	glm::uint32 reader_pos;

public:
	PacketReader(const PacketReader&) = delete;
	PacketReader(const Packet& packet) : packet(packet), reader_pos(0) {}

	bool reached_end();

	template<class Type>
	Type read() {
		if (reader_pos + sizeof(Type) > packet.data_size) {
			throw std::length_error(std::string("message size error reading (") + typeid(Type).name() + ") type");
		}

		Type var = *(Type*)(packet.data + reader_pos);
		reader_pos += sizeof(Type);

		return var;
	}

	template<class Type>
	std::basic_string<Type> read_string() {
		glm::uint32 size = read<glm::uint32>();

		if (reader_pos + size > packet.data_size) {
			throw std::length_error("Message size error reading (string) type");
		}

		std::basic_string<Type> var(packet.data + reader_pos, packet.data + reader_pos + size);
		reader_pos += size;

		return var;
	}
};

struct PacketSendEvent : ocode::Event {
	ENetPeer* peer;
	ENetPacket* packet;

	PacketSendEvent(ENetPeer* peer, PacketWriter& writer) : peer(peer), packet(writer.to_packet()) {}
};

struct PacketBroadcastEvent : ocode::Event {
	ENetPacket* packet;

	PacketBroadcastEvent(PacketWriter& writer) : packet(writer.to_packet()) {}
};

struct PacketReciveEvent : ocode::Event {
	ENetPeer* peer;
	Packet packet;

	PacketReciveEvent(ENetPeer* peer, PacketType type, glm::uint8* data, glm::uint32 data_size) : peer(peer), packet{ type, data, data_size } {}
};