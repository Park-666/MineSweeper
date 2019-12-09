#include "herodialog.h"

HeroDialog::HeroDialog(QDialog *parent)
    : QDialog(parent)
{
    setWindowTitle("排行榜");
    setWindowIcon(QIcon(":/images/heroes.png"));
    junior_label = new QLabel;
    junior_label->setText("初级 :");
    intermediate_label = new QLabel;
    intermediate_label->setText("中级 :");
    advanced_label = new QLabel;
    advanced_label->setText("高级 :");

    jun_time_label = new QLabel;
    jun_time_label->setText(" ");
    jun_time_label->setAlignment(Qt::AlignCenter);
    int_time_label = new QLabel;
    int_time_label->setText(" ");
    int_time_label->setAlignment(Qt::AlignCenter);
    adv_time_label = new QLabel;
    adv_time_label->setText(" ");
    adv_time_label->setAlignment(Qt::AlignCenter);

    jun_name_label = new QLabel;
    jun_name_label->setText(" ");
    jun_name_label->setAlignment(Qt::AlignCenter);
    int_name_label = new QLabel;
    int_name_label->setText(" ");
    int_name_label->setAlignment(Qt::AlignCenter);
    adv_name_label = new QLabel;
    adv_name_label->setText(" ");
    adv_name_label->setAlignment(Qt::AlignCenter);

    QVBoxLayout *difficulty_vgrid = new QVBoxLayout;
    difficulty_vgrid->addWidget(junior_label);
    difficulty_vgrid->addWidget(intermediate_label);
    difficulty_vgrid->addWidget(advanced_label);

    QVBoxLayout *second_vgrid = new QVBoxLayout;
    second_vgrid->addWidget(jun_time_label);
    second_vgrid->addWidget(int_time_label);
    second_vgrid->addWidget(adv_time_label);

    QVBoxLayout *name_vgrid = new QVBoxLayout;
    name_vgrid->addWidget(jun_name_label);
    name_vgrid->addWidget(int_name_label);
    name_vgrid->addWidget(adv_name_label);

    QHBoxLayout *up_hgrid = new QHBoxLayout;
    up_hgrid->addLayout(difficulty_vgrid);
    up_hgrid->addLayout(second_vgrid);
    up_hgrid->addLayout(name_vgrid);

    QPushButton *reset_button = new QPushButton("重置数据");
    QPushButton *ok_button = new QPushButton("确 认");
    connect(ok_button, &QPushButton::clicked, this, &QDialog::close);
    connect(reset_button, &QPushButton::clicked, this, &HeroDialog::slot_reset);

    ok_button->setCheckable(true);
    ok_button->setChecked(true);

    QHBoxLayout *down_hgrid = new QHBoxLayout;
    down_hgrid->addWidget(reset_button);
    down_hgrid->addStretch();
    down_hgrid->addWidget(ok_button);

    QVBoxLayout *main_grid = new QVBoxLayout(this);
    main_grid->addLayout(up_hgrid);
    main_grid->addLayout(down_hgrid);

    readSettings();
    setFixedSize(280, 150);
}

void HeroDialog::readSettings()
{
    QSettings *read = new QSettings("TPZS", "MineSweeper");
    //读取时间
    read->beginGroup("Heroes_record");
    QString junior_time = read->value("junior", "xxxx").toString();
    QString intermediate_time = read->value("intermediate", "xxxx").toString();
    QString advanced_time = read->value("advanced", "xxxx").toString();
    read->endGroup();

    jun_time_label->setText(junior_time);
    int_time_label->setText(intermediate_time);
    adv_time_label->setText(advanced_time);

    //读取名字
    read->beginGroup("Heroes_name");
    QString junior_name = read->value("junior", "xxxx").toString();
    QString intermediate_name = read->value("intermediate", "xxxx").toString();
    QString advanced_name = read->value("advanced", "xxxx").toString();
    read->endGroup();

    jun_name_label->setText(junior_name);
    int_name_label->setText(intermediate_name);
    adv_name_label->setText(advanced_name);
}


void HeroDialog::writeSetting()
{
    QSettings *write = new QSettings("TPZS", "MineSweeper");
    //写入时间
    write->beginGroup("Heroes_record");
    write->setValue("junior", jun_time_label->text());
    write->setValue("intermediate", int_time_label->text());
    write->setValue("advanced", adv_time_label->text());
    write->endGroup();

    //写入名字
    write->beginGroup("Heroes_name");
    write->setValue("junior", jun_name_label->text());
    write->setValue("intermediate", int_name_label->text());
    write->setValue("advanced", adv_name_label->text());
    write->endGroup();
}


void HeroDialog::slot_reset()
{
    QSettings *reset = new QSettings("TPZS", "MineSweeper");

    reset->beginGroup("Heroes_record");
    reset->setValue("junior", "9999");
    reset->setValue("intermediate", "9999");
    reset->setValue("advanced", "9999");
    reset->endGroup();

    reset->beginGroup("Heroes_name");
    reset->setValue("junior", "xxxx");
    reset->setValue("intermediate", "xxxx");
    reset->setValue("advanced", "xxxx");
    reset->endGroup();

    readSettings();
    writeSetting();
}

