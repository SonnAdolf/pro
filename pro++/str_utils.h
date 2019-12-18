#pragma once
#include <windows.h>
#include <string>
#include <time.h>
#include <iostream>
#include <vector>

void wchar_to_string(std::string& src_dst, const wchar_t* dst_wchar);

std::string ascii_2_utf8(std::string& strAsciiCode);