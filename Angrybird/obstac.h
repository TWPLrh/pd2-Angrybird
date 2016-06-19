#ifndef OBSTAC_H
#define OBSTAC_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define BRICK_DENSITY 20.0f
#define BRICK_FRICTION 0.2f
#define BRICK_RESTITUTION 0.5f

class obstac : public GameItem
{
public:
    obstac(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
};
#endif // OBSTAC_H
