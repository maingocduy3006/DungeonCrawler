#ifndef GRAPHICALUI_H
#define GRAPHICALUI_H

#include "abstraktui.h"
#include "controller.h"
#include "startscreen.h"
#include "mainwindow.h"
#include <string>
#include <QPixmap>
#include <vector>

namespace Ui {
class GraphicalUI;
}

class DungeonCrawler;
class GraphicalUI : public AbstraktUI, public Controller
{
public:
    explicit GraphicalUI(DungeonCrawler* dg, QString path);
    ~GraphicalUI();

    QPixmap BloodyFrame;
    QPixmap startScreenIm;
    QPixmap NewGameButton;
    QPixmap PitIm;
    QPixmap RampIm;
    QPixmap SwichtIm;
    QPixmap WallIm;
    QPixmap LevelChangerIm;
    QPixmap ChestIm;
    QPixmap LoadGameIm;
    std::vector<QPixmap> arrows;
    std::vector<std::vector<QPixmap>> chars;
    std::vector<QPixmap> doors;
    std::vector<QPixmap> floors;
    std::vector<QPixmap> portals;
    std::vector<QPixmap> zombies;

    void draw(Level* level) override;
    char move() override;

    void switchWindow();

    bool start();

    void insertQPixMap();
    void insertArrow();
    void insertChar();
    void insertDoor();
    void insertFloor();
    void insertPortal();
    void insertZombie();

    bool checkIfGameEnd(Level *level);

    DungeonCrawler* getDungeonCrawler();
    QString getPath();
    void setPath(QString path);
private:
    StartScreen *startscreen;
    MainWindow* mainWindow;
    DungeonCrawler* dungeonCraw;
    QString Path;
};

#endif // GRAPHICALUI_H
