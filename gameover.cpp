#include "gameover.h"
#include "ui_gameover.h"
#include<QPainter>
#include<QPushButton>
#include"play.h"
#include"mypushbutton.h"

GameOver::GameOver(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameOver) {
    ui->setupUi(this);
    this->setWindowTitle("游戏结束");
    this->setFixedSize(800, 600);
    MyPushButton *Btn_Ok = new MyPushButton("重新开始");
    Btn_Ok->setParent(this);
    Btn_Ok->setFixedSize(160, 50);
    Btn_Ok->setIconSize(QSize(200, 60));
    Btn_Ok->move(300, 400);
    
    MyPushButton *Btn_Exit = new MyPushButton("退出游戏");
    Btn_Exit->setParent(this);
    Btn_Exit->setFixedSize(160, 50);
    Btn_Exit->setIconSize(QSize(200, 60));
    Btn_Exit->move(300, 460);
    connect(Btn_Ok, &QPushButton::clicked, this, [=]() {
        Btn_Ok->zoom1();
        Btn_Ok->zoom2();
        QTimer::singleShot(500, this, [=]() {
            Play *p = new Play;
            p->show();
            this->close();
        });
        
    });
    
    connect(Btn_Exit, &QPushButton::clicked, this, [=]() {
        Btn_Exit->zoom1();
        Btn_Exit->zoom2();
        QTimer::singleShot(500, this, [=]() {
            this->close();
        });
    });
}

GameOver::~GameOver() {
    delete ui;
}

void GameOver::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/background.png"), 0, 50, 800, 600);
    painter.drawPixmap(200, 80, 500, 200, QPixmap(":gameover.png"));
}
