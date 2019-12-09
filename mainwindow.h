/******************
 版本号：v1.0
 作  者：唐攀
 日  期：2019-12-1
******************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "common.h"
#include "herodialog.h"
#include "customgamedialog.h"
#include "minescene.h"
#include <QLCDNumber>
#include <QPushButton>
#include <QTimer>
#include <QMainWindow>
#include <QAction>
#include <QActionGroup>
#include <QWidget>
#include <QGraphicsView>
#include <QMenuBar>
#include <QLabel>
#include <QDebug>
#include <QSound>
#include <QMultimedia>
#include <QDialog>
#include <QLineEdit>




class Mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    Mainwindow(QWidget *parent = 0);
    ~Mainwindow();

    QAction *newaction;
    QAction *lowleveaction;
    QAction *middleleveaction;
    QAction *heightleveaction;
    QAction *customaction;
    QAction *coloraction;
    QAction *soundaction;
    QAction *heroaction;        //英雄榜行为
    QAction *exitaction;
    QAction *aboutaction;

    QWidget *central;
    QGraphicsView *GameView;    //主程序视图
    MineScene *minescene;       //主程序场景
    QLCDNumber *minenumLcd;     //雷数LCD
    QLCDNumber *timeLcd;        //时间LCD
    QPushButton *new_button;      //笑脸按钮
    QPushButton *mine_button;
    QPushButton *time_button;
    int m_time;                 //当前用时数
    QTimer *m_timer;            //定时器
    bool is_first;              //是否第一次打开游戏

    /****************
     功  能：创建行为，并连接到相应槽
     参  数：空
     返回值：空
    ****************/
    void create_action();

    /****************
     功  能：创建菜单
     参  数：空
     返回值：空
    ****************/
    void create_menu();

    /****************
     功  能：读当前游戏设置，并设置到场景的行，列，雷数，级别
     参  数：空
     返回值：空
    ****************/
    void readsettings();

    /****************
     功  能：写当前游戏设置，将当前场景的行，列，雷数，级别写入到注册表
     参  数：空
     返回值：空
    ****************/
    void writesettings();

public slots:
    /****************
     功  能：开始新游戏槽
     参  数：空
     返回值：空
    ****************/
    void slot_newgame();

    /****************
     功  能：写当前游戏设置，将当前场景的行，列，雷数，级别写入到注册表
     参  数：空
     返回值：空
    ****************/
//    void slot_colorchanged();       //设置颜色的槽

    /****************
     功  能：设置声音的槽
     参  数：空
     返回值：空
    ****************/
    void slot_soundchanged();

    /****************
     功  能：显示英雄榜的槽
     参  数：空
     返回值：空
    ****************/
    void slot_herochecked();

    /****************
     功  能：显示about扫雷的槽
     参  数：空
     返回值：空
    ****************/
    void slot_about();

    /****************
     功  能：更新英雄榜的槽，根据场景级别和游戏时间决定是否更新英雄榜
     参  数：空
     返回值：空
    ****************/
    void slot_updatehero();

    /****************
     功  能：显示雷数的槽，显示场景中剩余雷数＝雷总数-已标旗雷数
     参  数：int类型的雷数
     返回值：空
    ****************/
    void slot_displayMineNum(int);

    /****************
     功  能：显示时间的槽
     参  数：空
     返回值：空
    ****************/
    void slot_displayTime();

    /****************
     功  能：点击游戏级别行为开始新游戏槽
     参  数：QAction类型的指针
     返回值：空
    ****************/
    void slot_newgamebyleve(QAction *);

    /****************
     功  能：接收自定义游戏设置槽
     参  数：行数，列数，难度等级
     返回值：空
    ****************/
    void slot_acceptCutsomvale(int,int,int);

};

#endif // MAINWINDOW_H
