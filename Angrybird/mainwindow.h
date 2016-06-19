#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QPushButton>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <QMediaPlayer>
#include <iostream>

#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <brick.h>
#include <enemy.h>
#include <listener.h>
#include <bird_black.h>
#include <bird_blue.h>
#include <bird_yellow.h>
#include <bird_dup4.h>
#include <obstac.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void handleContact();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
    void buildbutton();

public slots:
    void ReStartButton();


signals:
    void quitGame();

private slots:
    void tick();
    void QUITSLOT();
private:
    QPushButton *restartbutton;
    QPushButton *quitbutton;
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;
    double x,y;
    Bird *bird_1;
    Bird *bird_2;
    Bird *bird_3;
    Bird *bird_4,*bird_dup;
    enemy *pig;
    bool launch;
    int n=0;
    listener* myContactListener;
    QMediaPlayer *player;
};

#endif // MAINWINDOW_H
