#include "pro.h"

pro::pro()
{

}

pro::pro(float writing_pro, float art_learning_pro, float reading_pro, float computer_learning_pro, QString note)
{
    this->m_art_learning_pro = art_learning_pro;
    this->m_reading_pro = reading_pro;
    this->m_writing_pro = writing_pro;
    this->m_computer_learning_pro = computer_learning_pro;
    this->m_total_pro = art_learning_pro + reading_pro + writing_pro + computer_learning_pro;
    this->m_note = note;

}

pro::pro(QString writing_pro, QString art_learning_pro, QString reading_pro, QString computer_pro, QString note)
{
    if (writing_pro.compare("")==0||writing_pro==NULL)
    {
        writing_pro = "0";
    }
    if (art_learning_pro.compare("")==0||art_learning_pro==NULL)
    {
        art_learning_pro = "0";
    }
    if (reading_pro.compare("")==0||reading_pro==NULL)
    {
        reading_pro = "0";
    }
    if (computer_pro.compare("")==0||computer_pro==NULL)
    {
        computer_pro = "0";
    }
    this->m_art_learning_pro = art_learning_pro.toFloat();
    this->m_reading_pro = reading_pro.toFloat();
    this->m_writing_pro = writing_pro.toFloat();
    this->m_computer_learning_pro = computer_pro.toFloat();
    this->m_total_pro = m_art_learning_pro + m_reading_pro + m_writing_pro + m_computer_learning_pro;
    this->m_note = note;
}

float pro::get_writing_pro()
{
    return m_writing_pro;
}

float pro::get_art_learning_pro()
{
    return m_art_learning_pro;
}

float pro::get_reading_pro()
{
    return m_reading_pro;
}

float pro::get_computer_learning_pro()
{
    return m_computer_learning_pro;
}

float pro::get_total_pro()
{
    return m_total_pro;
}

QString pro::get_writing_pro_str()
{
    QString str = QString("%1").arg(m_writing_pro);
    return str;
}

QString pro::get_art_learning_pro_str()
{
    QString str = QString("%1").arg(m_art_learning_pro);
    return str;
}

QString pro::get_reading_pro_str()
{
    QString str = QString("%1").arg(m_reading_pro);
    return str;
}

QString pro::get_computer_learning_pro_str()
{
    QString str = QString("%1").arg(m_computer_learning_pro);
    return str;
}

QString pro::get_total_pro_str()
{
    QString str = QString("%1").arg(m_total_pro);
    return str;
}

QString pro::get_note()
{
    return m_note;
}
