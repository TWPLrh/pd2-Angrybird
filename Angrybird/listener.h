#ifndef LISTENER_H
#define LISTENER_H

#include "gameitem.h"

#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <bird.h>

class listener : public b2ContactListener
{
public:
    void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse);
    b2Body *bodyA;
    b2Body *bodyB;
    b2Body *bodyInfo_1;
    b2Body *bodyInfo_2;
    float impInfo;
};

#endif // LISTENER_H
