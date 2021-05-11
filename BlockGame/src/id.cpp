#include "id.h"

std::string get_name(const NameID& id) {
    return id.substr(id.find(':') + 1);
}

std::string get_package(const NameID& id) {
    return id.substr(0, id.find(':'));
}

IDManager::IDManager() {
    //New id manager for new galaxy
}

IDManager::IDManager(const std::string& file_name) {
    //Load ids from id file in galaxy filespace
}