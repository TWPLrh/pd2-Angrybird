#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <Box2D/Box2D.h>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QTransform>
#include <QtMath>

class GameItem : public QObject{
    Q_OBJECT
public:
    GameItem(b2World *world);
    ~GameItem();
    b2Body* getBody();
    static void setGlobalSize(QSizeF worldsize, QSizeF windowsize);
    float getHealth();
    void setHealth(float health);
    char getType();
    QGraphicsPixmapItem g_pixmap;
public slots:
    void paint();
protected:
    b2Body *g_body;
    QSizeF g_size;
    b2World *g_world;
    float g_health;
    char g_type;
    static QSizeF g_worldsize, g_windowsize;
};

#endif // GAMEITEM_H
