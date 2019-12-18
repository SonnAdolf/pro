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
*  date  : 2019-12-18
*  note  : create tables if not exists
*/
bool create_tables() {
	using namespace std;
	//id,writing_pro,reading_pro,art_learning_pro,total_pro,note,str_date,date
	string str_sql = "CREATE TABLE IF NOT EXISTS  pro(id integer  primary key autoincrement,writing_pro integer,reading_pro integer,art_learning_pro integer,total_pro integer,note varchar(500),date date NOT NULL); ";
	char* cErrMsg;
	int nRes = sqlite3_exec(pDB, str_sql.c_str(), 0, 0, &cErrMsg);
	if (nRes != SQLITE_OK)
		return false;
	return true;
}


bool add_pro_today(CPro pro) {
	using namespace std;
	time_t t = time(0);
	wchar_t ch_time[20];
	wcsftime(ch_time, sizeof(ch_time)/2, L"%Y-%m-%d", localtime(&t));

	wstring sql = L"INSERT INTO pro(writing_pro, reading_pro, art_learning_pro, total_pro,note,date) VALUES ('";
	sql.append(pro.get_writing_pro_str()).append(L"','").append(pro.get_reading_pro_str()).append(L"','").append(pro.get_art_learning_pro_str());
	sql.append(L"','").append(pro.get_total_pro_str()).append(L"','").append(pro.get_note()).append(L"','").append(ch_time).append(L"');");

	std::string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	// sqlite使用utf-8编码，汉字需要转
	string str_utf8_sql = ascii_2_utf8(str_sql);

	char* errmsg;
	if (sqlite3_exec(pDB, str_utf8_sql.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
		cout << "sqlite : insert data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	return true;
}


