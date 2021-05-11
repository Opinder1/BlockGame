#pragma once

#include <ocode.h>

#include <string>
#include <unordered_map>

#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

using ID = uint64;
using NameID = std::string;

NameID path_to_id(const fs::path& path);

class IDManager {
	using ID_Map = std::unordered_map<NameID, ID>;
	using ID_RMap = std::unordered_map<ID, NameID>;

private:
	ID_Map id_map;
	ID_RMap id_rmap;

public:
	IDManager(const IDManager&) = delete;
	IDManager();
	IDManager(const std::string& file_name);

	void add_new_id(const NameID& id);

	void get_id(const NameID& id);
	void get_nameid(const ID id);
};