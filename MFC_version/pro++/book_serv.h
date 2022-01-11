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
	int add_author_ret_id(std::wstring name);
	int add_translator_ret_id(std::wstring name);
	int add_publisher_ret_id(std::wstring name);
	int add_book_review_ret_id(std::wstring name, std::wstring score,
		std::wstring publisher_id, std::wstring note, std::wstring page_num, std::wstring date, std::wstring pub_year);
	int add_tag_book_relation(std::wstring tag_id, std::wstring book_id);
	int add_author_book_relation(std::wstring author_id, std::wstring book_id);
	int add_translator_book_relation(std::wstring translator_id, std::wstring book_id);
};