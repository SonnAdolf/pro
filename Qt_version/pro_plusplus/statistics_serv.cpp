#include "statistics_serv.h"

QString statistics_serv::get_statistics_inf()
{
    QString statistics_inf_str = "";

    QDate qdate;
    int this_year = qdate.currentDate().year();
    int this_month = qdate.currentDate().month();

    int month_num;

    int i, j = 0;
    float tmp_writing_pro_sum, tmp_reading_pro_sum,
        tmp_art_learning_pro_sum, tmp_computer_learning_pro_sum, tmp_total_pro_sum = 0;

    QString strtemp="";
    float day_num = 0.00;
    int tmp_day_num = 0;
    float average_w_pro, average_r_pro, average_a_pro, average_c_pro, average_t_pro = 0.00;

    //从2019年12月开始统计
    for (i = 2019; i <= this_year; i++)
    {
        month_num = 12;
        if (i == this_year)
        {
            month_num = this_month;
        }

        j = 1;
        if (i == 2019)
            j = 12;

        //每月统计
        for (; j <= month_num; j++)
        {
            strtemp = QString("%1").arg(j);
            statistics_inf_str.append(strtemp).append("月:  ");
            sqlite_utils::get_inst().get_pro_sum_by_month(&tmp_writing_pro_sum, &tmp_reading_pro_sum, &tmp_art_learning_pro_sum, &tmp_computer_learning_pro_sum, &tmp_total_pro_sum, i, j);
            strtemp = QString("%1").arg(tmp_writing_pro_sum);
            statistics_inf_str.append("寫作用時:").append(strtemp).append("   ").append("閲讀調研用時:");
            strtemp = QString("%1").arg(tmp_reading_pro_sum);
            statistics_inf_str.append(strtemp).append("   ").append("藝術學習用時:");
            strtemp = QString("%1").arg(tmp_art_learning_pro_sum);
            statistics_inf_str.append(strtemp).append("   ").append("計算機科學技術研習用時:");
            strtemp = QString("%1").arg(tmp_computer_learning_pro_sum);
            statistics_inf_str.append(strtemp).append("   ").append("縂用時:");
            strtemp = QString("%1").arg(tmp_total_pro_sum);
            statistics_inf_str.append(strtemp);

            sqlite_utils::get_inst().count_pro_by_month(&tmp_day_num, i, j);
            day_num = tmp_day_num;
            average_t_pro = tmp_total_pro_sum / day_num;
            average_w_pro = tmp_writing_pro_sum / day_num;
            average_a_pro = tmp_art_learning_pro_sum / day_num;
            average_c_pro = tmp_computer_learning_pro_sum / day_num;
            average_r_pro = tmp_reading_pro_sum / day_num;
            strtemp = QString("%1").arg(average_w_pro);
            statistics_inf_str.append("   ").append("平均值(寫-讀-藝-技-总):").append(strtemp).append("-");
            strtemp = QString("%1").arg(average_r_pro);
            statistics_inf_str.append(strtemp).append("-");
            strtemp = QString("%1").arg(average_a_pro);
            statistics_inf_str.append(strtemp).append("-");
            strtemp = QString("%1").arg(average_c_pro);
            statistics_inf_str.append(strtemp).append("-");
            strtemp = QString("%1").arg(average_t_pro);
            statistics_inf_str.append(strtemp).append("\r\n");;
        }
        //每年统计
        statistics_inf_str.append("----------------------\r\n");
        strtemp = QString("%1").arg(i);
        statistics_inf_str.append(strtemp).append("年:");
        sqlite_utils::get_inst().get_pro_sum_by_year(&tmp_writing_pro_sum, &tmp_reading_pro_sum, &tmp_art_learning_pro_sum, &tmp_computer_learning_pro_sum, &tmp_total_pro_sum, i);
        strtemp = QString("%1").arg(tmp_writing_pro_sum);
        statistics_inf_str.append("寫作用時:").append(strtemp).append("   ").append("閲讀調研用時:");
        strtemp = QString("%1").arg(tmp_reading_pro_sum);
        statistics_inf_str.append(strtemp).append("   ").append("藝術學習用時:");
        strtemp = QString("%1").arg(tmp_art_learning_pro_sum);
        statistics_inf_str.append(strtemp).append("   ").append("計算機科學技術研習用時:");
        strtemp = QString("%1").arg(tmp_computer_learning_pro_sum);
        statistics_inf_str.append(strtemp).append("   ").append("縂用時:");
        strtemp = QString("%1").arg(tmp_total_pro_sum);
        statistics_inf_str.append(strtemp);

        sqlite_utils::get_inst().count_pro_by_year(&tmp_day_num, i);
        day_num = tmp_day_num;
        average_t_pro = tmp_total_pro_sum / day_num;
        average_w_pro = tmp_writing_pro_sum / day_num;
        average_a_pro = tmp_art_learning_pro_sum / day_num;
        average_c_pro = tmp_computer_learning_pro_sum / day_num;
        average_r_pro = tmp_reading_pro_sum / day_num;
        strtemp = QString("%1").arg(average_w_pro);
        statistics_inf_str.append("   ").append("平均值(寫-讀-藝-技-总):").append(strtemp).append("-");
        strtemp = QString("%1").arg(average_r_pro);
        statistics_inf_str.append(strtemp).append("-");
        strtemp = QString("%1").arg(average_a_pro);
        statistics_inf_str.append(strtemp).append("-");
        strtemp = QString("%1").arg(average_c_pro);
        statistics_inf_str.append(strtemp).append("-");
        strtemp = QString("%1").arg(average_t_pro);
        statistics_inf_str.append(strtemp).append("\r\n");;

        statistics_inf_str.append("----------------------\r\n\r\n");
    }
    //总计
    statistics_inf_str.append("總計:");
    sqlite_utils::get_inst().get_pro_sum(&tmp_writing_pro_sum, &tmp_reading_pro_sum, &tmp_art_learning_pro_sum, &tmp_computer_learning_pro_sum, &tmp_total_pro_sum);
    strtemp = QString("%1").arg(tmp_writing_pro_sum);
    statistics_inf_str.append("寫作用時:").append(strtemp).append("   ").append("閲讀調研用時:");
    strtemp = QString("%1").arg(tmp_reading_pro_sum);
    statistics_inf_str.append(strtemp).append("   ").append("藝術學習用時:");
    strtemp = QString("%1").arg(tmp_art_learning_pro_sum);
    statistics_inf_str.append(strtemp).append("   ").append("計算機科學技術研習用時:");
    strtemp = QString("%1").arg(tmp_computer_learning_pro_sum);
    statistics_inf_str.append(strtemp).append("   ").append("縂用時:");
    strtemp = QString("%1").arg(tmp_total_pro_sum);
    statistics_inf_str.append(strtemp);

    sqlite_utils::get_inst().count_pro(&tmp_day_num);
    day_num = tmp_day_num;
    average_t_pro = tmp_total_pro_sum / day_num;
    average_w_pro = tmp_writing_pro_sum / day_num;
    average_a_pro = tmp_art_learning_pro_sum / day_num;
    average_c_pro = tmp_computer_learning_pro_sum / day_num;
    average_r_pro = tmp_reading_pro_sum / day_num;
    strtemp = QString("%1").arg(average_w_pro);
    statistics_inf_str.append("   ").append("平均值(寫-讀-藝-技-总):").append(strtemp).append("-");
    strtemp = QString("%1").arg(average_r_pro);
    statistics_inf_str.append(strtemp).append("-");
    strtemp = QString("%1").arg(average_a_pro);
    statistics_inf_str.append(strtemp).append("-");
    strtemp = QString("%1").arg(average_c_pro);
    statistics_inf_str.append(strtemp).append("-");
    strtemp = QString("%1").arg(average_t_pro);
    statistics_inf_str.append(strtemp);

    return statistics_inf_str;
}
