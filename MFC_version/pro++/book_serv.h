#pragma once
#include "sqlite_utils.h"

class CBookServ {
private:
	CBookServ() {}

public:
	//获取唯一可用的对象
	static CBookServ& get_inst() {
		static CBookServ instance;
		return instance;
	}
	int add_tag_ret_id(std::wstring name);
};