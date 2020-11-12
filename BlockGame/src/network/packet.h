#pragma once

#include "ocode.h"

#include <enet/enet.h>
#include <sstream>

enum class PacketType : uint8 {
    UNENCRYPTED,
    SSL_FROM,
    SSL_TO
};

struct Packet {
    PacketType type;
    uint8* data;
    uint32 data_size;
};

class PacketWriter {
	friend class PacketSendEvent;

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
	void write(Type* data, uint32 size) {
		stream.write((char*)data, sizeof(Type) * size);
	}

	template<class Type>
	void write_string(std::basic_string<Type>&& data) {
		write((uint32)data.size());
		write(data.data(), (uint32)data.size());
	}
};

class PacketReader {
private:
	const Packet& packet;

	uint32 reader_pos;

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
		uint32 size = read<uint32>();

		if (reader_pos + size > packet.data_size) {
			throw std::length_error("Message size error reading (string) type");
		}

		std::basic_string<Type> var(packet.data + reader_pos, packet.data + reader_pos + size);
		reader_pos += size;

		return var;
	}
};

class PacketSendEvent : ocode::Event {
private:
	ENetPeer* peer;

	ENetPacket* packet;

public:
	PacketSendEvent(ENetPeer* peer, PacketWriter& writer) : peer(peer), packet(writer.to_packet()) {}

	inline const std::string to_string() const override {
		return std::string("PacketSendEvent: ");
	}

	ENetPeer* get_peer() const;
	ENetPacket* get_packet() const;
};

class PacketBroadcastEvent : public PacketSendEvent {
public:
	PacketBroadcastEvent(PacketWriter& writer) : PacketSendEvent(NULL, writer) {}

	const std::string to_string() const override;
};

class PacketReciveEvent : ocode::Event {
private:
	ENetPeer* peer;

	Packet packet;

public:
	PacketReciveEvent(ENetPeer* peer, PacketType type, uint8* data, uint32 data_size) : peer(peer), packet{ type, data, data_size } {}

	inline const std::string to_string() const override {
		return std::string("PacketReviceEvent: ") + std::to_string((uint8)packet.type) + std::string(packet.data, packet.data + packet.data_size);
	}

	ENetPeer* get_peer() const;
	PacketReader get_packet() const;
};