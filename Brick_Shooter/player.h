#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QMediaPlayer>
#include <QGraphicsItem>
#include "enemy.h"
#include "bullet.h"

using namespace std;

class Player:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Player(QGraphicsItem * parent=NULL);
    ~Player();

    void go_Left();
    void go_Right();
    void go_Shoot();
    void cleanEnemies();

    vector<Enemy*> getEnemies() const;

public slots:
    void spawn();
    void keyPressEvent(QKeyEvent * event);


private:
    vector <Enemy*> enemies;

    QMediaPlayer * bulletsound;
};

#endif // PLAYER_H
