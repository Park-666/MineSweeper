/******************
 版本号：v1.0
 作  者：唐攀
 日  期：2019-12-1
******************/

#ifndef MINEITEM_H
#define MINEITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QMessageBox>
#include <QIcon>
#include <QDebug>
#include <QPushButton>
#include <QSound>
#include <QMultimedia>


class MineItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    MineItem(int t_x, int t_y, QPixmap pixmap, QGraphicsItem *parent = 0);

    int  m_X;                       //在容器中的列数
    int  m_Y;                       //在容器中的行数
    bool m_isMine;                  //是否为雷
    bool m_isOpened;                //是否打开
    int  m_aroundMineNum;           //周围雷数
    int  m_rMouseKeyNum;            //右键点击的次数
    bool m_is_rightbutton_mark;     //右键是否标记

    /****************
     功  能：鼠标点击事件(右键)
     参  数：QGraphicsSceneMouseEvent类的指针
     返回值：空
    ****************/
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    /****************
     功  能：鼠标释放事件(左键)
     参  数：QGraphicsSceneMouseEvent类的指针
     返回值：空
    ****************/      
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:
    /****************
     功  能：成功通关信号
     参  数：空
     返回值：空
    ****************/
    void sig_passGame();

    /****************
     功  能：重新开始游戏信号
     参  数：空
     返回值：空
    ****************/
    void sig_restartGame(); 

    /****************
     功  能：重设雷数信号
     参  数：整型的雷数
     返回值：空
    ****************/                      
    void sig_resetMineNum(int t_signedMineNum);

    /****************
     功  能：退出游戏信号
     参  数：空
     返回值：空
    ****************/ 
    void sig_exitGame();                     
public slots:
};

#endif // MINEITEM_H
