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
	int add_tag_ret_id(const std::wstring& name) const;
	int add_author_ret_id(const std::wstring& name) const;
	int add_translator_ret_id(const std::wstring& name) const;
	int add_publisher_ret_id(const std::wstring& name) const;
	int add_book_review_ret_id(const std::wstring& name, const std::wstring& score,
		const std::wstring& publisher_id, const std::wstring& note, const std::wstring& page_num, const std::wstring& date, const std::wstring& pub_year) const;
	int add_tag_book_relation(const std::wstring& tag_id, const std::wstring& book_id) const;
	int add_author_book_relation(const std::wstring& author_id, const std::wstring& book_id) const;
	int add_translator_book_relation(const std::wstring& translator_id, const std::wstring& book_id) const;
	bool get_book_reviews(std::list<CBook>& book_reviews) const;
};