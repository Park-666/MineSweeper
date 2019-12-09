/******************
 版本号：v1.0
 作  者：唐攀
 日  期：2019-12-1
******************/

#ifndef HERODIALOG_H
#define HERODIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QGraphicsView>
#include <QSettings>
#include <QString>


class HeroDialog : public QDialog
{
    Q_OBJECT
public:
    HeroDialog(QDialog *parent = 0);

    QLabel *junior_label;          //初级label
    QLabel *intermediate_label;    //中级label
    QLabel *advanced_label;        //高级label

    QLabel *jun_time_label;        //初级纪录时间
    QLabel *int_time_label;        //中级纪录时间
    QLabel *adv_time_label;        //高级纪录时间

    QLabel *jun_name_label;        //初级纪录姓名
    QLabel *int_name_label;        //中级纪录姓名
    QLabel *adv_name_label;        //高级纪录姓名

    /****************
     功  能：读英雄榜数据
     参  数：空
     返回值：空
    ****************/
    void readSettings();       

    /****************
     功  能：初始化英雄榜数据
     参  数：空
     返回值：空
    ****************/
    void writeSetting();      

signals:

public slots:
    /****************
     功  能：重新设置英雄榜数据槽函数
     参  数：空
     返回值：空
    ****************/
    void slot_reset();
};

#endif // HERODIALOG_H
