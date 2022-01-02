#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"list.h"
#include"play.h"
#include<QPainter>
#include<QPushButton>
#include<QKeyEvent>
#include<QDebug>
#include<QLabel>
#include<QTimer>
#include"mypushbutton.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setFixedSize(800, 600);
    this->setWindowTitle("贪吃蛇");
    MyPushButton *Btn_start = new MyPushButton("开始游戏");
    MyPushButton *Btn_exit = new MyPushButton("退出游戏");
    Btn_exit->setParent(this);
    Btn_start->setParent(this);
    Btn_start->setFixedSize(160, 50);
    Btn_start->setIconSize(QSize(200, 60));
    Btn_start->move(300, 400);
    Btn_exit->setFixedSize(160, 50);
    Btn_exit->setIconSize(QSize(200, 60));
    Btn_exit->move(300, 460);
    connect(Btn_exit, &QPushButton::clicked, [=]() {
        Btn_exit->zoom1();
        Btn_exit->zoom2();
        QTimer::singleShot(500, this, [=]() {
            this->close();
        });
    });
    
    connect(Btn_start, &QPushButton::clicked, [=]() {
        Btn_start->zoom1();
        Btn_start->zoom2();
        QTimer::singleShot(500, this, [=]() {
            Play *p = new Play;
            p->show();
            this->close();
        });
    });
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *) {
    
    QPainter paint(this);
    paint.setBrush(Qt::black);
    paint.drawPixmap(0, 0, 800, 600, QPixmap(":/background.png"));
    paint.drawPixmap(200, 20, 400, 150, QPixmap(":/snake2.png"));
}
