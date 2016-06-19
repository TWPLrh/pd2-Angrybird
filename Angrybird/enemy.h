#ifndef ENEMY_H
#define ENEMY_H

#define ENEMY_DENSITY 10.0f
#define ENEMY_FRICTION 0.2f
#define ENEMY_RESTITUTION 0.5f

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

class enemy:public GameItem
{
public:
    enemy(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
};

#endif // ENEMY_H
