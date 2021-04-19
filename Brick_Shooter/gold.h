#ifndef GOLD_H
#define GOLD_H

#include <QGraphicsTextItem>

class Gold: public QGraphicsTextItem{
public:
    Gold(QGraphicsItem * parent=NULL);

    int getGold() const;

    void setGold(int value);
    void increase();

private:
    int gold;


};
#endif // GOLD_H
