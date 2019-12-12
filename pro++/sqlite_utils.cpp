//
//  sqlite���ݿ�ʹ�ú���
//

#include "sqlite_utils.h"

sqlite3* pDB = NULL;

/*
 *  author: ����
 *  date  : 2018-08-07
 *  note  : close sqlite connection
 */
int sqliteClose() {
	sqlite3_close(pDB);
	return 0;
}


/*
*  author: ����
*  date  : 2018-08-07
*  note  : connect to sqlite
*/
int sqliteConn() {
	int nRes = sqlite3_open("data.db", &pDB);
	if (nRes != SQLITE_OK)
		return -1;
	return 0;
}


