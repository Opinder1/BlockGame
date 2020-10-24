#include "ofa.h"

namespace ocode {
    OFA::OFA(const std::string& archive_name) : Partial_File(archive_name) {
        this->read_scalar(this->meta_compressed_size);

        this->read_scalar(this->meta_size);

        Virtual_File archive_meta = this->load_partial_compressed("header", 8, this->meta_compressed_size, this->meta_size);

        archive_meta.read(this->file_count);

        for (uint32 file_index = 0; file_index < this->file_count; file_index++) {

            uint16 file_name_size;
            std::string file_name;

            archive_meta.read(file_name_size);

            archive_meta.read(file_name, file_name_size);

            File_Meta file_meta;

            archive_meta.read(file_meta.compressed_size);

            archive_meta.read(file_meta.size);

            archive_meta.read(file_meta.pos);

            this->files.emplace(file_name, file_meta);
        }
    }

    OFA::~OFA() {

    }

    void OFA::print_files() {
        for (auto file : this->files) {
            println("Name: %s", file.first.data());
        }
    }

    void OFA::error(const std::string& reason) {
        println("OFA Error: Error reading archive: %s\n Reason: %s", this->file_name.data(), reason.data());
    }

    bool OFA::contains_file(const std::string& file_name) {
        return this->files.find(file_name) != this->files.end();
    }

    Virtual_File OFA::operator[](const std::string& file_name) {
        if (!this->contains_file(file_name)) {
            println("OFA Error: Could not find the file %s in the archive %s", file_name.data(), this->file_name.data());
        }

        File_Meta file_meta = this->files.at(file_name);

        return this->load_partial_compressed(file_name, 8 + this->meta_compressed_size + file_meta.pos, file_meta.compressed_size, file_meta.size);
    }
}