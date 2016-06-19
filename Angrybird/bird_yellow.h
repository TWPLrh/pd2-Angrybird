#ifndef BIRD_YELLOW_H
#define BIRD_YELLOW_H

#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <bird.h>

#define BIRD_YELLOW_DENSITY 20.0f
#define BIRD_YELLOW_FRICTION 0.2f
#define BIRD_YELLOW_RESTITUTION 0.5f

class bird_yellow : public Bird
{
public:
    bird_yellow(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);

    virtual void skill();
};

#endif // YELBIRD_H
