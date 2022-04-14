#pragma once
#include <vector>
#include <iostream>
class CBook
{
public:
    CBook();
    CBook(std::wstring id,std::wstring note,std::wstring name,std::wstring date, std::wstring page_num,
        std::wstring score, std::wstring pub_year,std::wstring review_date,std::wstring publisher,
        std::vector<std::wstring> translators,std::vector<std::wstring> tags,
        std::vector<std::wstring> authors);
    void set_id(const std::wstring& inpt_id) { this->m_id = inpt_id; }
    void set_note(const std::wstring& inpt_note) { this->m_note = inpt_note; }
    void set_name(const std::wstring& inpt_name) { this->m_name = inpt_name; }
    void set_date(const std::wstring& inpt_date) { this->m_date = inpt_date; }
    void set_page_num(const std::wstring& inpt_page_num) { this->m_page_num = inpt_page_num; }
    void set_score(const std::wstring& inpt_score) { this->m_score = inpt_score; }
    void set_pub_year(const std::wstring& inpt_pub_year) { this->m_pub_year = inpt_pub_year; }
    void set_review_date(const std::wstring& inpt_review_date) { this->m_review_date = inpt_review_date; }
    void set_publisher(const std::wstring& inpt_publisher) { this->m_publisher = inpt_publisher; }
    void set_translators(const std::vector<std::wstring>& inpt_translators) { this->m_translators = inpt_translators; }
    void set_tags(const std::vector<std::wstring>& inpt_tags) { this->m_tags = inpt_tags; }
    void set_authors(const std::vector<std::wstring>& inpt_authors) { this->m_authors = inpt_authors; }

    std::wstring get_id() { return this->m_id; }
    std::wstring get_note() { return this->m_note; }
    std::wstring get_name() { return this->m_name; }
    std::wstring get_date() { return this->m_date; }
    std::wstring get_page_num() { return this->m_page_num; }
    std::wstring get_score() { return this->m_score; }
    std::wstring get_pub_year() { return this->m_pub_year; }
    std::wstring get_review_date() { return this->m_review_date; }
    std::wstring get_publisher() { return this->m_publisher; }
    std::vector<std::wstring> get_translators() { return this->m_translators; }
    std::vector<std::wstring> get_tags() { return this->m_tags; }
    std::vector<std::wstring> get_authors() { return this->m_authors; }
private:
    std::wstring m_id;
    std::wstring m_review_date;
    std::wstring m_publisher;
    std::wstring m_note;
    std::wstring m_name;
    std::wstring m_date;
    std::wstring m_page_num;
    std::wstring m_score;
    std::wstring m_pub_year;
    std::vector<std::wstring> m_translators;
    std::vector<std::wstring> m_tags;
    std::vector<std::wstring> m_authors;
};
