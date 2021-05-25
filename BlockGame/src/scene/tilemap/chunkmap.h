#pragma once

#include <ocode.h>

#include <unordered_map>

#include "chunk.h"

class ChunkMap {
	enum class ChunkType : glm::uint8 { EMPTY, LOADED, RECENT, CLIENT_SIDE };

	struct ChunkHeader {
		ChunkType status;
		Chunk* chunk;

		ChunkHeader(ChunkType status, Chunk* chunk) : status(status), chunk(chunk) {}
	};

private:
	std::unordered_map<glm::uint64, ChunkHeader> chunks;

public:
	ChunkMap(const ChunkMap&) = delete;
	ChunkMap() {}

	void insert_empty_chunk(glm::uint64 pos) {
		chunks.try_emplace(pos, ChunkHeader(ChunkType::EMPTY, nullptr));
	}

	void insert_chunk(glm::uint64 pos, Chunk* chunk) {
		chunks.try_emplace(pos, ChunkHeader(ChunkType::LOADED, nullptr));
	}
};

class SceneVoxelMap : ChunkMap {
private:
	glm::uint64 private_key;
	glm::uint64 public_key;
};

// class EntityVoxelMap : Entity {};