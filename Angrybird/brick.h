#ifndef BRICK_H
#define BRICK_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define BRICK_DENSITY 20.0f
#define BRICK_FRICTION 0.2f
#define BRICK_RESTITUTION 0.5f

class pillar : public GameItem
{
public:
    pillar(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
};

#endif // PILLAR_H
