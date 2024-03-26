#include "graphicalui.h"
//#include "ui_graphicalui.h"
#include "ui_mainwindow.h"
#include "dungeoncrawler.h"
#include <QPushButton>
#include <QtTest/QTest>

GraphicalUI::GraphicalUI(DungeonCrawler* dg, QString path): AbstraktUI(), Controller(), dungeonCraw(dg), Path(path)
{
    insertQPixMap();

    startscreen = new class StartScreen(this);
    mainWindow = new class MainWindow(this);

    mainWindow->setButton();
    mainWindow->connectButtons();

    startscreen->show();
}

GraphicalUI::~GraphicalUI()
{
}

void GraphicalUI::draw(Level *level)
{
    mainWindow->draw(level);
}


char GraphicalUI::move()
{
    while(1){
        QTest::qWait(50);
        QCoreApplication::processEvents();
        qDebug() << "check";
        if(mainWindow->getSaveChanged()){
            mainWindow->setSaveChanged(false);
        }
        if(mainWindow->hasInputChanged()){
            mainWindow->setInputChanged(false);
            qDebug() << mainWindow->getLastInput();
            return mainWindow->getLastInput();
        }
    }
}

bool GraphicalUI::start()
{
    while(1){
        QTest::qWait(50);
        QCoreApplication::processEvents();
        qDebug() << "check";
        if(startscreen->getHasClicked()){
            startscreen->setHasClicked(false);
            return startscreen->getWantToLoadGame();
        }
    }
}

void GraphicalUI::insertQPixMap()
{
    insertArrow();
    insertChar();
    insertDoor();
    insertFloor();
    insertPortal();
    insertZombie();
    BloodyFrame = QPixmap(Path + "/textures/bloody_frame.png");
    NewGameButton = QPixmap(Path + "/textures/new_game_button.png");
    startScreenIm = QPixmap(Path + "/textures/startscreen.png");
    PitIm = QPixmap(Path + "/textures/pit.png");
    RampIm = QPixmap(Path + "/textures/ramp.png");
    SwichtIm = QPixmap(Path + "/textures/switch.png");
    WallIm = QPixmap(Path + "/textures/wall/wall1.png");
    LevelChangerIm = QPixmap(Path + "/textures2/levelchanger.png");
    ChestIm = QPixmap(Path + "/textures2/chest.png");
    LoadGameIm = QPixmap(Path + "/textures2/LoadGame.png");
}

void GraphicalUI::insertArrow()
{
    arrows.resize(9);
    arrows[0] = QPixmap(Path + "/textures/arrows/arrow_down_left.png");
    arrows[1] = QPixmap(Path + "/textures/arrows/arrow_down_right.png");
    arrows[2] = QPixmap(Path + "/textures/arrows/arrow_down.png");
    arrows[3] = QPixmap(Path + "/textures/arrows/arrow_left.png");
    arrows[4] = QPixmap(Path + "/textures/arrows/arrow_right.png");
    arrows[5] = QPixmap(Path + "/textures/arrows/arrow_skip.png");
    arrows[6] = QPixmap(Path + "/textures/arrows/arrow_up_left.png");
    arrows[7] = QPixmap(Path + "/textures/arrows/arrow_up_right.png");
    arrows[8] = QPixmap(Path + "/textures/arrows/arrow_up.png");
}

void GraphicalUI::insertChar()
{
    chars.resize(4,std::vector<QPixmap>(3));
    //add char back
    chars[0][0] = QPixmap(Path + "/textures/char/back/char_back_2.png");
    chars[0][1] = QPixmap(Path + "/textures/char/back/char_back_1.png");
    chars[0][2] = QPixmap(Path + "/textures/char/back/char_back_3.png");
    //add char front
    chars[1][0] = QPixmap(Path + "/textures/char/front/char_front_2.png");
    chars[1][1] = QPixmap(Path + "/textures/char/front/char_front_1.png");
    chars[1][2] = QPixmap(Path + "/textures/char/front/char_front_3.png");
    //add char left
    chars[2][0] = QPixmap(Path + "/textures/char/left/char_left_2.png");
    chars[2][1] = QPixmap(Path + "/textures/char/left/char_left_1.png");
    chars[2][2] = QPixmap(Path + "/textures/char/left/char_left_3.png");
    //add char right
    chars[3][0] = QPixmap(Path + "/textures/char/right/char_right_2.png");
    chars[3][1] = QPixmap(Path + "/textures/char/right/char_right_1.png");
    chars[3][2] = QPixmap(Path + "/textures/char/right/char_right_3.png");
}

void GraphicalUI::insertDoor()
{
    doors.resize(2);
    doors[0] = QPixmap(Path + "/textures/doors/door1.png");
    doors[1] = QPixmap(Path + "/textures/doors/door2.png");
}

void GraphicalUI::insertFloor()
{
    floors.resize(5);
    floors[0] = QPixmap(Path + "/textures/floor/floor1.png");
    floors[1] = QPixmap(Path + "/textures/floor/floor2.png");
    floors[2] = QPixmap(Path + "/textures/floor/floor3.png");
    floors[3] = QPixmap(Path + "/textures/floor/floor4.png");
    floors[4] = QPixmap(Path + "/textures/floor/floor5.png");
}

void GraphicalUI::insertPortal()
{
    portals.resize(3);
    portals[0] = QPixmap(Path + "/textures/portal/portal1.png");
    portals[1] = QPixmap(Path + "/textures/portal/portal2.png");
    portals[2] = QPixmap(Path + "/textures/portal/portal3.png");
}

void GraphicalUI::insertZombie()
{
    zombies.resize(2);
    zombies[0] = QPixmap(Path + "/textures/zombie/zombie_left.png");
    zombies[1] = QPixmap(Path + "/textures/zombie/zombie_right.png");
}

bool GraphicalUI::checkIfGameEnd(Level *level)
{
    return mainWindow->checkifGameEnd(level);
}

DungeonCrawler *GraphicalUI::getDungeonCrawler()
{
    return dungeonCraw;
}

QString GraphicalUI::getPath()
{
    return Path;
}

void GraphicalUI::setPath(QString path)
{
    Path = path;
}

void GraphicalUI::switchWindow()
{
    startscreen->hide();
    mainWindow->show();
}


