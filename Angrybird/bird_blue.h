#ifndef BIRD_BLUE_H
#define BIRD_BLUE_H

#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <bird.h>

#define BIRD_BLUE_DENSITY 20.0f
#define BIRD_BLUE_FRICTION 0.2f
#define BIRD_BLUE_RESTITUTION 0.5f

class bird_blue : public Bird
{
public:
    bird_blue(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);

    virtual void skill();

};

#endif // WHITEBIRD_H
