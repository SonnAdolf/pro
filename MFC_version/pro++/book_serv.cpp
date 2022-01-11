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

int CBookServ::add_tag_ret_id(std::wstring name) {
	return CSqliteUtils::get_inst().add_tag_ret_id(name);
}

int CBookServ::add_author_ret_id(std::wstring name) {
	return CSqliteUtils::get_inst().add_author_ret_id(name);
}

int CBookServ::add_translator_ret_id(std::wstring name) {
	return CSqliteUtils::get_inst().add_translator_ret_id(name);
}
int CBookServ::add_tag_book_relation(std::wstring tag_id, std::wstring book_id) {
	return CSqliteUtils::get_inst().add_tag_book_relation(tag_id, book_id);
}
int CBookServ::add_author_book_relation(std::wstring author_id, std::wstring book_id) {
	return CSqliteUtils::get_inst().add_author_book_relation(author_id, book_id);
}
int CBookServ::add_translator_book_relation(std::wstring translator_id, std::wstring book_id) {
	return CSqliteUtils::get_inst().add_translator_book_relation(translator_id, book_id);
}
int CBookServ::add_book_review_ret_id(std::wstring name, std::wstring score,
	std::wstring publisher_id, std::wstring note, std::wstring page_num, std::wstring date, std::wstring pub_year) {
	return CSqliteUtils::get_inst().add_book_review_ret_id(name, score,
		publisher_id, note, page_num, date, pub_year);
}

int CBookServ::add_publisher_ret_id(std::wstring name) {
	return CSqliteUtils::get_inst().add_publisher_ret_id(name);
}