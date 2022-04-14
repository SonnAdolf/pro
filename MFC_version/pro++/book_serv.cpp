//////////////////////////////////////////////////////////////////////////  
/// @file    book_serv.cpp    
/// @brief   impl some functions about book  
///  
/// impl functions of book  
///  
/// @version 1.0     
/// @author  ÎÞÃû    
/// @date    2021/09/03
////////////////////////////////////////////////////////////////////////// 
#include "book_serv.h"

int CBookServ::add_tag_ret_id(const std::wstring& name) const {
	return CSqliteUtils::get_inst().add_tag_ret_id(name);
}

int CBookServ::add_author_ret_id(const std::wstring& name) const {
	return CSqliteUtils::get_inst().add_author_ret_id(name);
}

int CBookServ::add_translator_ret_id(const std::wstring& name) const {
	return CSqliteUtils::get_inst().add_translator_ret_id(name);
}
int CBookServ::add_tag_book_relation(const std::wstring& tag_id, const std::wstring& book_id) const {
	return CSqliteUtils::get_inst().add_tag_book_relation(tag_id, book_id);
}
int CBookServ::add_author_book_relation(const std::wstring& author_id, const std::wstring& book_id) const {
	return CSqliteUtils::get_inst().add_author_book_relation(author_id, book_id);
}
int CBookServ::add_translator_book_relation(const std::wstring& translator_id, const std::wstring& book_id) const {
	return CSqliteUtils::get_inst().add_translator_book_relation(translator_id, book_id);
}
int CBookServ::add_book_review_ret_id(const std::wstring& name, const std::wstring& score,
	const std::wstring& publisher_id, const std::wstring& note, const std::wstring& page_num, const std::wstring& date, const std::wstring& pub_year) const {
	return CSqliteUtils::get_inst().add_book_review_ret_id(name, score,
		publisher_id, note, page_num, date, pub_year);
}

int CBookServ::add_publisher_ret_id(const std::wstring& name) const {
	return CSqliteUtils::get_inst().add_publisher_ret_id(name);
}

bool CBookServ::get_book_reviews(std::list<CBook>& book_reviews) const {
	return CSqliteUtils::get_inst().get_book_reviews(book_reviews);
}