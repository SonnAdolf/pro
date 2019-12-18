#pragma once

#include "sqlite3.h"
#include "str_utils.h"
#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include "pro.h"

extern char g_strDevSn[32];


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


bool add_pro_today(CPro pro);


