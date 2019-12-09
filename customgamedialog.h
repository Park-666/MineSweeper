/******************
 版本号：v1.0
 作  者：唐攀
 日  期：2019-12-1
******************/

#ifndef CUSTOMGAMEDIALOG_H
#define CUSTOMGAMEDIALOG_H

#include "common.h"
#include <QWidget>
#include <QDialog>
#include <QSpinBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSettings>

class CustomGameDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CustomGameDialog(QWidget *parent = 0);

    QSpinBox *colspinbox;       //列分量框
    QSpinBox *rowspinbox;       //行分量框
    QSpinBox *minenumspinbox;   //雷数分量框

    /****************
     功  能：读自定义游戏设置文件，并将读取到的数据设置到相应分量框
     参  数：空
     返回值：空
    ****************/
    void readsettings();

    /****************
     功  能：写自定义游戏设置文件，将当前的自定义游戏设置保存到注册表
     参  数：空
     返回值：空
    ****************/
    void writesettings();

signals:
    /****************
     功  能：发送自定义游戏行，列，雷数的信号
     参  数：空
     返回值：空
    ****************/
    void signal_sendCustomset(int, int, int);

public slots:
    /****************
     功  能：接收确定按钮的槽，获取游戏 行数 列数 雷数并发送信号
     参  数：空
     返回值：空
    ****************/
    void slot_accpetok();
};

#endif // CUSTOMGAMEDIALOG_H
