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


bool CSqliteUtils::add_pro(CPro pro, std::wstring date)  const {
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

bool CSqliteUtils::check_if_tag_of_name_exist(const std::wstring& name) const {
	using namespace std;
	wstring sql = L"select count(*) from tag where name='";
	sql.append(name);
	sql.append(L"';");
	std::string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	// sqlite使用utf-8编码，汉字需要转
	string str_utf8_sql = ascii_2_utf8(str_sql);
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(m_db, str_utf8_sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
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

bool CSqliteUtils::check_if_author_of_name_exist(const std::wstring& name) const {
	using namespace std;
	wstring sql = L"select count(*) from author where name='";
	sql.append(name);
	sql.append(L"';");
	std::string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	// sqlite使用utf-8编码，汉字需要转
	string str_utf8_sql = ascii_2_utf8(str_sql);
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(m_db, str_utf8_sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	int nIndex = nCol;
	if (atoi(pResult[nIndex]) > 0)
		return true;
	return false;
}

bool CSqliteUtils::check_if_translator_of_name_exist(const std::wstring& name) const {
	using namespace std;
	wstring sql = L"select count(*) from translator where name='";
	sql.append(name);
	sql.append(L"';");
	std::string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	// sqlite使用utf-8编码，汉字需要转
	string str_utf8_sql = ascii_2_utf8(str_sql);
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(m_db, str_utf8_sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	int nIndex = nCol;
	if (atoi(pResult[nIndex]) > 0)
		return true;
	return false;
}

bool CSqliteUtils::check_if_publisher_of_name_exist(const std::wstring& name) const {
	using namespace std;
	wstring sql = L"select count(*) from publisher where name='";
	sql.append(name);
	sql.append(L"';");
	std::string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	// sqlite使用utf-8编码，汉字需要转
	string str_utf8_sql = ascii_2_utf8(str_sql);
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(m_db, str_utf8_sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	int nIndex = nCol;
	if (atoi(pResult[nIndex]) > 0)
		return true;
	return false;
}

int CSqliteUtils::get_tag_id_by_name(const std::wstring& name) const {
	using namespace std;
	wstring sql = L"select id from tag where name = '";
	sql.append(name).append(L"';");
	string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	// sqlite使用utf-8编码，汉字需要转
	string str_utf8_sql = ascii_2_utf8(str_sql);
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(m_db, str_utf8_sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
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

int CSqliteUtils::get_author_id_by_name(const std::wstring& name) const {
	using namespace std;
	wstring sql = L"select id from author where name = '";
	sql.append(name).append(L"';");
	string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	// sqlite使用utf-8编码，汉字需要转
	string str_utf8_sql = ascii_2_utf8(str_sql);
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(m_db, str_utf8_sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
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

int CSqliteUtils::get_translator_id_by_name(const std::wstring& name) const {
	using namespace std;
	wstring sql = L"select id from translator where name = '";
	sql.append(name).append(L"';");
	string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	// sqlite使用utf-8编码，汉字需要转
	string str_utf8_sql = ascii_2_utf8(str_sql);
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(m_db, str_utf8_sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
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

int CSqliteUtils::get_publisher_id_by_name(const std::wstring& name) const {
	using namespace std;
	wstring sql = L"select id from publisher where name = '";
	sql.append(name).append(L"';");
	string str_sql;
	wchar_to_string(str_sql, sql.c_str());
	// sqlite使用utf-8编码，汉字需要转
	string str_utf8_sql = ascii_2_utf8(str_sql);
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(m_db, str_utf8_sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
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

int CSqliteUtils::get_last_insert_tag_id() const {
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

int CSqliteUtils::get_last_insert_book_id() const {
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

int CSqliteUtils::get_last_insert_author_id() const {
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

int CSqliteUtils::get_last_insert_translator_id() const {
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

int CSqliteUtils::get_last_insert_publisher_id() const {
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

int CSqliteUtils::add_tag_ret_id(const std::wstring&  name)  const {
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

int CSqliteUtils::add_author_ret_id(const std::wstring& name) const {
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

int CSqliteUtils::add_translator_ret_id(const std::wstring& name) const {
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
int CSqliteUtils::add_tag_book_relation(const std::wstring& tag_id, const std::wstring& book_id) const {
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
int CSqliteUtils::add_translator_book_relation(const std::wstring& translator_id, const std::wstring& book_id) const {
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
int CSqliteUtils::add_author_book_relation(const std::wstring& author_id, const std::wstring& book_id) const {
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
int CSqliteUtils::add_publisher_ret_id(const std::wstring& name) const {
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

int CSqliteUtils::add_book_review_ret_id(const std::wstring& name, const std::wstring& score,
	const std::wstring& publisher_id,const std::wstring& note,const std::wstring& page_num,const std::wstring& date,const std::wstring& pub_year) const {
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



bool CSqliteUtils::update_pro(CPro pro, const std::wstring& date) const {
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
	float* const art_learning_pro_sum, float* const computer_learning_pro_sum, float* const total_pro_sum, const int year, const int month) const {
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
	float* const art_learning_pro_sum, float* const computer_learning_pro, float* const total_pro_sum, const int year) const {
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
	float* const art_learning_pro_sum, float* const computer_learning_pro, float* const total_pro_sum) const {
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


bool CSqliteUtils::check_if_pro_of_date_exist(const std::wstring& date) const {
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

bool CSqliteUtils::set_book_reviews_of_publisher(std::list<CBook>& book_reviews) const {
	using namespace std;
	std::list<CBook>::iterator book_review_inter;
	for (book_review_inter = book_reviews.begin(); book_review_inter != book_reviews.end(); book_review_inter++)
	{
		wstring sql = L"select p.name from publisher p join book b on (b.id=";
		sql += book_review_inter->get_id();
		sql += L" and b.publisher_id=p.id);";
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
		std::wstring tmp_wstring;
		std::string tmp_str;
		if (pResult[nIndex] != NULL && strcmp(pResult[nIndex], "") != 0)
		{
			tmp_str = pResult[nIndex];
			string_to_wstring(tmp_wstring, utf8_2_ascii(tmp_str));
			book_review_inter->set_publisher(tmp_wstring);
		}
	}
	return true;
}
bool CSqliteUtils::get_pro(const std::wstring& date, CPro* pro) const {
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
bool CSqliteUtils::set_book_reviews_of_authors(std::list<CBook>& book_reviews) const {
	using namespace std;
	std::list<CBook>::iterator book_review_inter;
	for (book_review_inter = book_reviews.begin(); book_review_inter != book_reviews.end(); book_review_inter++)
	{
		wstring sql = L"select a.name from author a join book_author b_a on (b_a.book_id=";
		sql += book_review_inter->get_id();
		sql += L" and a.id=b_a.author_id);";
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
		std::wstring tmp_wstring;
		std::string tmp_str;
		std::vector<std::wstring> authors;
		for (int i = 0; i < nRow; i++)
		{
			if (pResult[nIndex] != NULL && strcmp(pResult[nIndex], "") != 0)
			{
				tmp_str = pResult[nIndex];
				string_to_wstring(tmp_wstring, utf8_2_ascii(tmp_str));
				authors.push_back(tmp_wstring);
			}
			nIndex += nCol;
		}
		book_review_inter->set_authors(authors);
	}
	return true;
}
bool CSqliteUtils::set_book_reviews_of_translators(std::list<CBook>& book_reviews) const {
	using namespace std;
	std::list<CBook>::iterator book_review_inter;
	for (book_review_inter = book_reviews.begin(); book_review_inter != book_reviews.end(); book_review_inter++)
	{
		wstring sql = L"select t.name from translator t join book_translator b_t on (b_t.book_id=";
		sql += book_review_inter->get_id();
		sql += L" and b_t.translator_id = t.id);";
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
			return true;
		int nIndex = nCol;
		std::wstring tmp_wstring;
		std::string tmp_str;
		std::vector<std::wstring> translators;
		for (int i = 0; i < nRow; i++)
		{
			if (pResult[nIndex] != NULL && strcmp(pResult[nIndex], "") != 0)
			{
				tmp_str = pResult[nIndex];
				string_to_wstring(tmp_wstring, utf8_2_ascii(tmp_str));
				translators.push_back(tmp_wstring);
			}
			nIndex += nCol;
		}
		book_review_inter->set_translators(translators);
	}
	return true;
}
bool CSqliteUtils::get_book_reviews(std::list<CBook>& book_reviews) const {
	using namespace std;
	const wstring sql = L"select id,note,name,date,score,page_num,pub_year,publisher_id from book;";
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
	std::wstring tmp_wstring;
	std::string tmp_str;
	for (int i = 0; i < nRow; i++)
	{
		CBook tmp_book;
		if (pResult[nIndex] == NULL || strcmp(pResult[nIndex], "") == 0)
		{
			tmp_book.set_id(L"0");
		}
		else
		{
			tmp_str = pResult[nIndex];
			string_to_wstring(tmp_wstring, utf8_2_ascii(tmp_str));
			tmp_book.set_id(tmp_wstring);
		}
		if (pResult[nIndex+1] == NULL || strcmp(pResult[nIndex+1], "") == 0)
		{
			tmp_book.set_note(L"");
		}
		else
		{
			tmp_str = pResult[nIndex+1];
			string_to_wstring(tmp_wstring, utf8_2_ascii(tmp_str));
			tmp_book.set_note(tmp_wstring);
		}
		if (pResult[nIndex + 2] == NULL || strcmp(pResult[nIndex + 2], "") == 0)
		{
			tmp_book.set_name(L"");
		}
		else
		{
			tmp_str = pResult[nIndex+2];
			string_to_wstring(tmp_wstring, utf8_2_ascii(tmp_str));
			tmp_book.set_name(tmp_wstring);
		}
		if (pResult[nIndex + 3] == NULL || strcmp(pResult[nIndex + 3], "") == 0)
		{
			tmp_book.set_review_date(L"");
		}
		else
		{
			tmp_str = pResult[nIndex+3];
			string_to_wstring(tmp_wstring, utf8_2_ascii(tmp_str));
			tmp_book.set_review_date(tmp_wstring);
		}
		if (pResult[nIndex + 4] == NULL || strcmp(pResult[nIndex + 4], "") == 0)
		{
			tmp_book.set_score(L"");
		}
		else
		{
			tmp_str = pResult[nIndex+4];
			string_to_wstring(tmp_wstring, utf8_2_ascii(tmp_str));
			tmp_book.set_score(tmp_wstring);
		}
		if (pResult[nIndex + 5] == NULL || strcmp(pResult[nIndex + 5], "") == 0)
		{
			tmp_book.set_page_num(L"");
		}
		else
		{
			tmp_str = pResult[nIndex+5];
			string_to_wstring(tmp_wstring, utf8_2_ascii(tmp_str));
			tmp_book.set_page_num(tmp_wstring);
		}
		if (pResult[nIndex + 6] == NULL || strcmp(pResult[nIndex + 6], "") == 0)
		{
			tmp_book.set_pub_year(L"");
		}
		else
		{
			tmp_str = pResult[nIndex+6];
			string_to_wstring(tmp_wstring, utf8_2_ascii(tmp_str));
			tmp_book.set_pub_year(tmp_wstring);
		}
		nIndex += nCol;
		book_reviews.push_back(tmp_book);
	}
	if (!set_book_reviews_of_authors(book_reviews))
		return false;
	if (!set_book_reviews_of_translators(book_reviews))
		return false;
	if (!set_book_reviews_of_publisher(book_reviews))
		return false;
	return true;
}


bool CSqliteUtils::count_pro_by_month(int* const num, const int year, const int month) const {
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


bool CSqliteUtils::count_pro_by_year(int* const num, const int year)  const {
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


bool CSqliteUtils::count_pro(int* const num)  const {
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