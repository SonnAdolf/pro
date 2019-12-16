//
//  sqlite数据库使用函数
//

#include "sqlite_utils.h"

sqlite3* pDB = NULL;

/*
 *  author: 无名
 *  date  : 2018-08-07
 *  note  : close sqlite connection
 */
int sqlite_close() {
	sqlite3_close(pDB);
	return 0;
}


/*
*  author: 无名
*  date  : 2018-08-07
*  note  : connect to sqlite
*/
int sqlite_conn() {
	int nRes = sqlite3_open("data.db", &pDB);
	if (nRes != SQLITE_OK)
		return -1;
	return 0;
}


/*
*  author: 无名
*  date  : 2018-08-07
		   2018-12-21
*  note  : create tables if not exists
*/
bool create_tables() {
	using namespace std;
	//id,writing_pro,reading_pro,art_learning_pro,total_pro,note,str_date,date
	string str_sql = "CREATE TABLE IF NOT EXISTS  pro(id integer  primary key autoincrement,writing_pro integer,reading_pro integer,art_learning_pro integer,total_pro integer,note varchar(500),str_date varchar(11) NOT NULL,date date NOT NULL); ";
	char* cErrMsg;
	int nRes = sqlite3_exec(pDB, str_sql.c_str(), 0, 0, &cErrMsg);
	if (nRes != SQLITE_OK)
		return false;
	return true;
}


