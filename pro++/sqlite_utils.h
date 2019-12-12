#pragma once

#include "sqlite3.h"
#include <iostream>
#include <string>
#include <list>
#include <algorithm>

extern char g_strDevSn[32];


/*
*  author: 无名
*  date  : 2018-08-07
*  note  : close sqlite connection
*/
int sqliteClose();


/*
*  author: 无名
*  date  : 2018-08-07
*  note  : connect to sqlite
*/
int sqliteConn();


