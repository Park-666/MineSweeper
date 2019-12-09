#include "customgamedialog.h"

CustomGameDialog::CustomGameDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("自定义难度");
    setWindowIcon(QIcon(":/images/icon.png"));

    QLabel *row_label = new QLabel("设 置 行 数:");
    row_label->setFixedHeight(30);
    QLabel *col_label = new QLabel("设 置 列 数:");
    col_label->setFixedHeight(30);
    QLabel *mine_label = new QLabel("设 置 雷 数:");
    mine_label->setFixedHeight(30);

    rowspinbox = new QSpinBox;
    rowspinbox->setRange(10, 22);
    rowspinbox->setSingleStep(3);
    rowspinbox->setFixedWidth(150);
    rowspinbox->setFixedHeight(30);

    colspinbox = new QSpinBox;
    colspinbox->setRange(10, 33);
    colspinbox->setSingleStep(3);
    colspinbox->setFixedHeight(30);

    minenumspinbox = new QSpinBox;
    minenumspinbox->setRange(1, 99);
    minenumspinbox->setSingleStep(5);
    minenumspinbox->setFixedHeight(30);

    QPushButton *ok_button = new QPushButton("确 认");
    connect(ok_button, &QPushButton::clicked, this, &CustomGameDialog::slot_accpetok);
    QPushButton *cancel_button = new QPushButton("取 消");
    connect(cancel_button, &QPushButton::clicked, this, &QDialog::close);

    QVBoxLayout *l_vlayout = new QVBoxLayout;
    l_vlayout->addWidget(row_label);
    l_vlayout->addWidget(col_label);
    l_vlayout->addWidget(mine_label);

    QVBoxLayout *r_vlayout = new QVBoxLayout;
    r_vlayout->addWidget(rowspinbox);
    r_vlayout->addWidget(colspinbox);
    r_vlayout->addWidget(minenumspinbox);

    QHBoxLayout *up_hlayout = new QHBoxLayout;
    up_hlayout->addLayout(l_vlayout);
    up_hlayout->addLayout(r_vlayout);

    QHBoxLayout *down_hlayout = new QHBoxLayout;
    down_hlayout->addWidget(ok_button);
    down_hlayout->addStretch();
    down_hlayout->addWidget(cancel_button);

    QVBoxLayout *main_layout = new QVBoxLayout(this);
    main_layout->addLayout(up_hlayout);
    main_layout->addLayout(down_hlayout);

    readsettings();
    setFixedSize(300, 170);
}

void CustomGameDialog::readsettings()
{
    QSettings *read = new QSettings("TPZS", "MineSweeper");
    read->beginGroup("Current_row_col_mine_leve");
    int row = read->value("row", 10).toInt();
    int col = read->value("col", 10).toInt();
    int mine = read->value("mine", 10).toInt();
    int leve = read->value("leve", Common::CUSOM_LEVE).toInt();
    read->endGroup();

    rowspinbox->setValue(row);
    colspinbox->setValue(col);
    minenumspinbox->setValue(mine);
}


void CustomGameDialog::writesettings()
{
    QSettings *write = new QSettings("TPZS", "MineSweeper");
    write->beginGroup("Current_row_col_mine_leve");
    write->setValue("row", rowspinbox->value());
    write->setValue("col", colspinbox->value());
    write->setValue("mine", minenumspinbox->value());
    write->setValue("leve", Common::CUSOM_LEVE);
    write->endGroup();
}


void CustomGameDialog::slot_accpetok()
{
    int row = rowspinbox->value();
    int col = colspinbox->value();
    int mine = minenumspinbox->value();
    emit signal_sendCustomset(row, col, mine);

    writesettings();
    close();
}
