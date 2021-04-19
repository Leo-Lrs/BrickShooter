#include <QFont>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

#include "gold.h"
#include "game.h"

using namespace std;

extern Game * game;

Gold::Gold(QGraphicsItem * parent)
{
    string nomFichier = "game.txt";

    vector<string> listeTxt;

    ifstream monFichierIn(nomFichier);
    if(monFichierIn.good())
    {
        qDebug() << "fichier";
        string str;
        while(getline(monFichierIn,str))
        {
            listeTxt.push_back(str);
        }

        setGold(stoi(listeTxt[0]));
        game->setMoveEnnemi(stoi(listeTxt[1]));
        game->setMoveBullet(stoi(listeTxt[2]));
        game->setMovePlayer(stoi(listeTxt[3]));

    }else{
        qDebug() << "pas fichier";

        gold = 0;
        game->setMoveEnnemi(5);
        game->setMoveBullet(10);
        game->setMovePlayer(20);

        ofstream monFichierOut(nomFichier);
        monFichierOut << gold << endl;
        monFichierOut << game->getMoveEnnemi() << endl;
        monFichierOut << game->getMoveBullet() << endl;
        monFichierOut << game->getMovePlayer() << endl;
        qDebug() << "fichier écrit";
    }

    setPlainText(QString("Gold : ") + QString::number(gold));
    setDefaultTextColor(Qt::white);
    setFont(QFont("times",16));
}

int Gold::getGold() const
{
    return gold;
}

void Gold::setGold(int value)
{
    gold = value;
}

void Gold::increase()
{
    gold += 1;
    setPlainText(QString("gold : ") + QString::number(gold));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",16));
}
