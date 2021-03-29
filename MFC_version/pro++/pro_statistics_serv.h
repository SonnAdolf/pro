#pragma once
#include "sqlite_utils.h"

class CProStatisticsServ {
private:
	CProStatisticsServ() {}

public:
	//获取唯一可用的对象
	static CProStatisticsServ& get_inst() {
		static CProStatisticsServ instance;
		return instance;
	}
	std::wstring get_statistics_inf();
};