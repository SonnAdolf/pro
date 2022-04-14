#pragma once

#include "sqlite3.h"
#include "str_utils.h"
#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include "pro.h"
#include "book.h"


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

	bool add_pro(CPro pro, std::wstring date) const;

	int get_tag_id_by_name(const std::wstring& name) const;
	
	int get_translator_id_by_name(const std::wstring& name) const;

	int get_author_id_by_name(const std::wstring& name) const;

	int get_publisher_id_by_name(const std::wstring& name) const;

	bool check_if_tag_of_name_exist(const std::wstring& name) const;
	
	bool check_if_author_of_name_exist(const std::wstring& name) const;

	bool check_if_translator_of_name_exist(const std::wstring& name) const;

	bool check_if_publisher_of_name_exist(const std::wstring& name) const;

	int get_last_insert_tag_id() const;

	int get_last_insert_book_id() const;

	int get_last_insert_author_id() const;

	int get_last_insert_translator_id() const;

	int get_last_insert_publisher_id() const;

	int add_tag_ret_id(const std::wstring& name) const;

	int add_author_ret_id(const std::wstring& name) const;

	int add_translator_ret_id(const std::wstring& name) const;

	int add_tag_book_relation(const std::wstring& tag_id, const std::wstring& book_id) const;

	int add_author_book_relation(const std::wstring& author_id, const std::wstring& book_id) const;
	int add_translator_book_relation(const std::wstring& translator_id, const std::wstring& book_id) const;

	int add_publisher_ret_id(const std::wstring& name) const;

	int add_book_review_ret_id(const std::wstring&, const std::wstring& score,
		const std::wstring& publisher_id, const std::wstring& note, const std::wstring& page_num, const std::wstring& date, const std::wstring& pub_year) const;

	bool get_pro_sum_by_month(float* const writing_pro_sum, float* const reading_pro_sum,
		float* const art_learning_pro_sum, float* const computer_learning_pro, float* const total_pro_sum, const int year, const int month) const;


	bool get_pro_sum_by_year(float* const writing_pro_sum, float* const reading_pro_sum,
		float* const art_learning_pro_sum, float* const computer_learning_pro, float* const total_pro_sum, const int year) const;


	bool check_if_pro_of_date_exist(const std::wstring& date) const;


	bool update_pro(CPro pro, const std::wstring& date) const;


	bool get_pro(const std::wstring& date, CPro* pro) const;

	bool get_book_reviews(std::list<CBook>& book_reviews) const;
	bool set_book_reviews_of_authors(std::list<CBook>& book_reviews) const;
	bool set_book_reviews_of_translators(std::list<CBook>& book_reviews) const;
	bool set_book_reviews_of_publisher(std::list<CBook>& book_reviews) const;

	bool get_pro_sum(float* const writing_pro_sum, float* const reading_pro_sum,
		float* const art_learning_pro_sum, float* const computer_learning_pro, float* const total_pro_sum) const;

	bool count_pro_by_month(int* const num, const int year, const int month) const;

	bool count_pro_by_year(int* const num, const int year) const;

	bool count_pro(int* const num) const;
private:
	sqlite3* m_db = NULL;
};