#pragma once

#include "sqlite3.h"
#include "str_utils.h"
#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include "pro.h"


class CSqliteUtils {
private:
	CSqliteUtils() {}

public:
	//获取唯一可用的对象
	static CSqliteUtils& get_inst() {
		static CSqliteUtils instance;
		return instance;
	}

	CSqliteUtils(const CSqliteUtils&) = delete;

	CSqliteUtils& operator=(const CSqliteUtils&) = delete;

	/*
	*  author: 无名
	*  date  : 2018-08-07
	*  note  : close sqlite connection
	*/
	int sqlite_close();


	/*
	*  author: 无名
	*  date  : 2018-08-07
	*  note  : connect to sqlite
	*/
	int sqlite_conn();


	/*
	*  author: 无名
	*  date  : 2018-08-07
			   2018-12-21
	*  note  : create tables if not exists
	*/
	bool create_tables();


	bool add_pro(CPro pro, std::wstring date);


	bool get_pro_sum_by_month(float* const writing_pro_sum, float* const reading_pro_sum,
		float* const art_learning_pro_sum, float* const computer_learning_pro, float* const total_pro_sum, const int year, const int month);


	bool get_pro_sum_by_year(float* const writing_pro_sum, float* const reading_pro_sum,
		float* const art_learning_pro_sum, float* const computer_learning_pro, float* const total_pro_sum, const int year);


	bool check_if_pro_of_date_exist(std::wstring date);


	bool update_pro(CPro pro, std::wstring date);


	bool get_pro(std::wstring date, CPro* pro);


	bool get_pro_sum(float* const writing_pro_sum, float* const reading_pro_sum,
		float* const art_learning_pro_sum, float* const computer_learning_pro, float* const total_pro_sum);

	bool count_pro_by_month(int* const num, const int year, const int month);

	bool count_pro_by_year(int* const num, const int year);

	bool count_pro(int* const num);
private:
	sqlite3* m_db = NULL;
};