#include "resource.hpp"
EXTLD(___res_hi_txt);
	EXTLD(___res_muser_resources_bmp);
	
namespace muser::resource {
	decltype(resources) resources;
	void InitResources() {
		resources.insert_or_assign("hi.txt", 
			std::string(reinterpret_cast<const char*>(LDVAR(___res_hi_txt)),static_cast<int>(LDLEN(___res_hi_txt))));
		resources.insert_or_assign("muser_resources.bmp", 
			std::string(reinterpret_cast<const char*>(LDVAR(___res_muser_resources_bmp)),static_cast<int>(LDLEN(___res_muser_resources_bmp))));
		
	}
}
