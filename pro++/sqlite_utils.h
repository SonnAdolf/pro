#pragma once

#include "sqlite3.h"
#include <iostream>
#include <string>
#include <list>
#include <algorithm>

extern char g_strDevSn[32];


/*
*  author: ����
*  date  : 2018-08-07
*  note  : close sqlite connection
*/
int sqliteClose();


/*
*  author: ����
*  date  : 2018-08-07
*  note  : connect to sqlite
*/
int sqliteConn();


