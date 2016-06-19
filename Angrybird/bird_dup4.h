#ifndef BIRD_DUP4_H
#define BIRD_DUP4_H


#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <bird.h>

#define BIRD_dup4_DENSITY 20.0f
#define BIRD_dup4_FRICTION 0.2f
#define BIRD_dup4_RESTITUTION 0.5f

class bird_dup4 : public Bird
{
public:
    bird_dup4(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);

    virtual void skill();

};


#endif // BIRD_DUP4_H
