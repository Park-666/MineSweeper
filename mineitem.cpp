#include "mineitem.h"
#include "minescene.h"

MineItem::MineItem(int t_x, int t_y, QPixmap pixmap, QGraphicsItem *parent)
    : QGraphicsPixmapItem(pixmap, parent), m_X(t_x), m_Y(t_y)
{
    m_isMine = false;
    m_is_rightbutton_mark = false;
    m_isOpened = false;
    m_aroundMineNum = 0;
    m_rMouseKeyNum = 0;
}

void MineItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    MineScene *minescene = (MineScene *)scene();

    if(minescene->m_isGameOver || m_isOpened)
    {
        return;
    }

    if(event->button() == Qt::RightButton)
    {
        if(m_rMouseKeyNum == 0) //右键点击次数为0
        {
            if(minescene->m_soundOpen)
            {
                QSound::play(":/sounds/sounds/click.wav");
            }

            m_is_rightbutton_mark = true;
            m_rMouseKeyNum++;   //右键点击次数++
            minescene->m_signedMineNum++;   //右键标记雷数++
            setPixmap(QPixmap(":/images/flag1_1.png"));
            emit sig_resetMineNum(minescene->m_signedMineNum);

            if(m_isMine)
            {
                minescene->m_rightMineNum++;
            }
        }
        else if(m_rMouseKeyNum == 1)
        {
            if(minescene->m_soundOpen)
            {
                QSound::play(":/sounds/sounds/click.wav");
            }

            m_is_rightbutton_mark = true;
            m_rMouseKeyNum++;
            minescene->m_signedMineNum--;
            setPixmap(QPixmap(":/images/help_64.png"));
            emit sig_resetMineNum(minescene->m_signedMineNum);

            if(m_isMine)
            {
                minescene->m_rightMineNum--;
            }
        }
        else
        {
            if(minescene->m_soundOpen)
            {
                QSound::play(":/sounds/sounds/click.wav");
            }

            m_is_rightbutton_mark = false;
            m_rMouseKeyNum =  0;
            setPixmap(QPixmap(":/images/cover1.png"));
        }

        if(minescene->m_remainNoMines == 0 || (minescene->m_rightMineNum == minescene->m_minesum && minescene->m_signedMineNum == minescene->m_minesum))
        {

            if(minescene->m_soundOpen)
            {
                QSound::play(":/sounds/sounds/win.wav");
            }

            minescene->m_isGameOver = true;
            minescene->openAllMine();

            emit sig_passGame();

            QMessageBox game_success;
            QPushButton *yes = game_success.addButton("继续游戏", QMessageBox::YesRole);
            QPushButton *no = game_success.addButton("不玩了", QMessageBox::NoRole);
            game_success.setWindowTitle("成功过关");

            game_success.setWindowIcon(QIcon(":/images/icon.png"));
            game_success.setText("<font size='6' color='red'><b><p align='center'>恭喜你成功找到所有雷！</p></b></font>");

            game_success.exec();
            if(game_success.clickedButton() == yes)
            {
                emit sig_restartGame();
            }
            if(game_success.clickedButton() == no)
            {
                emit sig_exitGame();
            }
        }
    }
}


void MineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    MineScene *minescene = (MineScene *)scene();

    if(minescene->m_isGameOver || m_isOpened || m_is_rightbutton_mark)
    {
        return;
    }

    if(event->button() == Qt::LeftButton)
    {
        if(m_isMine)
        {
            if(minescene->m_soundOpen)
            {
                QSound::play(":/sounds/sounds/bong.wav");
            }

            minescene->openAllMine();
            minescene->m_isGameOver = true;
            QMessageBox game_false;
            game_false.setWindowTitle("失 败");
            QPushButton *yes = game_false.addButton("继续游戏", QMessageBox::YesRole);
            QPushButton *no = game_false.addButton("不玩了", QMessageBox::NoRole);

            game_false.setWindowIcon(QIcon(":/images/icon.png"));
            QString text = QString::number(minescene->m_rightMineNum);


            game_false.setText("<font size='3'><b>只找到</b></font>"
                               + text
                               + "<font size='3'><b>个雷，</b></font>"
                               "<font size='3'><b>祝你下次好运！</b></font>");
            game_false.exec();
            if(game_false.clickedButton() == yes)
            {
                emit sig_restartGame();
            }
            if(game_false.clickedButton() == no)
            {
                emit sig_exitGame();
            }
        }
        else
        {           
            if(m_aroundMineNum == 0)
            {
                if(minescene->m_soundOpen)
                {
                    QSound::play(":/sounds/sounds/click.wav");

                }
                minescene->expendWater(this);
            }
            else if(m_aroundMineNum != 0)
            {
                if(minescene->m_soundOpen)
                {
                    QSound::play(":/sounds/sounds/click.wav");

                }
                minescene->m_remainNoMines--;
                m_isOpened = true;
                switch (m_aroundMineNum)
                {
                case 1:
                    setPixmap(QPixmap(":/images/1.png"));
                    break;
                case 2:
                    setPixmap(QPixmap(":/images/2.png"));
                    break;
                case 3:
                    setPixmap(QPixmap(":/images/3.png"));
                    break;
                case 4:
                    setPixmap(QPixmap(":/images/4.png"));
                    break;
                case 5:
                    setPixmap(QPixmap(":/images/5.png"));
                    break;
                case 6:
                    setPixmap(QPixmap(":/images/6.png"));
                    break;
                case 7:
                    setPixmap(QPixmap(":/images/7.png"));
                    break;
                case 8:
                    setPixmap(QPixmap(":/images/8.png"));
                    break;
                default:
                    break;
                }
            }
        }

        if(minescene->m_remainNoMines == 0 || (minescene->m_rightMineNum == minescene->m_minesum && minescene->m_signedMineNum == minescene->m_minesum))
        {

            if(minescene->m_soundOpen)
            {
                QSound::play(":/sounds/sounds/win.wav");

            }
            minescene->m_isGameOver = true;
            minescene->openAllMine();
            emit sig_passGame();

            QMessageBox game_success;
            QPushButton *yes = game_success.addButton("继续游戏", QMessageBox::YesRole);
            QPushButton *no = game_success.addButton("不玩了", QMessageBox::NoRole);
            game_success.setWindowTitle("成功过关");

            game_success.setWindowIcon(QIcon(":/images/icon.png"));
            game_success.setText("<font size='10' color='red'><b><p align='center'>恭喜你成功找到所有雷！</p></b></font>");

            game_success.exec();
            if(game_success.clickedButton() == yes)
            {
                emit sig_restartGame();
            }
            if(game_success.clickedButton() == no)
            {
                emit sig_exitGame();
            }
        }
    }
}









