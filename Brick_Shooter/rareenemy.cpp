#include "rareenemy.h"
#include <iostream>

using namespace std;

RareEnemy::RareEnemy(QGraphicsItem * parent)
{
    setPixmap(QPixmap(":/images/rare_briques.jpg"));

}

RareEnemy::~RareEnemy()
{
}
