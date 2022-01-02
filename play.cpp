#include "play.h"
#include "ui_play.h"
#include"list.h"
#include<QPainter>
#include<QPushButton>
#include<QKeyEvent>
#include<QDebug>
#include<QLabel>
#include<QTimer>
#include<QMessageBox>
#include<gameover.h>
#include"mypushbutton.h"

Play::Play(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Play) {
    ui->setupUi(this);
    this->setFixedSize(800, 600);
    this->setWindowTitle("贪吃蛇");
    MyPushButton *Btn_start = new MyPushButton("重新开始");
    MyPushButton *Btn_stop = new MyPushButton("暂停游戏");
    Btn_start->setParent(this);
    Btn_start->setFixedSize(160, 50);
    Btn_start->move(590, 300);
    connect(Btn_start, &QPushButton::clicked, this, [=]() {
        if (IsStop) {
            Btn_stop->setText("暂停游戏");
            QTimer::singleShot(100, this, [=]() {
                GameInit();
                timer = startTimer(200);
            });
        } else {
            GameInit();
        }
        
    });
    
    Btn_stop->setParent(this);
    Btn_stop->setFixedSize(160, 50);
    Btn_stop->move(590, 370);
    connect(Btn_stop, &QPushButton::clicked, this, [=]() {
        switch (IsStop) {
            case 0:
                Btn_stop->setText("继续游戏");
                QTimer::singleShot(200, this, [=]() {
                    IsStop = 1;
                    killTimer(timer);
                });
                break;
            case 1:
                Btn_stop->setText("暂停游戏");
                QTimer::singleShot(200, this, [=]() {
                    IsStop = 0;
                    timer = startTimer(200);
                });
                break;
        }
    });
    
    MyPushButton *Btn_exit = new MyPushButton("退出游戏");
    Btn_exit->setParent(this);
    Btn_exit->setFixedSize(160, 50);
    Btn_exit->move(590, 440);
    connect(Btn_exit, &QPushButton::clicked, this, [=]() {
        Btn_exit->zoom1();
        Btn_exit->zoom2();
        QTimer::singleShot(500, this, [=]() {
            this->close();
        });
    });
    GameInit();
    timer = startTimer(200);
    
}

Play::~Play() {
    delete ui;
}

void Play::paintEvent(QPaintEvent *) {
    QPainter paint(this);
    paint.drawPixmap(0, 0, 800, 600, QPixmap(":/background.png"));
    paint.setPen(QPen(Qt::black));
    for (int i = 0; i < 21; i++) {
        paint.drawLine(25 * i + 50, 50, 25 * i + 50, 550);
        paint.drawLine(50, 25 * i + 50, 550, 25 * i + 50);
    }
    paint.drawRect(25, 50, 500, 500);
    paint.setBrush(Qt::red);
    paint.drawPixmap(food.fcd.x, food.fcd.y, 25, 25, QPixmap(":/food.png"));
    paint.setBrush(Qt::black);
    
    for (int i = 0; i < snake.len; i++) {
        paint.drawPixmap(snake.scd[i].x, snake.scd[i].y, 25, 25, QPixmap(":/circle.png"));
    }
    
    paint.setPen(QPen(Qt::black));
    paint.setFont(QFont("Times", 30, QFont::Bold));
    paint.drawText(240, 30, "分数:");
    paint.drawText(320, 30, QString::number(score));
    paint.drawText(40, 30, "时间:");
    paint.drawText(120, 30, QString::number(time, 'f', 2));
}

void Play::keyPressEvent(QKeyEvent *event) {
    if (Is_Press_Key) {
        return;
    } else {
        Is_Press_Key = true;
    }
    switch (event->key()) {
        case (Qt::Key_Up):
            if (snake.ch != 80) {
                snake.ch = 72;
            }
            break;
        case (Qt::Key_Down):
            if (snake.ch != 72) {
                snake.ch = 80;
            }
            break;
        case (Qt::Key_Left):
            if (snake.ch != 77) {
                snake.ch = 75;
            }
            break;
        case (Qt::Key_Right):
            if (snake.ch != 75) {
                snake.ch = 77;
            }
            break;
    }
}

void Play::keyReleaseEvent(QKeyEvent *) {
    QTimer::singleShot(10, [=]() {
        Is_Press_Key = false;
    });
}

void Play::GameInit() {
    snake.len = 3;
    snake.ch = 77;
    snake.scd[0].x = 150;
    snake.scd[0].y = 100;
    snake.scd[1].x = 125;
    snake.scd[1].y = 100;
    snake.scd[2].x = 100;
    snake.scd[2].y = 100;
    food.is_eat = true;
    Is_GameOver = false;
    Is_GameOver = false;
    score = 3;
    IsStop = 0;
    time = 0;
}

void Play::timeOut() {
    for (int i = snake.len - 1; i > 0; i--) {
        snake.scd[i].x = snake.scd[i - 1].x;
        snake.scd[i].y = snake.scd[i - 1].y;
    }
    
    switch (snake.ch) {
        case 72:
            snake.scd[0].y -= 25;
            break;
        case 80:
            snake.scd[0].y += 25;
            break;
        case 75:
            snake.scd[0].x -= 25;
            break;
        case 77:
            snake.scd[0].x += 25;
            break;
    }
    GameOver();
    if (!Is_GameOver) {
        update();
    } else {
        killTimer(timer);
        this->close();
        class GameOver *over = new class GameOver();
        over->show();
        delete this;
    }
    
}

void Play::timerEvent(QTimerEvent *) {
    
    time += 0.2;
    EatFood();
    if (food.is_eat) {
        CreateFood();
    }
    timeOut();
    
}

void Play::CreateFood() {
    int flag;
    while (1) {
        flag = 0;
        food.fcd.x = 50 + rand() % 25 * 25;
        food.fcd.y = 50 + rand() % 25 * 25;
        for (int i = 0; i < snake.len; i++) {
            if (food.fcd.x == snake.scd[i].x || food.fcd.y == snake.scd[i].y) {
                flag = 1;
                break;
            }
        }
        if (food.fcd.x < 50 || food.fcd.x >= 550 || food.fcd.y < 50 || food.fcd.y >= 550) {
            flag = 1;
        }
        if (flag) {
            continue;
        } else {
            food.is_eat = false;
            break;
        }
    }
}

void Play::EatFood() {
    if (snake.scd[0].x == food.fcd.x && snake.scd[0].y == food.fcd.y) {
        snake.len++;
        food.is_eat = true;
        score++;
    }
}

void Play::GameOver() {
    if (snake.scd[0].x < 50 || snake.scd[0].x > 525 || snake.scd[0].y < 50 || snake.scd[0].y > 525) {
        Is_GameOver = true;
    }
    for (int i = snake.len - 1; i > 0; i--) {
        if (snake.scd[0].x == snake.scd[i].x && snake.scd[0].y == snake.scd[i].y) {
            Is_GameOver = true;
        }
    }
}
