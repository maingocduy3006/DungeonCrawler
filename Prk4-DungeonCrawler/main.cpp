#include "graphicalui.h"
#include "level.h"
#include "dungeoncrawler.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DungeonCrawler* d = new DungeonCrawler();
    d->play();
    //return 0;
    return a.exec();
}
