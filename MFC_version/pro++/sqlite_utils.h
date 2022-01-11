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

	int get_tag_id_by_name(std::wstring name);
	
	int get_translator_id_by_name(std::wstring name);

	int get_author_id_by_name(std::wstring name);

	int get_publisher_id_by_name(std::wstring name);

	bool check_if_tag_of_name_exist(std::wstring name);
	
	bool check_if_author_of_name_exist(std::wstring name);

	bool check_if_translator_of_name_exist(std::wstring name);

	bool check_if_publisher_of_name_exist(std::wstring name);

	int get_last_insert_tag_id();

	int get_last_insert_book_id();

	int get_last_insert_author_id();

	int get_last_insert_translator_id();

	int get_last_insert_publisher_id();

	int add_tag_ret_id(std::wstring name);

	int add_author_ret_id(std::wstring name);

	int add_translator_ret_id(std::wstring name);

	int add_tag_book_relation(std::wstring tag_id, std::wstring book_id);

	int add_author_book_relation(std::wstring author_id, std::wstring book_id);
	int add_translator_book_relation(std::wstring translator_id, std::wstring book_id);

	int add_publisher_ret_id(std::wstring name);

	int add_book_review_ret_id(std::wstring name, std::wstring score,
		std::wstring publisher_id, std::wstring note, std::wstring page_num, std::wstring date, std::wstring pub_year);

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