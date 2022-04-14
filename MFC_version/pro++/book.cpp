#include "book.h"

CBook::CBook():m_id(L"0"), m_review_date(L""), m_publisher(L""),m_note(L"")
,m_date(L""),m_page_num(L"0"),m_pub_year(L""),m_score(L"")
{

}
CBook::CBook(std::wstring id,std::wstring note, std::wstring name,std::wstring date, std::wstring page_num,
    std::wstring score, std::wstring pub_year, std::wstring review_date, std::wstring publisher,
    std::vector<std::wstring> translators, std::vector<std::wstring> tags,
    std::vector<std::wstring> authors)
{

}