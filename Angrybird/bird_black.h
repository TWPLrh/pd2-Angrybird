#ifndef BIRD_BLACK_H
#define BIRD_BLACK_H

#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <bird.h>

#define BIRD_BLACK_DENSITY 20.0f
#define BIRD_BLACK_FRICTION 0.2f
#define BIRD_BLACK_RESTITUTION 0.5f

class bird_black : public Bird
{
public:
    bird_black(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);

    virtual void skill();

};

#endif // BLACKBIRD_H
