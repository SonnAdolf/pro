#pragma once
#include "sqlite_utils.h"

class CProStatisticsServ {
private:
	CProStatisticsServ() {}

public:
	//��ȡΨһ���õĶ���
	static CProStatisticsServ& get_inst() {
		static CProStatisticsServ instance;
		return instance;
	}
	std::wstring get_statistics_inf();
};