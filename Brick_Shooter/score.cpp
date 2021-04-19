#include "score.h"
#include "game.h"
#include <QFont>

extern Game * game;

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent), score(0), compteur_gold(0)
{
    setPlainText(QString("Votre score est de : ") + QString::number(score));
    setDefaultTextColor(Qt::white);
    setFont(QFont("times",16));
}

void Score::increase()
{
    if(compteur_gold == 4)
    {
        compteur_gold = 0;
        game->getGold()->increase();
    }
    else{
        compteur_gold++;
    }

    score++;
    setPlainText(QString("Votre score est de : ") + QString::number(score));
    setDefaultTextColor(Qt::white);
    setFont(QFont("times",16));
}

int Score::getScore()
{
    return score;
}

int Score::getCompteur_gold() const
{
    return compteur_gold;
}


