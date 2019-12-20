#pragma once
#include <windows.h>
#include <string>
#include <time.h>
#include <iostream>
#include <vector>

void wchar_to_string(std::string& src_dst, const wchar_t* dst_wchar);


void string_to_wstring(std::wstring& szDst, const std::string str);

std::string utf8_2_ascii(std::string& strUtf8Code);

std::string ascii_2_utf8(std::string& strAsciiCode);