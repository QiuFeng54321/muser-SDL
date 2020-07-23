#ifndef RESOURCE_HPP
#define RESOURCE_HPP
#include <map>
#include <string>
#include "embedded_resource.hpp"
namespace muser::resource {
    // struct ResourceEntry {
    //     const unsigned char* start;
    //     int length;
    // };
    extern std::map<std::string, std::string> resources;
    void InitResources();
}
#endif
