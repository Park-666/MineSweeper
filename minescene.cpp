#include "minescene.h"
#include "mineitem.h"

QPoint t_around[8] =
{
    QPoint(-1,-1),
    QPoint(-1,0),
    QPoint(-1,1),
    QPoint(0,-1),
    QPoint(0,1),
    QPoint(1,-1),
    QPoint(1,0),
    QPoint(1,1)
};

MineScene::MineScene(QObject *parent)
    : QGraphicsScene(parent)
{
    m_crrentleve;

    m_signedMineNum = 0;
    m_rightMineNum = 0;
    m_isGameOver = false;
}

void MineScene::initscene()
{    
    m_remainNoMines = m_scenerow * m_scenecol - m_minesum;

    //将小方块一个一个放入容器，并加入场景
    for(int i =  0; i < m_scenerow; i++)    //遍历行
    {
        QVector<MineItem *> row_vec;
        for(int j = 0; j < m_scenecol ; j++)        //遍历列
        {
            MineItem *cover = new MineItem(j, i, QPixmap(":/images/cover1.png"));
            cover->setPos(j * Common::MAP_WIDTH + 3, i * Common::MAP_HEIGHT + 3);
            addItem(cover);
            row_vec.push_back(cover);
        }
        m_itemVec.push_back(row_vec);   //存的是 一整行
    }

    srand(time(NULL));
    for(int i = 0; i < m_minesum; i++)
    {
        int row = rand() % m_scenerow;    //行的取值范围 [0, m_scenerow - 1]
        int col = rand() % m_scenecol;

        if(!m_itemVec[row][col]->m_isMine)
        {
            m_itemVec[row][col]->m_isMine = true;
            countAroundMines(m_itemVec[row][col]);
        }
        else
        {
            i--;
        }
    }

    for(int i = 0; i < m_scenerow; i++)
    {
        for(int j = 0; j < m_scenecol; j++)
        {
            connect(m_itemVec[i][j], &MineItem::sig_passGame, this, &MineScene::sig_successPassGame);
            connect(m_itemVec[i][j], &MineItem::sig_restartGame, this, &MineScene::sig_scenenewGame);
            connect(m_itemVec[i][j], &MineItem::sig_resetMineNum, this, &MineScene::sig_scenedisplayMineNum);
            connect(m_itemVec[i][j], &MineItem::sig_exitGame, this, &MineScene::sig_sceneExitGame);
        }
    }
}


void MineScene::countAroundMines(MineItem *t_item)
{
    for(int i = 0; i < 8; i++)
    {
        int x = t_item->m_X + t_around[i].x();      //x为列数
        int y = t_item->m_Y + t_around[i].y();      //y为行数

        if(x < 0 || x >= m_scenecol || y < 0 || y >= m_scenerow)
        {
            continue;
        }
        if(m_itemVec[y][x]->m_isMine)       //容器的下标用行列，不是坐标
        {
            continue;
        }

        m_itemVec[y][x]->m_aroundMineNum++;
    }
}


void MineScene::slot_openAllItems()
{
    for(int i = 0; i < m_scenerow; i++)
    {
        for(int j = 0; j < m_scenecol; j++)
        {
            if(m_itemVec[i][j]->m_isMine)
            {
                m_itemVec[i][j]->setPixmap(QPixmap(":/images/icon.png"));
            }
            else
            {
                if(m_itemVec[i][j]->m_aroundMineNum == 0)
                {
                    m_itemVec[i][j]->setPixmap(QPixmap(":/images/gradual_1.png"));
                }
                else if(m_itemVec[i][j]->m_aroundMineNum != 0)
                {
                    switch (m_itemVec[i][j]->m_aroundMineNum)
                    {
                    case 1:
                        m_itemVec[i][j]->setPixmap(QPixmap(":/images/1.png"));
                        break;
                    case 2:
                        m_itemVec[i][j]->setPixmap(QPixmap(":/images/2.png"));
                        break;
                    case 3:
                        m_itemVec[i][j]->setPixmap(QPixmap(":/images/3.png"));
                        break;
                    case 4:
                        m_itemVec[i][j]->setPixmap(QPixmap(":/images/4.png"));
                        break;
                    case 5:
                        m_itemVec[i][j]->setPixmap(QPixmap(":/images/5.png"));
                        break;
                    case 6:
                        m_itemVec[i][j]->setPixmap(QPixmap(":/images/6.png"));
                        break;
                    case 7:
                        m_itemVec[i][j]->setPixmap(QPixmap(":/images/7.png"));
                        break;
                    case 8:
                        m_itemVec[i][j]->setPixmap(QPixmap(":/images/8.png"));
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }
}


void MineScene::slot_closeAllItems()
{
    for(int i = 0; i < m_scenerow; i++)
    {
        for(int j = 0; j < m_scenecol; j++)
        {
            if(!m_itemVec[i][j]->m_isOpened)
            {
                if(m_itemVec[i][j]->m_rMouseKeyNum == 0)
                {
                   m_itemVec[i][j]->setPixmap(QPixmap(":/images/cover1.png"));
                }
                else if(m_itemVec[i][j]->m_rMouseKeyNum == 1)
                {
                    m_itemVec[i][j]->setPixmap(QPixmap(":/images/flag1_1.png"));
                }
                else if(m_itemVec[i][j]->m_rMouseKeyNum == 2)
                {
                    m_itemVec[i][j]->setPixmap(QPixmap(":/images/help_64.png"));
                }
            }
        }
    }
}


void MineScene::openAllMine()
{
    for(int i = 0; i < m_scenerow; i++)
    {
        for(int j = 0; j < m_scenecol; j++)
        {
            m_itemVec[i][j]->m_isOpened = true;
            if(m_itemVec[i][j]->m_isMine)
            {
                if(m_itemVec[i][j]->m_rMouseKeyNum == 1)
                {
                    m_itemVec[i][j]->setPixmap(QPixmap(":/images/mark_right.png"));
                }
                else
                {
                   m_itemVec[i][j]->setPixmap(QPixmap(":/images/icon.png"));
                }
            }
            if(!m_itemVec[i][j]->m_isMine)
            {
                if(m_itemVec[i][j]->m_rMouseKeyNum == 1)
                {
                    m_itemVec[i][j]->setPixmap(QPixmap(":/images/mark_error.png"));
                }
            }
        }
    }
}


void MineScene::expendWater(MineItem *t_item)
{
    if(t_item->m_isMine)
    {
        return;
    }
    if(!t_item->m_isMine && t_item->m_aroundMineNum == 0)   //非雷而且周围无雷
    {
        t_item->m_isOpened = true;
        m_remainNoMines--;

        t_item->setPixmap(QPixmap(":/images/gradual_1.png"));
//        _sleep(3);
        for(int i = 0; i < 8; i++)
        {
            int x = t_item->m_X + t_around[i].x();      //x为列数
            int y = t_item->m_Y + t_around[i].y();      //y为行数

            if(x < 0 || x >= m_scenecol || y < 0 || y >= m_scenerow)
            {
                continue;
            }
            if(m_itemVec[y][x]->m_isOpened == false && m_itemVec[y][x]->m_is_rightbutton_mark == false)
            { 

                expendWater(m_itemVec[y][x]);
            }
        }
    }
    if(!t_item->m_isMine && t_item->m_aroundMineNum != 0)       //非雷，周围有雷
    {
        t_item->m_isOpened = true;
        m_remainNoMines--;

        switch (t_item->m_aroundMineNum)
        {
        case 1:
            t_item->setPixmap(QPixmap(":/images/1.png"));
            break;
        case 2:
            t_item->setPixmap(QPixmap(":/images/2.png"));
            break;
        case 3:
            t_item->setPixmap(QPixmap(":/images/3.png"));
            break;
        case 4:
            t_item->setPixmap(QPixmap(":/images/4.png"));
            break;
        case 5:
            t_item->setPixmap(QPixmap(":/images/5.png"));
            break;
        case 6:
            t_item->setPixmap(QPixmap(":/images/6.png"));
            break;
        case 7:
            t_item->setPixmap(QPixmap(":/images/7.png"));
            break;
        case 8:
            t_item->setPixmap(QPixmap(":/images/8.png"));
            break;
        default:
            break;
        }
    }
}

















