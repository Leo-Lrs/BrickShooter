#include "home_btn.h"

#include <QGraphicsTextItem>
#include <QKeyEvent>
#include <QBrush>
#include <QFont>



home_btn::home_btn(QString nom, QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    setRect(0,0,200,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkMagenta);
    setBrush(brush);

    text = new QGraphicsTextItem(nom,this);
    QFont title("Times",13, QFont::Bold);
    text->setFont(title);
    text->setDefaultTextColor(QColor(0xff, 0xff, 0xff, 0xff));
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos,yPos);

    setAcceptHoverEvents(true);
}


void home_btn::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
}

void home_btn::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::magenta);
    setBrush(brush);
}

void home_btn::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkMagenta);
    setBrush(brush);
}
