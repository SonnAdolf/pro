#ifndef PRO_H
#define PRO_H

#include <QString>
#include"iostream"

class pro
{
public:
    pro();
    pro(float writing_pro, float art_learning_pro, float reading_pro, float computer_learning_pro, QString note);
    pro(QString writing_pro, QString art_learning_pro, QString reading_pro, QString computer_pro, QString note);
    float get_writing_pro();
    float get_art_learning_pro();
    float get_reading_pro();
    float get_total_pro();
    float get_computer_learning_pro();
    QString get_writing_pro_str();
    QString get_art_learning_pro_str();
    QString get_reading_pro_str();
    QString get_total_pro_str();
    QString get_computer_learning_pro_str();
    QString get_note();
private:
    float m_writing_pro;
    float m_art_learning_pro;
    float m_reading_pro;
    float m_total_pro;
    float m_computer_learning_pro;
    QString m_note;
};

#endif // PRO_H
