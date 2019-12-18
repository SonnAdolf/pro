#include "pro.h"

CPro::CPro(float writing_pro, float art_learning_pro, float reading_pro, std::wstring note)
{
	this->m_art_learning_pro = art_learning_pro;
	this->m_reading_pro = reading_pro;
	this->m_writing_pro = writing_pro;
	this->m_total_pro = art_learning_pro + reading_pro + writing_pro;
	this->m_note = note;
	wchar_t buf[6];
	swprintf(buf, L"%.2f", this->m_writing_pro);
	this->m_writing_pro_str = buf;
	swprintf(buf, L"%.2f", this->m_reading_pro);
	this->m_reading_pro_str = buf;
	swprintf(buf, L"%.2f", this->m_art_learning_pro);
	this->m_art_learning_pro_str = buf;
	swprintf(buf, L"%.2f", this->m_total_pro);
	this->m_total_pro_str = buf;

}

CPro::CPro(std::wstring writing_pro, std::wstring art_learning_pro, std::wstring reading_pro, std::wstring note)
{
	this->m_art_learning_pro_str = art_learning_pro;
	this->m_reading_pro_str = reading_pro;
	this->m_writing_pro_str = writing_pro;

	this->m_art_learning_pro = static_cast<float>(_wtof(art_learning_pro.c_str()));
	this->m_reading_pro = static_cast<float>(_wtof(reading_pro.c_str()));
	this->m_writing_pro = static_cast<float>(_wtof(writing_pro.c_str()));
	this->m_total_pro = m_art_learning_pro + m_reading_pro + m_writing_pro;

	wchar_t total_num_buf[6];
	swprintf(total_num_buf, L"%.2f", this->m_total_pro);
	this->m_total_pro_str = total_num_buf;
	this->m_note = note;
}

float CPro::get_writing_pro()
{
	return m_writing_pro;
}

float CPro::get_art_learning_pro()
{
	return m_art_learning_pro;
}

float CPro::get_reading_pro()
{
	return m_reading_pro;
}

float CPro::get_total_pro()
{
	return m_total_pro;
}

std::wstring CPro::get_writing_pro_str()
{
	return m_writing_pro_str;
}

std::wstring CPro::get_art_learning_pro_str()
{
	return m_art_learning_pro_str;
}

std::wstring CPro::get_reading_pro_str()
{
	return m_reading_pro_str;
}

std::wstring CPro::get_total_pro_str()
{
	return m_total_pro_str;
}

std::wstring CPro::get_note()
{
	return m_note;
}
