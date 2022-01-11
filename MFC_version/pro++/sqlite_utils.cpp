//
//  sqlite数据库使用函数
//

#include "sqlite_utils.h"


/*
 *  author: 无名
 *  date  : 2018-08-07
 *  note  : close sqlite connection
 */
int CSqliteUtils::sqlite_close() {
	sqlite3_close(m_db);
	return 0;
}


/*
*  author: 无名
*  date  : 2018-08-07
*  note  : connect to sqlite
*/
int CSqliteUtils::sqlite_conn() {
	int nRes = sqlite3_open("data.db", &m_db);
	if (nRes != SQLITE_OK)
		return -1;
	return 0;
}


/*
*  author: 无名
*  date  : 2019-12-18
*  note  : create tables if not exists
*/
bool CSqliteUtils::create_tables() {
	using namespace std;
	//id,writing_pro,reading_pro,art_learning_pro,total_pro,note,str_date,date
	string str_sql = "CREATE TABLE IF NOT EXISTS  pro(id integer primary key autoincrement,writing_pro integer,reading_pro integer,art_learning_pro integer,computer_science_tech_pro integer,total_pro integer,note varchar(500),date date NOT NULL);\
		CREATE TABLE IF NOT EXISTS author(id integer primary key autoincrement,name varchar(30));\
		CREATE TABLE IF NOT EXISTS tag(id integer primary key autoincrement, name varchar(30));\
		CREATE TABLE IF NOT EXISTS translator(id integer primary key autoincrement, name varchar(30));\
		CREATE TABLE IF NOT EXISTS publisher(id integer primary key autoincrement, name varchar(30));\
		CREATE TABLE IF NOT EXISTS book(id integer primary key autoincrement,note varchar(900),name varchar(50) not null,date date not null,score integer check(-1<score and score<101) not null,page_num integer check(page_num>0),pub_year integer check(pub_year>0 and pub_year<3000),publisher_id integer references publisher(id));\
		CREATE TABLE IF NOT EXISTS book_tag(id integer primary key autoincrement,book_id integer references book(id),tag_id integer references tag(id));\
		CREATE TABLE IF NOT EXISTS book_author(id integer primary key autoincrement, book_id integer references book(id), author_id integer references author(id));\
		CREATE TABLE IF NOT EXISTS book_translator(id integer primary key autoincrement, book_id integer references book(id), translator_id integer references translator(id));\
		";
	//CREATE TABLE IF NOT EXISTS movie(id integer primary key autoincrement, note varchar(900), name varchar(50), date date not null, score integer check(-1 < score and score < 101)); \
	//CREATE TABLE IF NOT EXISTS game(id integer primary key autoincrement, note varchar(900), name varchar(50), date date not null, score integer check(-1 < score and score < 101));
	char* cErrMsg;
	int nRes = sqlite3_exec(m_db, str_sql.c_str(), 0, 0, &cErrMsg);
	if (nRes != SQLITE_OK)
		return false;
	return true;
}


bool CSqliteUtils::add_pro(CPro pro, std::wstring date) {
	using namespace std;
	int pos;
	pos = date.find(L"/");
	while (pos != -1) {
		// str.length()求字符的长度，注意str必须是string类型
		date.replace(pos, wstring(L"/").length(), L"-");
		pos = date.find(L"/");
	}

	wstring sql = L"INSERT INTO pro(writing_pro, reading_pro, art_learning_pro, computer_science_tech_pro, total_pro, note, date) VALUES ('";
	sql.append(pro.get_writing_pro_str()).append(L"','").append(pro.get_reading_pro_str()).append(L"','").append(pro.get_art_learning_pro_str());
	sql.append(L"','").append(pro.get_computer_learning_pro_str()).append(L"','").append(pro.get_total_pro_str()).append(L"','");
	sql.append(pro.get_note()).append(L"','").append(date).append(L"');");

	std::string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	// sqlite使用utf-8编码，汉字需要转
	string str_utf8_sql = ascii_2_utf8(str_sql);

	char* errmsg;
	if (sqlite3_exec(m_db, str_utf8_sql.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
		cout << "sqlite : insert data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	return true;
}

bool CSqliteUtils::check_if_tag_of_name_exist(std::wstring name) {
	using namespace std;
	wstring sql = L"select count(*) from tag where name='";
	sql.append(name);
	sql.append(L"';");
	std::string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(m_db, str_sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	int nIndex = nCol;
	char* test = pResult[nIndex];
	int num = atoi(pResult[nIndex]);
	if (num > 0)
		return true;
	return false;
}

bool CSqliteUtils::check_if_author_of_name_exist(std::wstring name) {
	using namespace std;
	wstring sql = L"select count(*) from author where name='";
	sql.append(name);
	sql.append(L"';");
	std::string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(m_db, str_sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	int nIndex = nCol;
	if (atoi(pResult[nIndex]) > 0)
		return true;
	return false;
}

bool CSqliteUtils::check_if_translator_of_name_exist(std::wstring name) {
	using namespace std;
	wstring sql = L"select count(*) from translator where name='";
	sql.append(name);
	sql.append(L"';");
	std::string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(m_db, str_sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	int nIndex = nCol;
	if (atoi(pResult[nIndex]) > 0)
		return true;
	return false;
}

bool CSqliteUtils::check_if_publisher_of_name_exist(std::wstring name) {
	using namespace std;
	wstring sql = L"select count(*) from publisher where name='";
	sql.append(name);
	sql.append(L"';");
	std::string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(m_db, str_sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	int nIndex = nCol;
	if (atoi(pResult[nIndex]) > 0)
		return true;
	return false;
}

int CSqliteUtils::get_tag_id_by_name(std::wstring name) {
	using namespace std;
	wstring sql = L"select id from tag where name = '";
	sql.append(name).append(L"';");
	string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(m_db, str_sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return -1;
	}
	if (nRow == 0 || nCol == 0)
		return -1;
	int nIndex = nCol;
	int id;
	if (pResult[nIndex] == NULL || strcmp(pResult[nIndex], "") == 0)
	{
		id = -1;
	}
	else
	{
		id = static_cast<int>(atoi(pResult[nIndex]));
	}
	return id;
}

int CSqliteUtils::get_author_id_by_name(std::wstring name) {
	using namespace std;
	wstring sql = L"select id from author where name = '";
	sql.append(name).append(L"';");
	string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(m_db, str_sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return -1;
	}
	if (nRow == 0 || nCol == 0)
		return -1;
	int nIndex = nCol;
	int id;
	if (pResult[nIndex] == NULL || strcmp(pResult[nIndex], "") == 0)
	{
		id = -1;
	}
	else
	{
		id = static_cast<int>(atoi(pResult[nIndex]));
	}
	return id;
}

int CSqliteUtils::get_translator_id_by_name(std::wstring name) {
	using namespace std;
	wstring sql = L"select id from translator where name = '";
	sql.append(name).append(L"';");
	string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(m_db, str_sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return -1;
	}
	if (nRow == 0 || nCol == 0)
		return -1;
	int nIndex = nCol;
	int id;
	if (pResult[nIndex] == NULL || strcmp(pResult[nIndex], "") == 0)
	{
		id = -1;
	}
	else
	{
		id = static_cast<int>(atoi(pResult[nIndex]));
	}
	return id;
}

int CSqliteUtils::get_publisher_id_by_name(std::wstring name) {
	using namespace std;
	wstring sql = L"select id from publisher where name = '";
	sql.append(name).append(L"';");
	string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(m_db, str_sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return -1;
	}
	if (nRow == 0 || nCol == 0)
		return -1;
	int nIndex = nCol;
	int id;
	if (pResult[nIndex] == NULL || strcmp(pResult[nIndex], "") == 0)
	{
		id = -1;
	}
	else
	{
		id = static_cast<int>(atoi(pResult[nIndex]));
	}
	return id;
}

int CSqliteUtils::get_last_insert_tag_id() {
	using namespace std;
	wstring sql = L"select last_insert_rowid() from tag;";
	string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(m_db, str_sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return -1;
	}
	if (nRow == 0 || nCol == 0)
		return -1;
	int nIndex = nCol;
	int id;
	if (pResult[nIndex] == NULL || strcmp(pResult[nIndex], "") == 0)
	{
		id = -1;
	}
	else
	{
		id = static_cast<int>(atoi(pResult[nIndex]));
	}
	return id;
}

int CSqliteUtils::get_last_insert_book_id() {
	using namespace std;
	wstring sql = L"select last_insert_rowid() from book;";
	string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(m_db, str_sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return -1;
	}
	if (nRow == 0 || nCol == 0)
		return -1;
	int nIndex = nCol;
	int id;
	if (pResult[nIndex] == NULL || strcmp(pResult[nIndex], "") == 0)
	{
		id = -1;
	}
	else
	{
		id = static_cast<int>(atoi(pResult[nIndex]));
	}
	return id;
}

int CSqliteUtils::get_last_insert_author_id() {
	using namespace std;
	wstring sql = L"select last_insert_rowid() from author;";
	string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(m_db, str_sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return -1;
	}
	if (nRow == 0 || nCol == 0)
		return -1;
	int nIndex = nCol;
	int id;
	if (pResult[nIndex] == NULL || strcmp(pResult[nIndex], "") == 0)
	{
		id = -1;
	}
	else
	{
		id = static_cast<int>(atoi(pResult[nIndex]));
	}
	return id;
}

int CSqliteUtils::get_last_insert_translator_id() {
	using namespace std;
	wstring sql = L"select last_insert_rowid() from translator;";
	string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(m_db, str_sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return -1;
	}
	if (nRow == 0 || nCol == 0)
		return -1;
	int nIndex = nCol;
	int id;
	if (pResult[nIndex] == NULL || strcmp(pResult[nIndex], "") == 0)
	{
		id = -1;
	}
	else
	{
		id = static_cast<int>(atoi(pResult[nIndex]));
	}
	return id;
}

int CSqliteUtils::get_last_insert_publisher_id() {
	using namespace std;
	wstring sql = L"select last_insert_rowid() from publisher;";
	string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(m_db, str_sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return -1;
	}
	if (nRow == 0 || nCol == 0)
		return -1;
	int nIndex = nCol;
	int id;
	if (pResult[nIndex] == NULL || strcmp(pResult[nIndex], "") == 0)
	{
		id = -1;
	}
	else
	{
		id = static_cast<int>(atoi(pResult[nIndex]));
	}
	return id;
}

int CSqliteUtils::add_tag_ret_id(std::wstring name) {
	using namespace std;

	if (check_if_tag_of_name_exist(name)) {
		return get_tag_id_by_name(name);
	}

	wstring sql = L"insert into tag(name) values('";
	sql.append(name).append(L"');");

	std::string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	// sqlite使用utf-8编码，汉字需要转
	string str_utf8_sql = ascii_2_utf8(str_sql);

	char* errmsg;
	if (sqlite3_exec(m_db, str_utf8_sql.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
		cout << "sqlite : insert data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return -1;
	}
	return get_last_insert_tag_id();
}

int CSqliteUtils::add_author_ret_id(std::wstring name) {
	using namespace std;

	if (check_if_author_of_name_exist(name)) {
		return get_author_id_by_name(name);
	}

	wstring sql = L"insert into author(name) values('";
	sql.append(name).append(L"');");

	std::string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	// sqlite使用utf-8编码，汉字需要转
	string str_utf8_sql = ascii_2_utf8(str_sql);

	char* errmsg;
	if (sqlite3_exec(m_db, str_utf8_sql.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
		cout << "sqlite : insert data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return -1;
	}
	return get_last_insert_author_id();
}

int CSqliteUtils::add_translator_ret_id(std::wstring name) {
	using namespace std;

	if (check_if_translator_of_name_exist(name)) {
		return get_translator_id_by_name(name);
	}

	wstring sql = L"insert into translator(name) values('";
	sql.append(name).append(L"');");

	std::string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	// sqlite使用utf-8编码，汉字需要转
	string str_utf8_sql = ascii_2_utf8(str_sql);

	char* errmsg;
	if (sqlite3_exec(m_db, str_utf8_sql.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
		cout << "sqlite : insert data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return -1;
	}
	return get_last_insert_translator_id();
}
int CSqliteUtils::add_tag_book_relation(std::wstring tag_id, std::wstring book_id) {
	using namespace std;

	wstring sql = L"insert into book_tag(tag_id,book_id) values(";
	sql.append(tag_id).append(L",").append(book_id).append(L");");

	std::string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	// sqlite使用utf-8编码，汉字需要转
	string str_utf8_sql = ascii_2_utf8(str_sql);

	char* errmsg;
	if (sqlite3_exec(m_db, str_utf8_sql.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
		cout << "sqlite : insert data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return -1;
	}
	return 0;
}
int CSqliteUtils::add_translator_book_relation(std::wstring translator_id, std::wstring book_id) {
	using namespace std;

	wstring sql = L"insert into book_translator(translator_id,book_id) values(";
	sql.append(translator_id).append(L",").append(book_id).append(L");");

	std::string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	// sqlite使用utf-8编码，汉字需要转
	string str_utf8_sql = ascii_2_utf8(str_sql);

	char* errmsg;
	if (sqlite3_exec(m_db, str_utf8_sql.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
		cout << "sqlite : insert data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return -1;
	}
	return 0;
}
int CSqliteUtils::add_author_book_relation(std::wstring author_id, std::wstring book_id) {
	using namespace std;

	wstring sql = L"insert into book_author(author_id,book_id) values(";
	sql.append(author_id).append(L",").append(book_id).append(L");");

	std::string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	// sqlite使用utf-8编码，汉字需要转
	string str_utf8_sql = ascii_2_utf8(str_sql);

	char* errmsg;
	if (sqlite3_exec(m_db, str_utf8_sql.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
		cout << "sqlite : insert data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return -1;
	}
	return 0;
}
int CSqliteUtils::add_publisher_ret_id(std::wstring name) {
	using namespace std;

	if (check_if_publisher_of_name_exist(name)) {
		return get_publisher_id_by_name(name);
	}

	wstring sql = L"insert into publisher(name) values('";
	sql.append(name).append(L"');");

	std::string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	// sqlite使用utf-8编码，汉字需要转
	string str_utf8_sql = ascii_2_utf8(str_sql);

	char* errmsg;
	if (sqlite3_exec(m_db, str_utf8_sql.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
		cout << "sqlite : insert data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return -1;
	}
	return get_last_insert_publisher_id();
}

int CSqliteUtils::add_book_review_ret_id(std::wstring name, std::wstring score,
	std::wstring publisher_id,std::wstring note,std::wstring page_num,std::wstring date,std::wstring pub_year) {
	using namespace std;

	wstring sql = L"insert into book(note,name,date,score,page_num,pub_year,publisher_id) values('";
	sql.append(note).append(L"','").append(name).append(L"','").append(date).append(L"',")
		.append(score).append(L",").append(page_num).append(L",").append(pub_year)
		.append(L",").append(publisher_id).append(L");");

	std::string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	// sqlite使用utf-8编码，汉字需要转
	string str_utf8_sql = ascii_2_utf8(str_sql);

	char* errmsg;
	if (sqlite3_exec(m_db, str_utf8_sql.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
		cout << "sqlite : insert data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return -1;
	}
	return get_last_insert_publisher_id();
}



bool CSqliteUtils::update_pro(CPro pro, std::wstring date) {
	using namespace std;
	wstring sql = L"update pro set writing_pro='";
	sql.append(pro.get_writing_pro_str()).append(L"',reading_pro='").append(pro.get_reading_pro_str()).append(L"',art_learning_pro='")
		.append(pro.get_art_learning_pro_str()).append(L"',computer_science_tech_pro='")
		.append(pro.get_computer_learning_pro_str()).append(L"',total_pro='").append(pro.get_total_pro_str()).append(L"',note='")
		.append(pro.get_note()).append(L"' where date='");
	sql.append(date);
	sql.append(L"';");

	string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	// sqlite使用utf-8编码，汉字需要转
	string str_utf8_sql = ascii_2_utf8(str_sql);

	char* errmsg;
	if (sqlite3_exec(m_db, str_utf8_sql.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
		cout << "sqlite : insert data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	return true;
}


bool CSqliteUtils::get_pro_sum_by_month(float* const writing_pro_sum, float* const reading_pro_sum,
	float* const art_learning_pro_sum, float* const computer_learning_pro_sum, float* const total_pro_sum, const int year, const int month) {
	using namespace std;
	char year_buf[15];
	char month_buf[15];
	if (month < 10)
	{
		month_buf[0] = '0';
		_itoa(month, month_buf+1, 10);
	}
	else
	{
		_itoa(month, month_buf, 10);
	}
	_itoa(year,year_buf,10);

	string sql = "select sum(writing_pro),sum(reading_pro),sum(art_learning_pro),sum(computer_science_tech_pro),sum(total_pro) from pro where strftime('%Y-%m',date)='";
	sql.append(year_buf).append("-").append(month_buf).append("';");

	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(m_db, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	int nIndex = nCol;
	if (pResult[nIndex] == NULL || strcmp(pResult[nIndex], "") == 0)
	{
		*writing_pro_sum = 0;
	}
	else 
	{
		*writing_pro_sum = static_cast<float>(atof(pResult[nIndex]));
	}
	if (pResult[nIndex+1] == NULL || strcmp(pResult[nIndex+1], "") == 0)
	{
		*reading_pro_sum = 0;
	}
	else
	{
		*reading_pro_sum = static_cast<float>(atof(pResult[nIndex + 1]));
	}
	if (pResult[nIndex + 2] == NULL || strcmp(pResult[nIndex + 2], "") == 0)
	{
		*art_learning_pro_sum = 0;
	}
	else 
	{
		*art_learning_pro_sum = static_cast<float>(atof(pResult[nIndex + 2]));
	}
	if (pResult[nIndex + 3] == NULL || strcmp(pResult[nIndex + 3], "") == 0)
	{
		*computer_learning_pro_sum = 0;
	}
	else
	{
		*computer_learning_pro_sum = static_cast<float>(atof(pResult[nIndex + 3]));
	}
	if (pResult[nIndex + 4] == NULL || strcmp(pResult[nIndex + 4], "") == 0)
	{
		*total_pro_sum = 0;
	}
	else
	{
		*total_pro_sum = static_cast<float>(atof(pResult[nIndex + 4]));
	}
	return true;
}


bool CSqliteUtils::get_pro_sum_by_year(float* const writing_pro_sum, float* const reading_pro_sum,
	float* const art_learning_pro_sum, float* const computer_learning_pro, float* const total_pro_sum, const int year) {
	using namespace std;
	char year_buf[15];
	_itoa(year, year_buf, 10);
	string sql = "select sum(writing_pro),sum(reading_pro),sum(art_learning_pro),sum(computer_science_tech_pro),sum(total_pro) from pro where strftime('%Y',date)='";
	sql.append(year_buf).append("';");

	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(m_db, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	int nIndex = nCol;
	if (pResult[nIndex] == NULL || strcmp(pResult[nIndex], "") == 0)
	{
		*writing_pro_sum = 0;
	}
	else
	{
		*writing_pro_sum = static_cast<float>(atof(pResult[nIndex]));
	}
	if (pResult[nIndex + 1] == NULL || strcmp(pResult[nIndex + 1], "") == 0)
	{
		*reading_pro_sum = 0;
	}
	else
	{
		*reading_pro_sum = static_cast<float>(atof(pResult[nIndex + 1]));
	}
	if (pResult[nIndex + 2] == NULL || strcmp(pResult[nIndex + 2], "") == 0)
	{
		*art_learning_pro_sum = 0;
	}
	else
	{
		*art_learning_pro_sum = static_cast<float>(atof(pResult[nIndex + 2]));
	}
	if (pResult[nIndex + 3] == NULL || strcmp(pResult[nIndex + 3], "") == 0)
	{
		*computer_learning_pro = 0;
	}
	else
	{
		*computer_learning_pro = static_cast<float>(atof(pResult[nIndex + 3]));
	}
	if (pResult[nIndex + 4] == NULL || strcmp(pResult[nIndex + 4], "") == 0)
	{
		*total_pro_sum = 0;
	}
	else
	{
		*total_pro_sum = static_cast<float>(atof(pResult[nIndex + 4]));
	}
	return true;
}


bool CSqliteUtils::get_pro_sum(float* const writing_pro_sum, float* const reading_pro_sum,
	float* const art_learning_pro_sum, float* const computer_learning_pro, float* const total_pro_sum) {
	using namespace std;
	string sql = "select sum(writing_pro),sum(reading_pro),sum(art_learning_pro),sum(computer_science_tech_pro),sum(total_pro) from pro;";

	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(m_db, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	int nIndex = nCol;
	if (pResult[nIndex] == NULL || strcmp(pResult[nIndex], "") == 0)
	{
		*writing_pro_sum = 0;
	}
	else
	{
		*writing_pro_sum = static_cast<float>(atof(pResult[nIndex]));
	}
	if (pResult[nIndex + 1] == NULL || strcmp(pResult[nIndex + 1], "") == 0)
	{
		*reading_pro_sum = 0;
	}
	else
	{
		*reading_pro_sum = static_cast<float>(atof(pResult[nIndex + 1]));
	}
	if (pResult[nIndex + 2] == NULL || strcmp(pResult[nIndex + 2], "") == 0)
	{
		*art_learning_pro_sum = 0;
	}
	else
	{
		*art_learning_pro_sum = static_cast<float>(atof(pResult[nIndex + 2]));
	}
	if (pResult[nIndex + 3] == NULL || strcmp(pResult[nIndex + 3], "") == 0)
	{
		*computer_learning_pro = 0;
	}
	else
	{
		*computer_learning_pro = static_cast<float>(atof(pResult[nIndex + 3]));
	}
	if (pResult[nIndex + 4] == NULL || strcmp(pResult[nIndex + 4], "") == 0)
	{
		*total_pro_sum = 0;
	}
	else
	{
		*total_pro_sum = static_cast<float>(atof(pResult[nIndex + 4]));
	}
	return true;
}


bool CSqliteUtils::check_if_pro_of_date_exist(std::wstring date) {
	using namespace std;
	wstring sql = L"select count(*) from pro where date='";
	sql.append(date);
	sql.append(L"';");
	std::string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(m_db, str_sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	int nIndex = nCol;
	if (atoi(pResult[nIndex]) > 0)
		return true;
	return false;
}


bool CSqliteUtils::get_pro(std::wstring date, CPro* pro) {
	using namespace std;
	wstring sql = L"select writing_pro,reading_pro,art_learning_pro,computer_science_tech_pro,note from pro where date='";
	sql.append(date).append(L"';");
	string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(m_db, str_sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	if (nRow == 0 || nCol == 0)
		return false;
	int nIndex = nCol;
	float writing_pro_num, reading_pro_num, art_learning_pro_num, computer_pro_num = 0.0;
	if (pResult[nIndex] == NULL || strcmp(pResult[nIndex], "") == 0)
	{
		writing_pro_num = 0;
	}
	else
	{
		writing_pro_num = static_cast<float>(atof(pResult[nIndex]));
	}
	if (pResult[nIndex + 1] == NULL || strcmp(pResult[nIndex + 1], "") == 0)
	{
		reading_pro_num = 0;
	}
	else
	{
		reading_pro_num = static_cast<float>(atof(pResult[nIndex + 1]));
	}
	if (pResult[nIndex + 2] == NULL || strcmp(pResult[nIndex + 2], "") == 0)
	{
		art_learning_pro_num = 0;
	}
	else
	{
		art_learning_pro_num = static_cast<float>(atof(pResult[nIndex + 2]));
	}
	if (pResult[nIndex + 3] == NULL || strcmp(pResult[nIndex + 3], "") == 0)
	{
		computer_pro_num = 0;
	}
	else
	{
		computer_pro_num = static_cast<float>(atof(pResult[nIndex + 3]));
	}
	string str_note;
	if (pResult[nIndex + 4] == NULL || strcmp(pResult[nIndex + 4], "") == 0)
	{
		str_note = "";
	}
	else
	{
		str_note = pResult[nIndex + 4];
		str_note = utf8_2_ascii(str_note);
	}
	wstring wstr_note;
	string_to_wstring(wstr_note, str_note);
	CPro new_pro(writing_pro_num, art_learning_pro_num,reading_pro_num, computer_pro_num,wstr_note);
	//浅拷贝即可
	*pro = new_pro;
	return true;
}


bool CSqliteUtils::count_pro_by_month(int* const num, const int year, const int month) {
	using namespace std;
	char year_buf[15];
	char month_buf[15];
	_itoa(year, year_buf, 10);
	if (month < 10)
	{
		month_buf[0] = '0';
		_itoa(month, month_buf + 1, 10);
	}
	else
	{
		_itoa(month, month_buf, 10);
	}
	string sql = "select count(*) from pro where strftime('%Y-%m',date)='";
	sql.append(year_buf).append("-").append(month_buf).append("';");

	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(m_db, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	int nIndex = nCol;
	if (pResult[nIndex] == NULL || strcmp(pResult[nIndex], "") == 0)
	{
		*num = 0;
	}
	else
	{
		*num = static_cast<float>(atoi(pResult[nIndex]));
	}
	return true;
}


bool CSqliteUtils::count_pro_by_year(int* const num, const int year) {
	using namespace std;
	char year_buf[15];
	_itoa(year, year_buf, 10);
	string sql = "select count(*) from pro where strftime('%Y',date)='";
	sql.append(year_buf).append("';");

	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(m_db, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	int nIndex = nCol;
	if (pResult[nIndex] == NULL || strcmp(pResult[nIndex], "") == 0)
	{
		*num = 0;
	}
	else
	{
		*num = static_cast<float>(atoi(pResult[nIndex]));
	}
	return true;
}


bool CSqliteUtils::count_pro(int* const num) {
	using namespace std;
	string sql = "select count(*) from pro;";

	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(m_db, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	int nIndex = nCol;
	if (pResult[nIndex] == NULL || strcmp(pResult[nIndex], "") == 0)
	{
		*num = 0;
	}
	else
	{
		*num = static_cast<float>(atoi(pResult[nIndex]));
	}
	return true;
}