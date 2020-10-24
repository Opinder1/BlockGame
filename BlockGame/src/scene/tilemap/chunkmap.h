#pragma once

#include "ocode.h"

#include <unordered_map>

#include "chunk.h"

class ChunkMap {
	enum class ChunkType : uint8 { EMPTY, LOADED, RECENT, CLIENT_SIDE };

	struct ChunkHeader {
		ChunkType status;
		Chunk* chunk;

		ChunkHeader(ChunkType status, Chunk* chunk) : status(status), chunk(chunk) {}
	};

private:
	std::unordered_map<uint64, ChunkHeader> chunks;

public:
	ChunkMap(const ChunkMap&) = delete;
	ChunkMap() {}

	void insert_empty_chunk(uint64 pos) {
		chunks.try_emplace(pos, ChunkHeader(ChunkType::EMPTY, nullptr));
	}

	void insert_chunk(uint64 pos, Chunk* chunk) {
		chunks.try_emplace(pos, ChunkHeader(ChunkType::LOADED, nullptr));
	}
};

class SceneVoxelMap : ChunkMap {
private:
	uint64 private_key;
	uint64 public_key;
};

// class EntityVoxelMap : Entity {};