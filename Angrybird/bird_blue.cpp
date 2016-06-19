#include "bird_blue.h"

bird_blue::bird_blue(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):Bird(x,y,radius,timer,pixmap,world,scene)
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
    fixturedef.density = BIRD_BLUE_DENSITY;
    fixturedef.friction = BIRD_BLUE_FRICTION;
    fixturedef.restitution = BIRD_BLUE_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);

    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);
}

void bird_blue::skill(){
    this->g_pixmap.setPixmap(QPixmap(":/image/bird_blue.png").scaled(42,42));
    this->g_size = QSize(1.0f,1.0f);
    // change original fixture
    b2Fixture *originalFixture = this->getBody()->GetFixtureList();
    this->setLinearVelocity(b2Vec2(15,-3));
    this->getBody()->DestroyFixture(originalFixture);
    b2CircleShape bodyshape;
    bodyshape.m_radius = 1.0f;
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyshape;
    fixturedef.density = BIRD_DENSITY;
    fixturedef.friction = BIRD_FRICTION;
    fixturedef.restitution = BIRD_RESTITUTION;
    this->getBody()->CreateFixture(&fixturedef);
    this->getBody()->ResetMassData();
}
