#ifndef RESOURCE_HPP
#define RESOURCE_HPP
#include <map>
#include <string>
#include "embedded_resource.hpp"
namespace muser::resource {
    typedef long long unsigned int len_t;
    struct ResourceEntry {
        const char* start;
        len_t length;
    };
    extern std::map<std::string, ResourceEntry> resources;
    void InitResources();
}
#endif
