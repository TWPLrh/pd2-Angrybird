#include "listener.h"


void listener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{
     bodyA = contact->GetFixtureA()->GetBody();
     bodyB = contact->GetFixtureB()->GetBody();
     GameItem* itemA = (GameItem*)bodyA->GetUserData();
     float healthA = itemA->getHealth();
     GameItem* itemB = (GameItem*)bodyB->GetUserData();
     float healthB = itemB->getHealth();

     if(healthA > 0 && healthB < 0){
     bodyInfo_1 = bodyA;
     bodyInfo_2 = NULL;
     impInfo = impulse->normalImpulses[0];
}
     if(healthB > 0 && healthA < 0){
         bodyInfo_1 = bodyB;
         bodyInfo_2 = NULL;
         impInfo = impulse->normalImpulses[0];
     }

     if(healthA > 0 && healthB > 0){
         bodyInfo_1 = bodyA;
         bodyInfo_2 = bodyB;
         impInfo = impulse->normalImpulses[0];

     }
}
