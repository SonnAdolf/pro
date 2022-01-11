#include "str_utils.h"

/**
* 作      者:	无名
* 功      能:  wchar_t to string
*/
void wchar_to_string(std::string& src_dst, const wchar_t* dst_wchar) {
	const wchar_t* wText = dst_wchar;
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);
	char* psText;
	psText = new char[dwNum];
	WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);
	src_dst = psText;
	delete[]psText;
}


// string to wstring  
void string_to_wstring(std::wstring& szDst, const std::string str) {
	unsigned int len = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)str.c_str(), -1, NULL, 0);
	wchar_t* wsz_utf8 = new wchar_t[len + 1];
	memset(wsz_utf8, 0, len * 2 + 2);
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)str.c_str(), -1, (LPWSTR)wsz_utf8, len);
	szDst = wsz_utf8;
	delete[] wsz_utf8;
}


//UTF-8转Unicode 
std::wstring Utf82Unicode(const std::string& utf8string)
{
	int widesize = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, NULL, 0);
	if (widesize == ERROR_NO_UNICODE_TRANSLATION)
	{
		throw std::exception("Invalid UTF-8 sequence.");
	}
	if (widesize == 0)
	{
		throw std::exception("Error in conversion.");
	}
	std::vector<wchar_t> resultstring(widesize);
	int convresult = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, &resultstring[0], widesize);
	if (convresult != widesize)
	{
		throw std::exception("La falla!");
	}
	return std::wstring(&resultstring[0]);
}


//unicode 转为 ascii 
std::string WideByte2Acsi(std::wstring& wstrcode)
{
	int asciisize = ::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, NULL, 0, NULL, NULL);
	if (asciisize == ERROR_NO_UNICODE_TRANSLATION)
	{
		throw std::exception("Invalid UTF-8 sequence.");
	}
	if (asciisize == 0)
	{
		throw std::exception("Error in conversion.");
	}
	std::vector<char> resultstring(asciisize);
	int convresult = ::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, &resultstring[0], asciisize, NULL, NULL);
	if (convresult != asciisize)
	{
		throw std::exception("La falla!");
	}
	return std::string(&resultstring[0]);
}



//utf-8 转 ascii 
std::string utf8_2_ascii(std::string& strUtf8Code)
{
	using namespace std;
	string strRet = "";
	//先把 utf8 转为 unicode 
	wstring wstr = Utf82Unicode(strUtf8Code);
	//最后把 unicode 转为 ascii 
	strRet = WideByte2Acsi(wstr);
	return strRet;
}



//ascii 转 Unicode 
std::wstring Acsi2WideByte(std::string& strascii)
{
	using namespace std;
	int widesize = MultiByteToWideChar(CP_ACP, 0, (char*)strascii.c_str(), -1, NULL, 0);
	if (widesize == ERROR_NO_UNICODE_TRANSLATION)
	{
		throw std::exception("Invalid UTF-8 sequence.");
	}
	if (widesize == 0)
	{
		throw std::exception("Error in conversion.");
	}
	std::vector<wchar_t> resultstring(widesize);
	int convresult = MultiByteToWideChar(CP_ACP, 0, (char*)strascii.c_str(), -1, &resultstring[0], widesize);
	if (convresult != widesize)
	{
		throw std::exception("La falla!");
	}
	return std::wstring(&resultstring[0]);
}


//Unicode 转 Utf8 
std::string Unicode2Utf8(const std::wstring& widestring)
{
	using namespace std;
	int utf8size = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, NULL, 0, NULL, NULL);
	if (utf8size == 0)
	{
		throw std::exception("Error in conversion.");
	}
	std::vector<char> resultstring(utf8size);
	int convresult = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, &resultstring[0], utf8size, NULL, NULL);
	if (convresult != utf8size)
	{
		throw std::exception("La falla!");
	}
	return std::string(&resultstring[0]);
}

//ascii 转 Utf8 
std::string ascii_2_utf8(std::string& strAsciiCode) {
	using namespace std;
	string strRet("");
	//先把 ascii 转为 unicode 
	wstring wstr = Acsi2WideByte(strAsciiCode);
	//最后把 unicode 转为 utf8 
	strRet = Unicode2Utf8(wstr);
	return strRet;
}

std::vector<std::wstring> split(const std::wstring& s, const std::wstring& delim) {
	std::vector<std::wstring> elems;
	size_t pos = 0;
	size_t len = s.length();
	size_t delim_len = delim.length();
	while (pos < len) {
		int find_pos = s.find(delim, pos);
		if (find_pos < 0) {
			elems.push_back(s.substr(pos, len - pos));
			break;
		}
		elems.push_back(s.substr(pos, find_pos - pos));
		pos = find_pos + delim_len;
	}
	return elems;
}