#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    //enable the event Filter
    player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/image/123.mp3"));
    player->play();
    qApp->installEventFilter(this);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//disable scrollbar (horizontal)
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//disable scrollbar (vertical)
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::showEvent(QShowEvent *){
    //setting QGraphicsScene
    scene = new QGraphicsScene(0, 0, 960, 540);

    ui->graphicsView->setScene(scene);
    //create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    myContactListener = new listener();
    world->SetContactListener(myContactListener);
    //setting Size
    GameItem::setGlobalSize(QSizeF(32.0f, 18.0f),size());
    //create ground
    itemList.push_back(new Land(16.0f, 1.5f, 32.0f, 3.0f, QPixmap(":/image/down.png").scaled(960,90), world, scene));

    //non-collision background
    QGraphicsPixmapItem *up = new QGraphicsPixmapItem(QPixmap(":/image/up.png"));
    scene -> addItem(up);
    QGraphicsPixmapItem *bun = new QGraphicsPixmapItem(QPixmap(":/image/bun.png"));
    QGraphicsPixmapItem *bun2 = new QGraphicsPixmapItem(QPixmap(":/image/bun2.png"));

    this -> buildbutton();

    bun->setPos(130,334); bun->setScale(0.6); scene -> addItem(bun);

    launch = false;

    //create bird
      bird_1 = new Bird(4.0f, 6.2f, 1.0f, &timer, QPixmap(":/bird_red").scaled(60, 60), world, scene);
      bird_2 = new bird_black(1000.0f, 6.2f, 1.0f, &timer, QPixmap(":/image/bird_black").scaled(60, 60), world, scene);
      bird_3 = new bird_yellow(1000.0f, 6.2f, 1.0f, &timer, QPixmap(":/image/bird_yellow").scaled(60, 60), world, scene);
      bird_4 = new bird_blue(1000.0f, 6.2f, 1.0f, &timer, QPixmap(":/image/bird_blue").scaled(60, 60), world, scene);
      bird_dup = new bird_dup4(1000.0f, 6.2f, 1.0f, &timer, QPixmap(":/image/bird_blue").scaled(60, 60), world, scene);

      bird_1->getBody()->SetActive(0);
      bird_2->getBody()->SetActive(0);
      bird_3->getBody()->SetActive(0);
      bird_4->getBody()->SetActive(0);

      itemList.push_back(bird_1);
      itemList.push_back(bird_2);
      itemList.push_back(bird_3);
      itemList.push_back(bird_4);
      itemList.push_back(bird_dup);

    bun2->setPos(112,332); bun2->setScale(0.6); scene -> addItem(bun2);

    //create OBSTACLE

    itemList.push_back(new pillar(26.5f, 4.0f, 2, 2, &timer, QPixmap(":/image/block1").scaled(60, 60), world, scene));
    itemList.push_back(new pillar(26.5f, 4.0f, 2, 2, &timer, QPixmap(":/image/block1").scaled(60, 60), world, scene));
    itemList.push_back(new pillar(19.2f, 4.0f, 2, 2, &timer, QPixmap(":/image/block1").scaled(60, 60), world, scene));
    itemList.push_back(new pillar(19.2f, 4.0f, 2, 2, &timer, QPixmap(":/image/block1").scaled(60, 60), world, scene));

    itemList.push_back(new obstac(31.0f, 4.9f, 1, 3, &timer, QPixmap(":/image/wall").scaled(40, 100), world, scene));
    itemList.push_back(new obstac(31.0f, 8.5f, 1, 3, &timer, QPixmap(":/image/wall").scaled(40, 100), world, scene));
    itemList.push_back(new obstac(31.0f, 12.1f, 1, 3, &timer, QPixmap(":/image/wall").scaled(40, 100), world, scene));
    itemList.push_back(new obstac(31.0f, 16.1f, 1, 3, &timer, QPixmap(":/image/wall").scaled(40, 100), world, scene));
    itemList.push_back(new obstac(25.0f, 4.9f, 1, 3, &timer, QPixmap(":/image/wall").scaled(40, 100), world, scene));
    itemList.push_back(new obstac(17.0f, 4.9f, 1, 3, &timer, QPixmap(":/image/wall").scaled(40, 100), world, scene));

    //create ENEMY
    itemList.push_back(new enemy(19.2, 8, 1, &timer, QPixmap(":/image/pig").scaled(60, 60), world, scene));
    itemList.push_back(new enemy(26.2, 8, 1, &timer, QPixmap(":/image/pig").scaled(60, 60), world, scene));
    itemList.push_back(new enemy(29.2, 3, 1, &timer, QPixmap(":/image/pig").scaled(60, 60), world, scene));

    //timer
    connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
    connect(this, SIGNAL(quitGame()), this, SLOT(QUITSLOT()));
    timer.start(100/6);
}

bool MainWindow::eventFilter(QObject *, QEvent *event){

    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

    x = static_cast<QMouseEvent*>(event)->x()/30 ;
    y = 17 - static_cast<QMouseEvent*>(event)->y()/30;

    if(event->type() == QEvent::MouseButtonPress){

        launch = true;

        if(n==0){
            bird_1->getBody()->SetTransform(b2Vec2(x,y),0);
            bird_1->getBody()->SetActive(0);
        }
        else if(n==2){
            bird_2->getBody()->SetTransform(b2Vec2(x,y),0);
            bird_2->getBody()->SetActive(0);
        }
        else if(n==4){
            bird_3->getBody()->SetTransform(b2Vec2(x,y),0);
            bird_3->getBody()->SetActive(0);
        }
        else if(n==6){
            bird_4->getBody()->SetTransform(b2Vec2(x,y),0);
            bird_dup->getBody()->SetTransform(b2Vec2(x,y),0);
            bird_4->getBody()->SetActive(0);
            bird_dup->getBody()->SetActive(0);
        }
    }

    else if(event->type() == QEvent::MouseButtonRelease){

        launch = false;

        if(n == 0){
            bird_1->getBody()->SetActive(1);
            bird_1->setLinearVelocity(b2Vec2((4.0-x)*3.4,(6.2-y)*6.7));
        }
        else if(n == 2){
            bird_2->getBody()->SetActive(1);
            bird_2->setLinearVelocity(b2Vec2((4.0-x)*3.4,(6.2-y)*6.7));
            bird_1->getBody()->SetTransform(b2Vec2(1000,0),0);
        }
        else if(n == 4){
            bird_3->getBody()->SetActive(1);
            bird_3->setLinearVelocity(b2Vec2((4.0-x)*3.4,(6.2-y)*6.7));
            bird_2->getBody()->SetTransform(b2Vec2(1000,0),0);
        }
        else if(n == 6){
            bird_4->getBody()->SetActive(1);
            bird_4->setLinearVelocity(b2Vec2((4.0-x)*3.4,(6.2-y)*6.7));
            bird_dup->getBody()->SetActive(1);
            bird_dup->setLinearVelocity(b2Vec2((4.0-x)*3.4,(6.2-y)*6.7));
            bird_3->getBody()->SetTransform(b2Vec2(1000,0),0);
        }

        n += 1;
        std::cout << n << std::endl;
    }

    else if(event->type() == QEvent::MouseMove){

        if(launch == true){
        if(n == 0) bird_1->getBody()->SetTransform(b2Vec2(x,y),0);
        else if(n == 2) bird_2->getBody()->SetTransform(b2Vec2(x,y),0);
        else if(n == 4) bird_3->getBody()->SetTransform(b2Vec2(x,y),0);
        else if(n == 6) {
            bird_4->getBody()->SetTransform(b2Vec2(x,y),0);
            bird_dup->getBody()->SetTransform(b2Vec2(x,y),0);
            bird_dup->getBody()->SetActive(0);
            }
        }
    }
    if(keyEvent->key() == Qt::Key_Space){
        if(n==4) bird_2->skill();
        else if(n==6) bird_3->skill();
        else if(n==8) {
            bird_4->skill();
            bird_dup->skill();
        }
    }

    return false;
}

void MainWindow::handleContact(){

    GameItem* item = (GameItem*)myContactListener->bodyInfo_1->GetUserData();
    float healthLeft = (item->getHealth()) - myContactListener->impInfo;


    if (healthLeft<=0) {

        QPixmap *Pixmap_die = new QPixmap(QPixmap(":/image/dispear.png").scaled(60,60));
        item->g_pixmap.setPixmap(*Pixmap_die);
        item->getBody()->DestroyFixture(item->getBody()->GetFixtureList());
        }
}

void MainWindow::closeEvent(QCloseEvent *){
    //close event
    emit quitGame();
}

void MainWindow::tick(){
    world->Step(1.0/60.0,6,2);
    scene->update();
    handleContact();
}

void MainWindow::QUITSLOT(){
    //send output signal (for debug)
    this->close();
    std::cout << "Quit Game Signal receive !" << std::endl ;
}

void MainWindow::buildbutton(){
    // Create restart button
    restartbutton = new QPushButton();
    restartbutton->setText("RESTART");
    restartbutton->setFlat(true);
    restartbutton->setAutoFillBackground(true);
    restartbutton->setGeometry(QRect(20, 10, 100, 35));
    scene->addWidget(restartbutton);
    //otherSceneObjectList.push_back(restartbutton);

    // Create quit button
    quitbutton = new QPushButton();
    quitbutton->setText("QUIT");
    quitbutton->setFlat(true);
    quitbutton->setAutoFillBackground(true);
    quitbutton->setGeometry(QRect(20, 50, 100, 35));
    scene->addWidget(quitbutton);
    //otherSceneObjectList.push_back(quitbutton);

    // connect restartButton
    // delete button and call buildGameScene
    connect(restartbutton, SIGNAL(clicked()), this,SLOT(ReStartButton()));

    // connect quitButton
    // cout something
    connect(quitbutton, SIGNAL(clicked()), this,SLOT(QUITSLOT()));
}

void MainWindow::ReStartButton(){

    for(int j=0; j < itemList.size() ; j++){
        itemList[j]->deleteLater();
    }

    itemList.push_back(new Land(16.0f, 1.5f, 32.0f, 3.0f, QPixmap(":/image/down.png").scaled(960,90), world, scene));

    this -> buildbutton();

    bird_1 = new Bird(4.0f, 6.2f, 1.0f, &timer, QPixmap(":/bird_red").scaled(60, 60), world, scene);
    bird_2 = new bird_black(1000.0f, 6.2f, 1.0f, &timer, QPixmap(":/image/bird_black").scaled(60, 60), world, scene);
    bird_3 = new bird_yellow(1000.0f, 6.2f, 1.0f, &timer, QPixmap(":/image/bird_yellow").scaled(60, 60), world, scene);
    bird_4 = new bird_blue(1000.0f, 6.2f, 1.0f, &timer, QPixmap(":/image/bird_blue").scaled(60, 60), world, scene);
    bird_dup = new bird_dup4(1000.0f, 6.2f, 1.0f, &timer, QPixmap(":/image/bird_blue").scaled(60, 60), world, scene);

    bird_1->getBody()->SetActive(0);
    bird_2->getBody()->SetActive(0);
    bird_3->getBody()->SetActive(0);
    bird_4->getBody()->SetActive(0);

    itemList.push_back(bird_1);
    itemList.push_back(bird_2);
    itemList.push_back(bird_3);
    itemList.push_back(bird_4);
    itemList.push_back(bird_dup);

    itemList.push_back(new pillar(26.5f, 4.0f, 2, 2, &timer, QPixmap(":/image/block1").scaled(60, 60), world, scene));
    itemList.push_back(new pillar(26.5f, 4.0f, 2, 2, &timer, QPixmap(":/image/block1").scaled(60, 60), world, scene));
    itemList.push_back(new pillar(19.2f, 4.0f, 2, 2, &timer, QPixmap(":/image/block1").scaled(60, 60), world, scene));
    itemList.push_back(new pillar(19.2f, 4.0f, 2, 2, &timer, QPixmap(":/image/block1").scaled(60, 60), world, scene));

    itemList.push_back(new obstac(31.0f, 4.9f, 1, 3, &timer, QPixmap(":/image/wall").scaled(40, 100), world, scene));
    itemList.push_back(new obstac(31.0f, 8.5f, 1, 3, &timer, QPixmap(":/image/wall").scaled(40, 100), world, scene));
    itemList.push_back(new obstac(31.0f, 12.1f, 1, 3, &timer, QPixmap(":/image/wall").scaled(40, 100), world, scene));
    itemList.push_back(new obstac(31.0f, 16.1f, 1, 3, &timer, QPixmap(":/image/wall").scaled(40, 100), world, scene));
    itemList.push_back(new obstac(25.0f, 4.9f, 1, 3, &timer, QPixmap(":/image/wall").scaled(40, 100), world, scene));
    itemList.push_back(new obstac(17.0f, 4.9f, 1, 3, &timer, QPixmap(":/image/wall").scaled(40, 100), world, scene));

    //create ENEMY
    itemList.push_back(new enemy(19.2, 8, 1, &timer, QPixmap(":/image/pig").scaled(60, 60), world, scene));
    itemList.push_back(new enemy(26.2, 8, 1, &timer, QPixmap(":/image/pig").scaled(60, 60), world, scene));
    itemList.push_back(new enemy(29.2, 3, 1, &timer, QPixmap(":/image/pig").scaled(60, 60), world, scene));


    n = 0;


}
