#include "datafile.h"

namespace ocode {
	Config::Config(const std::string& name) {
		file_name = name + ".yml";

		try {
			load_data_file(file_name, tree);
		}
		catch (const char*) {
			tree.SetObject();
		}
	}

	Config::~Config() {
		save();
	}

	void Config::save() {
		save_data_file(file_name, tree);
	}

	void load_data_file(std::string file_name, json::Document& data) {
		if (!ocode::file_exists(file_name)) {
			ocode::create_file(file_name);
		}

		FILE* file;
		fopen_s(&file, file_name.c_str(), "rb");

		if (file == NULL) {
			throw "Could not open file";
		}

		char buffer[4096];
		json::FileReadStream stream(file, buffer, sizeof(buffer));

		data.ParseStream(stream);

		if (fclose(file) != 0) {
			throw "Could not close file";
		}

		if (data.HasParseError()) {
			ocode::data_file_error(data);
			throw "Data parse error";
		}
	}

	void save_data_file(std::string file_name, const json::Document& data) {
		FILE* file;
		fopen_s(&file, file_name.c_str(), "wb");

		if (file == NULL) {
			throw "Could not open file";
		}

		char buffer[4096];
		json::FileWriteStream stream(file, buffer, sizeof(buffer));

		json::Writer writer(stream);
		data.Accept(writer);

		if (fclose(file) != 0) {
			throw "Could not close file";
		}
	}

	void data_file_error(const json::Document& data) {
		printf("Error at position %llu: %s\n", data.GetErrorOffset(), json::GetParseError_En(data.GetParseError()));
	}
}