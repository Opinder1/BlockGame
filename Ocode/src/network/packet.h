 #pragma once

#include "typedef.h"

#include <string>
#include <sstream>
#include <vector>

#include <enet/enet.h>

namespace ocode {

	enum class NetPacketType : uint8 {
		DEFAULT,
		SSL_TO,
		SSL_FROM
	};

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
		const uint32 size();
		PacketReader segment(uint32 segment_size);

		template<class Type>
		Type read() {
			if (reader_pos + sizeof(Type) > data_size) {
				throw std::out_of_range("Packet size error");
			}

			Type var = *(Type*)(data + reader_pos);
			reader_pos += sizeof(Type);

			return var;
		}

		template<>
		std::string read<std::string>() {
			uint32 size = read<uint32>();

			if (reader_pos + size > data_size) {
				throw std::out_of_range("Packet size error");
			}

			std::string var(data + reader_pos, data + reader_pos + size);
			reader_pos += size;

			return var;
		}
	};

	class PacketWriter {
	private:
		uint8 type;
		std::stringstream writer;

	public:
		PacketWriter(uint8 type);
		PacketWriter(const PacketWriter&) = delete;

		const uint8 get_type();
		const uint32 get_size();
		std::stringbuf* get_data();

		template<class Type>
		void write(Type&& data) {
			writer.write((const char*)&data, sizeof(Type));
		}

		template<>
		void write<std::string>(std::string&& data) {
			write(data.size());
			writer << data.c_str();
		}
	};

	class PacketGroup {
	private:
		std::stringstream writer;

	public:
		PacketGroup();
		PacketGroup(const PacketGroup&) = delete;

		void write_packet(PacketWriter& packet);

		ENetPacket* to_packet();
	};
}