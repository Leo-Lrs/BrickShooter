#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "player.h"
#include "score.h"
#include "home_btn.h"
#include "gold.h"

class Game: public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget* parent=NULL);

    Player *getPlayer() const;
    Score *getScore() const;
    QTimer *getTimer() const;
    Gold *getGold() const;

    int getMoveEnnemi() const;
    int getMoveBullet() const;
    int getMovePlayer() const;

    void setMoveEnnemi(int value);
    void setMoveBullet(int value);
    void setMovePlayer(int value);

public slots:
    void start();
    void displayMainMenu();
    void createMainMenu();
    void displayMenuIG();
    void hideMenu();
    void destructStart();
    void displayEndGame();
    void hideBtnEndGame();
    void showUpgrade();
    void upgradeTir();
    void upgradeDefilement();
    void upgradeDeplacement();
    void pause();
    void resume();
    void achat_Tir();
    void achat_Defil();
    void achat_Player();
    void updateGold();
    void showInstruction();
    void returnMenuViaEndGame();

    int data_Txt(int x);
private :

    //Attributs
    QGraphicsScene * scene;
    Player * player;
    Score * score;
    QTimer * timer;
    Gold * gold;

    QGraphicsTextItem * titleText;
    QGraphicsTextItem * endGameText;
    QGraphicsTextItem * upgradeText;
    QGraphicsTextItem * goldEndText;
    QGraphicsTextItem * arrowText;
    QGraphicsTextItem * spaceText;
    QGraphicsTextItem * escapeText;

    QGraphicsPixmapItem * pictureArrow;
    QGraphicsPixmapItem * pictureSpaceBar;
    QGraphicsPixmapItem * pictureEsc;

    home_btn * playButton;
    home_btn * quitButton;
    home_btn * escButton;
    home_btn * replayButton;
    home_btn * upgradeButton;
    home_btn * upgradeTirButton;
    home_btn * upgradeDefilementButton;
    home_btn * upgradeDeplacementButton;
    home_btn * returnMenuButton;
    home_btn * resumeButton;
    home_btn * instructionButton;
    home_btn *returnMainMenuBtn;

    int moveEnnemi;
    int moveBullet;
    int movePlayer;
    int myGold = 0;
};

#endif // GAME_H
