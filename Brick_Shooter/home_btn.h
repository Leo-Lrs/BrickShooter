#ifndef HOME_BTN_H
#define HOME_BTN_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>


class home_btn:public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    home_btn(QString nom, QGraphicsItem* parent=NULL);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:
    void clicked();

private:
    QGraphicsTextItem* text;

};

#endif // HOME_BTN_H
