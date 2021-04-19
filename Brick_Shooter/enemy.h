#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class Enemy: public QObject, public QGraphicsPixmapItem
{

Q_OBJECT

public:
    Enemy(QGraphicsItem * parent=NULL);
    ~Enemy();

    void pause();
    void resume();

    bool getIsDead() const;
    void setIsDead(bool value);

public slots:
    void move();

private:
    QTimer * timerTest;

    bool isDead=false;
};


#endif // ENEMY_H
