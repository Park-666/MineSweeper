/******************
 版本号：v1.0
 作  者：唐攀
 日  期：2019-12-1
******************/

#ifndef MINESCENE_H
#define MINESCENE_H

#include "common.h"
#include "mineitem.h"
#include <ctime>
#include <cstdlib>
#include <QObject>
#include <QGraphicsScene>
#include <QVector>
#include <QDebug>
#include <QSound>
#include <QMultimedia>

using namespace std;

class MineScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MineScene(QObject *patent = 0);

    QVector< QVector< MineItem *> > m_itemVec;  //存储方块的容器
    int m_scenerow;         //当前场景行数
    int m_scenecol;         //当前场景列数
    int m_minesum;          //当前场景雷数
    int m_crrentleve;       //当前场景难度级别

    int m_signedMineNum;    //右键标记的雷数
    int m_rightMineNum;     //右键标记正确的雷数
    bool m_isGameOver;      //游戏是否结束
    int m_remainNoMines;    //剩余非雷数
    bool m_soundOpen;       //声音开关: true: 打开声音 false: 关闭声音

    /****************
     功  能：初始化游戏场景
     参  数：空
     返回值：空
    ****************/ 
    void initscene();      

    /****************
     功  能：统计方块周围的雷数
     参  数：MineIem类型的对象指针
     返回值：空
    ****************/                      
    void countAroundMines(MineItem *t_item);    

    /****************
     功  能：打开所有雷
     参  数：空
     返回值：空
    ****************/ 
    void openAllMine(); 

    /****************
     功  能：扩散函数
     参  数：MineIem类型的指针
     返回值：空
    ****************/                      
    void expendWater(MineItem *t_item);     

signals:
    /****************
     功  能：游戏成功过关信号
     参  数：空
     返回值：空
    ****************/
    void sig_successPassGame();        

    /****************
     功  能：重新开始游戏信号
     参  数：空
     返回值：空
    ****************/
    void sig_scenenewGame();                

    /****************
     功  能：显示雷数信号
     参  数：整型的雷数
     返回值：空
    ****************/
    void sig_scenedisplayMineNum(int);     

    /****************
     功  能：游戏退出信号
     参  数：空
     返回值：空
    ****************/
    void sig_sceneExitGame();              
public slots:
    /****************
     功  能：打开所有的方块
     参  数：空
     返回值：空
    ****************/
    void slot_openAllItems();            

    /****************
     功  能：所有未打开方块覆盖
     参  数：空
     返回值：空
    ****************/
    void slot_closeAllItems();          
};

#endif // MINESCENE_H
