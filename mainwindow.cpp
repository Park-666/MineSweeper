#include "mainwindow.h"

Mainwindow::Mainwindow(QWidget *parent)
    : QMainWindow(parent), central(0), GameView(0), minescene(0), minenumLcd(0), timeLcd(0), new_button(0), m_timer(0)
{
    setWindowTitle("扫雷");
    setWindowIcon(QIcon(":/images/icon.png"));
    is_first = true;

    create_action();
    create_menu();

    slot_newgame();
}


void Mainwindow::create_action()
{
    heroaction = new QAction(QIcon(":/images/heroes.png"), "排行榜", this);
    connect(heroaction, &QAction::triggered, this, &Mainwindow::slot_herochecked);

    newaction = new QAction("新游戏", this);
    connect(newaction, &QAction::triggered, this, &Mainwindow::slot_newgame);

//    coloraction = new QAction();

    soundaction = new QAction("背景音乐", this);
    soundaction->setCheckable(true);
    connect(soundaction, &QAction::triggered, this, &Mainwindow::slot_soundchanged);

    exitaction = new QAction("退出游戏", this);
    connect(exitaction, &QAction::triggered, this, &Mainwindow::close);

    lowleveaction = new QAction("初等", this);
    lowleveaction->setCheckable(true);
    lowleveaction->setChecked(true);
    middleleveaction = new QAction("中等", this);
    middleleveaction->setCheckable(true);
    heightleveaction = new QAction("高等", this);
    heightleveaction->setCheckable(true);
    customaction = new QAction("自定义", this);
    customaction->setCheckable(true);

    QActionGroup *Defficulty = new QActionGroup(this);
    Defficulty->addAction(lowleveaction);
    Defficulty->addAction(middleleveaction);
    Defficulty->addAction(heightleveaction);
    Defficulty->addAction(customaction);
    connect(Defficulty, SIGNAL(triggered(QAction *)), this, SLOT(slot_newgamebyleve(QAction *)));

    aboutaction = new QAction(QIcon(":/images/about.png"), "关于", this);
    connect(aboutaction, &QAction::triggered, this, &Mainwindow::slot_about);
}

void Mainwindow::create_menu()
{
    QMenu *RankingList = menuBar()->addMenu("英雄榜");        //菜单栏中的排行榜
    RankingList->addAction(heroaction);


    QMenu *Set = menuBar()->addMenu("设置");        //菜单栏中的游戏设置
    Set->addAction(newaction);
    Set->addSeparator();
//    Set->addAction(coloraction);
    Set->addAction(soundaction);
    Set->addAction(exitaction);

    QMenu *Difficulty = menuBar()->addMenu("难度");      //菜单栏中的游戏难度选择
    Difficulty->addAction(lowleveaction);
    Difficulty->addAction(middleleveaction);
    Difficulty->addAction(heightleveaction);
    Difficulty->addAction(customaction);

    QMenu *Help = menuBar()->addMenu("帮助");      //菜单栏中的帮助
    Help->addAction(aboutaction);
}

void Mainwindow::readsettings()
{
    QSettings *read = new QSettings("TPZS", "MineSweeper");
    read->beginGroup("Current_row_col_mine_leve");
    int row = read->value("row", 10).toInt();
    int col = read->value("col", 10).toInt();
    int mine = read->value("mine", 10).toInt();
    int leve = read->value("leve", Common::LOW_LEVE).toInt();
    bool sounds = read->value("sound", false).toBool();
    read->endGroup();

    minescene->m_scenerow = row;
    minescene->m_scenecol = col;
    minescene->m_minesum = mine;
    minescene->m_crrentleve = leve;
    minescene->m_soundOpen = sounds;
    if(sounds)
    {
        soundaction->setChecked(true);
    }
}


void Mainwindow::writesettings()
{
    QSettings *write = new QSettings("TPZS", "MineSweeper");
    write->beginGroup("Current_row_col_mine_leve");
    write->setValue("row", QString::number(minescene->m_scenerow));
    write->setValue("col", QString::number(minescene->m_scenecol));
    write->setValue("mine", QString::number(minescene->m_minesum));
    write->setValue("leve", QString::number(minescene->m_crrentleve));
    write->setValue("sound", minescene->m_soundOpen);
    write->endGroup();
}


void Mainwindow::slot_herochecked()
{
    HeroDialog heronames;
    heronames.exec();
}


void Mainwindow::slot_newgame()
{
    if(is_first)
    {
        is_first = !is_first;
    }
    else
    {
        delete minenumLcd;
        delete mine_button;
        delete new_button;
        delete time_button;

        delete timeLcd;
        delete m_timer;
    }

    minenumLcd = new QLCDNumber;        //雷数
    minenumLcd->setBackgroundRole(QPalette::Window);
    minenumLcd->setForegroundRole(QPalette::WindowText);

    mine_button = new QPushButton;      //雷数按钮
    mine_button->setShortcut(QKeySequence::Undo);
    mine_button->setIcon(QIcon(":/images/warning.png"));

    new_button = new QPushButton;       //新游戏按钮
    new_button->setIcon(QIcon(":/images/smile.png"));
    connect(new_button, &QPushButton::clicked, this, &Mainwindow::slot_newgame);

    time_button = new QPushButton;      //计时图标
    time_button->setShortcut(QKeySequence::SelectAll);
    time_button->setIcon(QIcon(":/images/alarm.png"));

    timeLcd = new QLCDNumber;       //用时
    timeLcd->setBackgroundRole(QPalette::Window);
    timeLcd->setForegroundRole(QPalette::WindowText);

    central = new QWidget(this);
    setCentralWidget(central);

    QHBoxLayout *lcd_layout = new QHBoxLayout;      //雷数和用时的 水平布局
    lcd_layout->addWidget(minenumLcd);
    lcd_layout->addWidget(mine_button);
    lcd_layout->addStretch();
    lcd_layout->addWidget(new_button);
    lcd_layout->addStretch();
    lcd_layout->addWidget(time_button);
    lcd_layout->addWidget(timeLcd);

    GameView = new QGraphicsView;
    minescene = new MineScene;
    GameView->setScene(minescene);

    QVBoxLayout *main_layout = new QVBoxLayout(central);
    main_layout->addLayout(lcd_layout);
    main_layout->addWidget(GameView);
    main_layout->addStretch();

    readsettings();

    connect(minescene, &MineScene::sig_successPassGame, this, &Mainwindow::slot_updatehero);
    connect(minescene, &MineScene::sig_scenenewGame, this, &Mainwindow::slot_newgame);
    connect(minescene, &MineScene::sig_scenedisplayMineNum, this, &Mainwindow::slot_displayMineNum);

    connect(minescene, &MineScene::sig_sceneExitGame, this, &Mainwindow::close);


    minescene->setSceneRect(0, 0, minescene->m_scenecol * Common::MAP_WIDTH, minescene->m_scenerow * Common::MAP_HEIGHT);
    setFixedSize(minescene->m_scenecol * Common::MAP_WIDTH + 24, minescene->m_scenerow * Common::MAP_HEIGHT + 86);
    if(minescene->m_crrentleve == Common::LOW_LEVE)
    {
        lowleveaction->setChecked(true);
    }
    else if(minescene->m_crrentleve == Common::MIDD_LELEVE)
    {
        middleleveaction->setChecked(true);
    }
    else if(minescene->m_crrentleve == Common::HEIGHT_LEVE)
    {
        heightleveaction->setChecked(true);
    }
    m_time = 0;
    minenumLcd->display(minescene->m_minesum);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &Mainwindow::slot_displayTime);
    m_timer->start(1000);

    minescene->initscene();

    connect(time_button, &QPushButton::pressed, minescene, &MineScene::slot_openAllItems);
    connect(mine_button, &QPushButton::pressed, minescene, &MineScene::slot_closeAllItems);
}

//void Mainwindow::slot_colorchanged()
//{

//}

void Mainwindow::slot_soundchanged()
{
    minescene->m_soundOpen = !minescene->m_soundOpen;
    writesettings();        //改变声音开关后写入注册表
}

void Mainwindow::slot_about()
{
    QMessageBox About;
    About.setWindowTitle("About");
    About.setWindowIcon(QIcon(":/images/about.png"));
    About.setIconPixmap(QPixmap(":/images/icon.png"));

    QString text = " The Version  : MineSweeper v1.0\n\n The Auther   : TangPan\n\n The Date       : 2019-12-1";

    About.setText(text);
    About.exec();
}

void Mainwindow::slot_updatehero()
{
    if(minescene->m_crrentleve == Common::LOW_LEVE)
    {
        QSettings *read = new QSettings("TPZS", "MineSweeper");

        //读取时间
        read->beginGroup("Heroes_record");
        QString junior_time = read->value("junior", "999").toString();
        read->endGroup();

        if(m_time < junior_time.toInt())
        {
            QDialog *new_record = new QDialog;
            new_record->setFixedSize(250, 100);
            new_record->setWindowTitle("新纪录");
            QLabel *label_name = new QLabel("破纪录了，请留下你的大名");
            label_name->setAlignment(Qt::AlignCenter);
            QLineEdit *line_name = new QLineEdit;
            QPushButton *ok_button = new QPushButton("确 认");
            connect(ok_button, &QPushButton::clicked, new_record, &QDialog::close);
            QVBoxLayout *record_layout = new QVBoxLayout(new_record);
            record_layout->addWidget(label_name);
            record_layout->addWidget(line_name);
            record_layout->addWidget(ok_button);
            new_record->exec();
            QSettings *write = new QSettings("TPZS", "MineSweeper");

            //写入名字
            write->beginGroup("Heroes_name");
            write->setValue("junior", line_name->text());
            write->endGroup();

            //写入时间
            write->beginGroup("Heroes_record");
            write->setValue("junior", m_time);
            write->endGroup();
        }

    }
    else if(minescene->m_crrentleve == Common::MIDD_LELEVE)
    {
        QSettings *read = new QSettings("TPZS", "MineSweeper");

        //读取时间
        read->beginGroup("Heroes_record");
        QString intermediate_time = read->value("intermediate", "999").toString();
        read->endGroup();

        if(m_time < intermediate_time.toInt())
        {
            QDialog *new_record = new QDialog;
            new_record->setFixedSize(250, 100);
            new_record->setWindowTitle("新纪录");
            QLabel *label_name = new QLabel("破纪录了，请留下你的大名");
            label_name->setAlignment(Qt::AlignCenter);
            QLineEdit *line_name = new QLineEdit;
            QPushButton *ok_button = new QPushButton("确 认");
            connect(ok_button, &QPushButton::clicked, new_record, &QDialog::close);
            QVBoxLayout *record_layout = new QVBoxLayout(new_record);
            record_layout->addWidget(label_name);
            record_layout->addWidget(line_name);
            record_layout->addWidget(ok_button);
            new_record->exec();
            QSettings *write = new QSettings("TPZS", "MineSweeper");

            //写入名字
            write->beginGroup("Heroes_name");
            write->setValue("intermediate", line_name->text());
            write->endGroup();

            //写入时间
            write->beginGroup("Heroes_record");
            write->setValue("intermediate", m_time);
            write->endGroup();
        }
    }
    else if(minescene->m_crrentleve == Common::HEIGHT_LEVE)
    {
        QSettings *read = new QSettings("TPZS", "MineSweeper");

        //读取时间
        read->beginGroup("Heroes_record");
        QString advanced_time = read->value("advanced", "999").toString();
        read->endGroup();

        if(m_time < advanced_time.toInt())
        {
            QDialog *new_record = new QDialog;
            new_record->setFixedSize(250, 100);
            new_record->setWindowTitle("新纪录");
            QLabel *label_name = new QLabel("破纪录了，请留下你的大名");
            label_name->setAlignment(Qt::AlignCenter);
            QLineEdit *line_name = new QLineEdit;
            QPushButton *ok_button = new QPushButton("确 认");
            connect(ok_button, &QPushButton::clicked, new_record, &QDialog::close);
            QVBoxLayout *record_layout = new QVBoxLayout(new_record);
            record_layout->addWidget(label_name);
            record_layout->addWidget(line_name);
            record_layout->addWidget(ok_button);

            new_record->exec();
            QSettings *write = new QSettings("TPZS", "MineSweeper");

            //写入名字
            write->beginGroup("Heroes_name");
            write->setValue("advanced", line_name->text());
            write->endGroup();

            //写入时间
            write->beginGroup("Heroes_record");
            write->setValue("advanced", m_time);
            write->endGroup();
        }
    }
}

void Mainwindow::slot_displayMineNum(int mine)
{
    minenumLcd->display(minescene->m_minesum - mine);
}

void Mainwindow::slot_displayTime()
{
    if(!minescene->m_isGameOver)
    {
        if(minescene->m_soundOpen)
        {
            QSound::play(":/sounds/sounds/time.wav");

        }
        timeLcd->display(++m_time);
    }
}

void Mainwindow::slot_newgamebyleve(QAction *action)
{
    if(action == lowleveaction)
    {
        minescene->m_scenerow = Common::LOW_ROW_AND_COL;
        minescene->m_scenecol = Common::LOW_ROW_AND_COL;
        minescene->m_minesum = Common::LOW_MINE_NUM;
        minescene->m_crrentleve = Common::LOW_LEVE;
    }
    else if(action == middleleveaction)
    {
        minescene->m_scenerow = Common::MIDDLE_ROW_AND_COL;
        minescene->m_scenecol = Common::MIDDLE_ROW_AND_COL;
        minescene->m_minesum = Common::MIDDLE_MINE_NUM;
        minescene->m_crrentleve = Common::MIDD_LELEVE;
    }
    else if(action == heightleveaction)
    {
        minescene->m_scenerow = Common::HEIGHT_ROW;
        minescene->m_scenecol = Common::HEIGHT_COL;
        minescene->m_minesum = Common::HEIGHT_MINE_NUM;
        minescene->m_crrentleve = Common::HEIGHT_LEVE;
    }
    else if(action == customaction)
    {
        CustomGameDialog *custom = new CustomGameDialog(this);
        connect(custom, &CustomGameDialog::signal_sendCustomset, this, &Mainwindow::slot_acceptCutsomvale);

        custom->exec();
    }
    writesettings();
    slot_newgame();
}

void Mainwindow::slot_acceptCutsomvale(int row, int col, int mine)
{
    minescene->m_scenerow = row;
    minescene->m_scenecol = col;
    minescene->m_minesum = mine;
    minescene->m_crrentleve = Common::CUSOM_LEVE;
}

Mainwindow::~Mainwindow()
{

}
