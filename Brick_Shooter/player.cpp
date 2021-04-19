#include "player.h"
#include "bullet.h"
#include "home_btn.h"
#include "game.h"
#include "commonenemy.h"
#include "rareenemy.h"
#include "veryrareenemy.h"
#include "extrarareenemy.h"

#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <iostream>

using namespace std;

extern Game * game;

Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    bulletsound = new QMediaPlayer();
    bulletsound->setMedia(QUrl("qrc:/sounds/laserpascher.wav"));

    setPixmap(QPixmap(":/images/player_dbz.png"));
}

void Player::go_Left()
{
    if (pos().x()>0)
    setPos(x()-game->getMovePlayer(),y());
}

void Player::go_Right()
{
    if (pos().x() + 30 < 750)
    setPos(x()+game->getMovePlayer(),y());
}

void Player::go_Shoot()
{
    Bullet * bullet = new Bullet();
    bullet->setPos(x()+25,y()-22);
    scene()->addItem(bullet);


    if (bulletsound->state() == QMediaPlayer::PlayingState){
        bulletsound->setPosition(0);
    }
    else if (bulletsound->state() == QMediaPlayer::StoppedState){
        bulletsound->play();
    }
    
}

void Player::cleanEnemies()
{
    int i = 0;

    for(auto enemy:getEnemies()){
        if(enemy->getIsDead()){
            enemy = nullptr;
            enemies.erase(enemies.begin()+i);
            delete enemy;
        }
    i++;
    }
}

vector<Enemy*> Player::getEnemies() const
{
    return enemies;
}


void Player::spawn()
{
    Enemy * enemy = nullptr;

    int randNumber = rand() % 100 + 1;
    if (randNumber <= 70){
        enemy = new CommonEnemy(this);
    }
    else if( randNumber > 70 && randNumber <= 90){
        enemy = new RareEnemy(this);
    }
    else if(randNumber > 90 && randNumber <= 95){
        enemy = new VeryRareEnemy(this);
    }
    else if(randNumber > 95){
        enemy = new Extrarareenemy(this);
    }
    enemies.push_back(enemy);
    scene()->addItem(enemy);
    cleanEnemies();
}

void Player::keyPressEvent(QKeyEvent *event)
{

    if (event->key() == Qt::Key_Escape){
        // Add Return to MainMenu
        game->displayMenuIG();
        game->pause();
    }

    if (event->key() == Qt::Key_Left){
        go_Left();
    }
    if (event->key() == Qt::Key_Right){
        go_Right();
    }
    if (event->key() == Qt::Key_Space){
        go_Shoot();
    }
}

Player::~Player()
{
}
