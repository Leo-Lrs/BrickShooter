#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include <vector>

using namespace std;

class Bullet: public QObject, public QGraphicsPixmapItem
{

Q_OBJECT

public:
    Bullet(QGraphicsItem * parent=NULL);
    ~Bullet();

    void pause();
    void resume();

    void upVitSpeed();
    void upVitSpeed2();
    void upVitSpeed3();

    QTimer * timer;

public slots:
    void move();

};

#endif // BULLET_H
