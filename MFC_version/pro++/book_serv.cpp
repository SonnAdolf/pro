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