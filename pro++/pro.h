#pragma once
#include "pro.h"
#include <string>

class CPro
{
public:
	CPro();
	CPro(float writing_pro, float art_learning_pro, float reading_pro, std::wstring note);
	CPro(std::wstring writing_pro, std::wstring art_learning_pro, std::wstring reading_pro, std::wstring note);
	float get_writing_pro();
	float get_art_learning_pro();
	float get_reading_pro();
	float get_total_pro();
	std::wstring  get_writing_pro_str();
	std::wstring  get_art_learning_pro_str();
	std::wstring  get_reading_pro_str();
	std::wstring  get_total_pro_str();
	std::wstring get_note();
private:
	float m_writing_pro;
	float m_art_learning_pro;
	float m_reading_pro;
	float m_total_pro;
	std::wstring m_writing_pro_str;
	std::wstring m_art_learning_pro_str;
	std::wstring m_reading_pro_str;
	std::wstring m_total_pro_str;
	std::wstring m_note;
};
