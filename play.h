#ifndef PLAY_H
#define PLAY_H

#include <QWidget>
#include<list.h>
#include<QTimer>
#include<QString>

namespace Ui {
    class Play;
}
class Play : public QWidget {
    Q_OBJECT

public:
    explicit Play(QWidget *parent = nullptr);
    ~Play();
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void GameInit();
    void timeOut();
    void CreateFood();
    void EatFood();
    void GameOver();
    struct Food food;
    struct Snake snake;
    bool Is_GameOver;
    bool Is_Press_Key;
    int IsStop;
    int score;
    int timer;
    float time;
private:
    Ui::Play *ui;
};

#endif // PLAY_H
