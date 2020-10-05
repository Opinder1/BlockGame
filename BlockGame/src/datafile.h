#include "typedef.h"

#include <fstream>
#include <cstdio>

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>

#include "ocode.h"

inline void load_data_file(std::string file_name, rapidjson::Document& data) {
	if (!ocode::file_exists(file_name)) {
		ocode::create_file(file_name);
	}

	FILE* file;
	fopen_s(&file, file_name.c_str(), "rb");

	char buffer[4096];
	rapidjson::FileReadStream stream(file, buffer, sizeof(buffer));

	data.ParseStream(stream);
}

inline void save_data_file(std::string file_name, const rapidjson::Document& data) {
	FILE* file;
	fopen_s(&file, file_name.c_str(), "wb");

	char buffer[4096];
	rapidjson::FileWriteStream stream(file, buffer, sizeof(buffer));

	rapidjson::Writer writer(stream);
	data.Accept(writer);
}