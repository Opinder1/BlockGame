#include "id.h"

const std::string_view get_name(const NameID& id) {
    std::string_view view(id);
    return view.substr(view.find(':') + 1);
}

const std::string_view get_package(const NameID& id) {
    std::string_view view(id);
    return view.substr(0, view.find(':'));
}

IDManager::IDManager() {
    //New id manager for new galaxy
}

IDManager::IDManager(const std::string& file_name) {
    //Load ids from id file in galaxy filespace
}