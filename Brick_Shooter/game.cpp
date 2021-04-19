#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QMediaPlayer>
#include <QBrush>
#include <QString>
#include <QImage>
#include <QKeyEvent>
#include <QDebug>
#include <iostream>
#include <fstream>
#include <string>


#include "game.h"
#include "enemy.h"
#include "player.h"
#include "home_btn.h"
#include "gold.h"

using namespace std;

Game::Game(QWidget *parent)
{
    string nomFichier = "game.txt";

    vector<string> listeTxt;

    ifstream monFichierIn(nomFichier);
    if(monFichierIn.is_open())
    {
        if(monFichierIn.good())
        {
            qDebug() <<"trouve fichier";
            string str;
            while(getline(monFichierIn,str))
            {
                listeTxt.push_back(str);
            }

            myGold = data_Txt(0);
            moveEnnemi = stoi(listeTxt[1]);
            moveBullet = stoi(listeTxt[2]);
            movePlayer = stoi(listeTxt[3]);
        }
    }else{
        qDebug() <<"trouve pas fichier";
        string nomFichier = "game.txt";
        ofstream monFichierOut(nomFichier);
        monFichierOut << 0 << endl;
        monFichierOut << 8 << endl;
        monFichierOut << 10  << endl;
        monFichierOut << 20 << endl;
        qDebug() <<"créer fichier";
    }
    qDebug() <<"continue";

    //Create la scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,900);
    setBackgroundBrush(QBrush(QImage(":/images/background.jpg")));
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,900);
    qDebug() <<"continue";

    createMainMenu();
    qDebug() <<"continue pas car pd veut pas écrire";

    displayMainMenu();
}

void Game::createMainMenu()
{
    titleText = new QGraphicsTextItem(QString("DBZ Shooter"));
    QFont titleFont("Times",50, QFont::Bold);
    titleText->setFont(titleFont);
    titleText->setDefaultTextColor(QColor(0xff, 0xff, 0xff, 0xff));
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 110;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    // create the play button
    playButton = new home_btn(QString("Play"));
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 275;
    playButton->setPos(bxPos,byPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(start()));
    connect(playButton,SIGNAL(clicked()),this,SLOT(hideMenu()));
    scene->addItem(playButton);

    // create the upgrade button
    upgradeButton = new home_btn(QString("Upgrade"));
    int uxPos = this->width()/2 - upgradeButton->boundingRect().width()/2;
    int uyPos = 350;
    upgradeButton->setPos(uxPos,uyPos);
    scene->addItem(upgradeButton);
    connect(upgradeButton,SIGNAL(clicked()),this,SLOT(showUpgrade()));

    // create the instruction button
    instructionButton = new home_btn(QString("Instruction"));
    int nxPos = this->width()/2 - instructionButton->boundingRect().width()/2;
    int nyPos = 425;
    instructionButton->setPos(nxPos,nyPos);
    connect(instructionButton,SIGNAL(clicked()),this,SLOT(showInstruction()));
    scene->addItem(instructionButton);

    // create the quit button
    quitButton = new home_btn(QString("Quit"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 500;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quitButton);

    // Le btn escape
    escButton = new home_btn(QString("Return"));
    int axPos = this->width()/2 - escButton->boundingRect().width()/2;
    int ayPos = 350;
    escButton->setPos(axPos,ayPos);
    scene->addItem(escButton);

    connect(escButton,SIGNAL(clicked()),this,SLOT(updateGold()));
    connect(escButton,SIGNAL(clicked()),this,SLOT(displayMainMenu()));
    connect(escButton,SIGNAL(clicked()),this,SLOT(destructStart()));

    // Le btn pour reprendre la partie en cours
    resumeButton = new home_btn(QString("Resume"));
    int gxPos = this->width()/2 - resumeButton->boundingRect().width()/2;
    int gyPos = 420;
    resumeButton->setPos(gxPos,gyPos);
    connect(resumeButton,SIGNAL(clicked()),this,SLOT(displayMainMenu()));
    connect(resumeButton,SIGNAL(clicked()),this,SLOT(resume()));
    connect(resumeButton,SIGNAL(clicked()),this,SLOT(hideMenu()));
    scene->addItem(resumeButton);

    // Create Title Upgrade
    upgradeText = new QGraphicsTextItem(QString("Upgrade"));
    upgradeText->setDefaultTextColor(QColor(0xff, 0xff, 0xff, 0xff));
    upgradeText->setFont(titleFont);
    int wxPos = this->width()/2 - upgradeText->boundingRect().width()/2;
    int wyPos = 100;
    upgradeText->setPos(wxPos,wyPos);
    scene->addItem(upgradeText);

    // create the vit tir button
    upgradeTirButton = new home_btn(QString("Tir = 10 Golds "));
    int xxPos = this->width()/2 - upgradeTirButton->boundingRect().width()/2;
    int xyPos = 250;
    upgradeTirButton->setPos(xxPos,xyPos);
    scene->addItem(upgradeTirButton);
    connect(upgradeTirButton,SIGNAL(clicked()),this,SLOT(achat_Tir()));


    // create the vit defilement button
    upgradeDefilementButton = new home_btn(QString("Défilement = 40 Golds "));
    int zxPos = this->width()/2 - upgradeDefilementButton->boundingRect().width()/2;
    int zyPos = 325;
    upgradeDefilementButton->setPos(zxPos,zyPos);
    scene->addItem(upgradeDefilementButton);
    connect(upgradeDefilementButton,SIGNAL(clicked()),this,SLOT(achat_Defil()));

    // create the vit deplacement button
    upgradeDeplacementButton = new home_btn(QString("Déplacement = 50 Golds "));
    int exPos = this->width()/2 - upgradeDeplacementButton->boundingRect().width()/2;
    int eyPos = 400;
    upgradeDeplacementButton->setPos(exPos,eyPos);
    scene->addItem(upgradeDeplacementButton);
    connect(upgradeDeplacementButton,SIGNAL(clicked()),this,SLOT(achat_Player()));

    // create return to menu
    returnMenuButton = new home_btn(QString("Retour"));
    int rxPos = this->width()/2 - returnMenuButton->boundingRect().width()/2;
    int ryPos = 500;
    returnMenuButton->setPos(rxPos,ryPos);
    connect(returnMenuButton,SIGNAL(clicked()),this,SLOT(displayMainMenu()));
    scene->addItem(returnMenuButton);

    // number de GOLD pour le mekton
    goldEndText = new QGraphicsTextItem(QString("Gold : ") + QString::number(data_Txt(0)));
    QFont endFont("comic sans",25);
    goldEndText->setFont(endFont);
    goldEndText->setDefaultTextColor(QColor(0xff, 0xff, 0xff, 0xff));
    goldEndText->setFont(endFont);
    int dxPos = this->width()/2 - goldEndText->boundingRect().width()/2;
    int dyPos = 178;
    goldEndText->setPos(dxPos,dyPos);
    scene->addItem(goldEndText);

    // create picture arrow in instruction
    pictureArrow = new QGraphicsPixmapItem();
    pictureArrow->setPixmap(QPixmap(":/images/key_bind.png"));
    int aaxPos = 50;
    int aayPos = 250;
    pictureArrow->setPos(aaxPos,aayPos);
    scene->addItem(pictureArrow);

    // create picture space bar in instruction
    pictureSpaceBar = new QGraphicsPixmapItem();
    pictureSpaceBar->setPixmap(QPixmap(":/images/space_bar.png"));
    int abxPos = 330;
    int abyPos = 305;
    pictureSpaceBar->setPos(abxPos,abyPos);
    scene->addItem(pictureSpaceBar);

    // create picture Escape in instruction
    pictureEsc = new QGraphicsPixmapItem();
    pictureEsc->setPixmap(QPixmap(":/images/escape_bind.png"));
    int acxPos = 530;
    int acyPos = 273;
    pictureEsc->setPos(acxPos,acyPos);
    scene->addItem(pictureEsc);

    // Flèche pour aller droite - gauche
    arrowText = new QGraphicsTextItem(QString(" Gauche <--> Droite "));
    arrowText->setFont(titleFont);
    arrowText->setDefaultTextColor(QColor(0xff, 0xff, 0xff, 0xff));
    QFont arrowTitle("comic sans",20);
    arrowText->setFont(arrowTitle);
    int bbxPos = 20;
    int bbyPos = 180;
    arrowText->setPos(bbxPos,bbyPos);
    scene->addItem(arrowText);

    // Space bar pour tirer
    spaceText = new QGraphicsTextItem(QString("Tirer"));
    spaceText->setFont(titleFont);
    spaceText->setDefaultTextColor(QColor(0xff, 0xff, 0xff, 0xff));
    spaceText->setFont(arrowTitle);
    int bcxPos = 350;
    int bcyPos = 180;
    spaceText->setPos(bcxPos,bcyPos);
    scene->addItem(spaceText);

    // Escape pour faire pause
    escapeText = new QGraphicsTextItem(QString("Pause"));
    escapeText->setFont(titleFont);
    escapeText->setDefaultTextColor(QColor(0xff, 0xff, 0xff, 0xff));
    escapeText->setFont(arrowTitle);
    int bdxPos = 565;
    int bdyPos = 180;
    escapeText->setPos(bdxPos,bdyPos);
    scene->addItem(escapeText);
}

void Game::displayMainMenu()
{
    escButton->hide();
    resumeButton->hide();

    titleText->show();
    playButton->show();
    quitButton->show();
    upgradeButton->show();


    upgradeText->hide();
    upgradeTirButton->hide();
    upgradeDefilementButton->hide();
    upgradeDeplacementButton->hide();
    returnMenuButton->hide();
    goldEndText->hide();
    instructionButton->show();

    pictureArrow->hide();
    pictureSpaceBar->hide();
    pictureEsc->hide();
    arrowText->hide();
    spaceText->hide();
    escapeText->hide();
}

void Game::displayMenuIG()
{
    escButton->show();
    resumeButton->show();

    titleText->hide();
    playButton->hide();
    quitButton->hide();
    upgradeButton->hide();

    upgradeText->hide();
    upgradeTirButton->hide();
    upgradeDefilementButton->hide();
    upgradeDeplacementButton->hide();
    returnMenuButton->hide();
    goldEndText->hide();
    instructionButton->hide();


    pictureArrow->hide();
    pictureSpaceBar->hide();
    pictureEsc->hide();
    arrowText->hide();
    spaceText->hide();
    escapeText->hide();
}

void Game::hideMenu()
{
    escButton->hide();
    resumeButton->hide();

    titleText->hide();
    playButton->hide();
    quitButton->hide();
    upgradeButton->hide();

    upgradeText->hide();
    upgradeTirButton->hide();
    upgradeDefilementButton->hide();
    upgradeDeplacementButton->hide();
    returnMenuButton->hide();
    goldEndText->hide();
    instructionButton->hide();


    pictureArrow->hide();
    pictureSpaceBar->hide();
    pictureEsc->hide();
    arrowText->hide();
    spaceText->hide();
    escapeText->hide();
}

void Game::hideBtnEndGame()
{
    escButton->hide();
    resumeButton->hide();

    titleText->hide();
    playButton->hide();
    quitButton->hide();
    upgradeButton->hide();
    endGameText->hide();
    replayButton->hide();

    upgradeText->hide();
    upgradeTirButton->hide();
    upgradeDefilementButton->hide();
    upgradeDeplacementButton->hide();
    returnMenuButton->hide();
    goldEndText->hide();
    instructionButton->hide();
    returnMainMenuBtn->hide();


    pictureArrow->hide();
    pictureSpaceBar->hide();
    pictureEsc->hide();
    arrowText->hide();
    spaceText->hide();
    escapeText->hide();
}

void Game::displayEndGame()
{

    scene->clear();

    // Create Title END
    endGameText = new QGraphicsTextItem(QString("Game Over"));
    QFont titleFont("comic sans",50);
    endGameText->setFont(titleFont);
    endGameText->setDefaultTextColor(QColor(0xff, 0xff, 0xff, 0xff));
    int uxPos = this->width()/2 - endGameText->boundingRect().width()/2;
    int uyPos = 150;
    endGameText->setPos(uxPos,uyPos);
    scene->addItem(endGameText);

    // create le END button
    replayButton = new home_btn(QString("Play"));
    int ixPos = this->width()/2 - replayButton->boundingRect().width()/2;
    int iyPos = 275;
    replayButton->setPos(ixPos,iyPos);
    connect(replayButton,SIGNAL(clicked()),this,SLOT(start()));
    connect(replayButton,SIGNAL(clicked()),this,SLOT(createMainMenu()));
    connect(replayButton,SIGNAL(clicked()),this,SLOT(hideBtnEndGame()));
    scene->addItem(replayButton);

    // create return to menu
    returnMainMenuBtn = new home_btn(QString("Retour au menu"));
    int rxPos = this->width()/2 - returnMainMenuBtn->boundingRect().width()/2;
    int ryPos = 350;
    returnMainMenuBtn->setPos(rxPos,ryPos);
    connect(returnMainMenuBtn,SIGNAL(clicked()),this,SLOT(returnMenuViaEndGame()));
    scene->addItem(returnMainMenuBtn);
}

void Game::showUpgrade()
{
    escButton->hide();
    titleText->hide();
    playButton->hide();
    quitButton->hide();
    upgradeButton->hide();

    upgradeText->show();
    upgradeTirButton->show();
    upgradeDefilementButton->show();
    upgradeDeplacementButton->show();
    returnMenuButton->show();
    goldEndText->show();
    instructionButton->hide();


    pictureArrow->hide();
    pictureSpaceBar->hide();
    pictureEsc->hide();
    arrowText->hide();
    spaceText->hide();
    escapeText->hide();
}

void Game::showInstruction()
{
    escButton->hide();
    titleText->hide();
    playButton->hide();
    quitButton->hide();
    upgradeButton->hide();

    upgradeText->hide();
    upgradeTirButton->hide();
    upgradeDefilementButton->hide();
    upgradeDeplacementButton->hide();
    returnMenuButton->show();
    goldEndText->hide();
    instructionButton->hide();


    pictureArrow->show();
    pictureSpaceBar->show();
    pictureEsc->show();
    arrowText->show();
    spaceText->show();
    escapeText->show();
}

void Game::start()
{
    //Create + Add item dans la scene
    player = new Player();
    player->setPos(400,800);

    gold = new Gold();
    gold->setPos(gold->x(),gold->y()+24);
    scene->addItem(gold);

    //Mise en place du score
    score = new Score();
    score->setPos(score->x(),score->y());
    scene->addItem(score);

    // Faire spawn les ennemis
    timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),player,SLOT(spawn()));

    timer->start(1500);

    //Permettre au player d'être " focus "
    scene->addItem(player);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
}

void Game::destructStart()
{
    scene->removeItem(player);
    delete player;
    scene->removeItem(score);
    delete score;

    scene->clear();
    createMainMenu();
    displayMainMenu();
}

Score *Game::getScore() const
{
    return score;
}

Player *Game::getPlayer() const
{
    return player;
}

void Game::pause()
{
    timer->stop();

    for(auto enemy:player->getEnemies()){
        enemy->pause();
    }
}

void Game::resume()
{
    timer->start(1000);

    for(auto enemy:player->getEnemies()){
        enemy->resume();
    }
    player->setFocus();
}

int Game::data_Txt(int x)
{
    string nomFichier = "game.txt";

    vector<string> listeTxt;

    ifstream monFichierIn(nomFichier);
    string str;
    while(getline(monFichierIn,str))
    {
        listeTxt.push_back(str);
    }

    return stoi(listeTxt[x]);
}

void Game::returnMenuViaEndGame()
{
    endGameText->hide();
    replayButton->hide();
    returnMainMenuBtn->hide();
    createMainMenu();
    displayMainMenu();
}

Gold *Game::getGold() const
{
    return gold;
}

void Game::upgradeTir()
{
    moveBullet +=1;
    myGold -= 10;

    string nomFichier = "game.txt";

    ofstream monFichierOut(nomFichier);
    monFichierOut << myGold << endl;
    monFichierOut << getMoveEnnemi() << endl;
    monFichierOut << getMoveBullet() << endl;
    monFichierOut << getMovePlayer() << endl;
}

void Game::achat_Tir()
{
    if(data_Txt(0) > 9){
        if(data_Txt(2) < 35){
        delete goldEndText;
        upgradeTir();
        goldEndText = new QGraphicsTextItem(QString("Gold : ") + QString::number(data_Txt(0)));
        QFont titleFont("comic sans",25);
        goldEndText->setFont(titleFont);
        goldEndText->setDefaultTextColor(QColor(0xff, 0xff, 0xff, 0xff));
        int dxPos = this->width()/2 - goldEndText->boundingRect().width()/2;
        int dyPos = 178;
        goldEndText->setPos(dxPos,dyPos);
        scene->addItem(goldEndText);
        }
    }
}

void Game::upgradeDefilement()
{
    moveEnnemi -=1;
    myGold -= 40;

    string nomFichier = "game.txt";

    ofstream monFichierOut(nomFichier);
    monFichierOut << myGold << endl;
    monFichierOut << getMoveEnnemi() << endl;
    monFichierOut << getMoveBullet() << endl;
    monFichierOut << getMovePlayer() << endl;

}

void Game::achat_Defil()
{
    if(data_Txt(0) > 39){
        if(data_Txt(1) > 1){
        delete goldEndText;
        upgradeDefilement();
        goldEndText = new QGraphicsTextItem(QString("Gold : ") + QString::number(data_Txt(0)));
        QFont titleFont("comic sans",25);
        goldEndText->setFont(titleFont);
        goldEndText->setDefaultTextColor(QColor(0xff, 0xff, 0xff, 0xff));
        int dxPos = this->width()/2 - goldEndText->boundingRect().width()/2;
        int dyPos = 178;
        goldEndText->setPos(dxPos,dyPos);
        scene->addItem(goldEndText);
        }
    }
}

void Game::upgradeDeplacement()
{
    movePlayer +=2;
    myGold -= 50;

    string nomFichier = "game.txt";

    ofstream monFichierOut(nomFichier);
    monFichierOut << myGold << endl;
    monFichierOut << getMoveEnnemi() << endl;
    monFichierOut << getMoveBullet() << endl;
    monFichierOut << getMovePlayer() << endl;
}

void Game::achat_Player()
{
    if(data_Txt(0) > 49){
        if(data_Txt(3) < 39){
        delete goldEndText;
        upgradeDeplacement();
        goldEndText = new QGraphicsTextItem(QString("Gold : ") + QString::number(data_Txt(0)));
        QFont titleFont("comic sans",25);
        goldEndText->setFont(titleFont);
        goldEndText->setDefaultTextColor(QColor(0xff, 0xff, 0xff, 0xff));
        int dxPos = this->width()/2 - goldEndText->boundingRect().width()/2;
        int dyPos = 178;
        goldEndText->setPos(dxPos,dyPos);
        scene->addItem(goldEndText);
        }
    }
}

void Game::updateGold()
{
    int a = data_Txt(1);
    int b = data_Txt(2);
    int c = data_Txt(3);
    string nomFichier = "game.txt";

    ofstream monFichierOut(nomFichier);
    monFichierOut << gold->getGold() << endl;
    monFichierOut << a << endl;
    monFichierOut << b << endl;
    monFichierOut << c << endl;
}

int Game::getMovePlayer() const
{
    return movePlayer;
}

void Game::setMovePlayer(int value)
{
    movePlayer = value;
}

int Game::getMoveBullet() const
{
    return moveBullet;
}

void Game::setMoveBullet(int value)
{
    moveBullet = value;
}

int Game::getMoveEnnemi() const
{
    return moveEnnemi;
}

void Game::setMoveEnnemi(int value)
{
    moveEnnemi = value;
}

QTimer *Game::getTimer() const
{
    return timer;
}
