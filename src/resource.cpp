#include "resource.hpp"
EXTLD(___res_muser_resources_bmp);
	
namespace muser::resource {
	decltype(resources) resources;
	void InitResources() {
		resources.insert_or_assign("muser_resources.bmp", 
			ResourceEntry{reinterpret_cast<const char*>(LDVAR(___res_muser_resources_bmp)),static_cast<len_t>(LDLEN(___res_muser_resources_bmp))});
		
	}
}
