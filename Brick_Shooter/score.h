#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

class Score: public QGraphicsTextItem{
public:
    Score(QGraphicsItem * parent=NULL);
    void increase();
    int getScore();
    int getCompteur_gold() const;

private:
    int score;
    int compteur_gold;
    void increaseGold();
};

#endif // SCORE_H
