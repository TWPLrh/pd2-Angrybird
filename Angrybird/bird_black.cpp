#include "bird_black.h"

bird_black::bird_black(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):Bird(x,y,radius,timer,pixmap,world,scene)
{
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSize(radius*2,radius*2);

    g_health = -1;

    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.bullet = true;
    bodydef.position.Set(x,y);
    bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);

    b2CircleShape bodyshape;
    bodyshape.m_radius = radius;

    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyshape;
    fixturedef.density = BIRD_BLACK_DENSITY;
    fixturedef.friction = BIRD_BLACK_FRICTION;
    fixturedef.restitution = BIRD_BLACK_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);

    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);
}

void bird_black::skill(){
    this->g_pixmap.setPixmap(QPixmap(":/image/bird_black.png").scaled(100,100));
    this->g_size = QSize(2.7f,2.7f);
    // change original fixture
    b2Fixture *originalFixture = this->getBody()->GetFixtureList();
    this->getBody()->DestroyFixture(originalFixture);
    this->getBody()->SetLinearVelocity(b2Vec2(0,-20));
    b2CircleShape bodyshape;
    bodyshape.m_radius = 2.0f;
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyshape;
    fixturedef.density = BIRD_DENSITY;
    fixturedef.friction = BIRD_FRICTION;
    fixturedef.restitution = BIRD_RESTITUTION;
    this->getBody()->CreateFixture(&fixturedef);
    this->getBody()->ResetMassData();

}

