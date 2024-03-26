#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>

namespace Ui {
class StartScreen;
}

class GraphicalUI;
class StartScreen : public QDialog
{
    Q_OBJECT

public:
    explicit StartScreen(GraphicalUI* Gui, QWidget *parent = nullptr);
    ~StartScreen();

    bool getHasClicked() const;

    void setHasClicked(bool newHasClicked);

    bool getWantToLoadGame() const;

public slots:
    void clickedNewGame();
    void clickedSaveGame();

private:
    Ui::StartScreen *ui;
    QPushButton *pushButton;
    GraphicalUI* gui;
    bool hasClicked;
    bool wantToLoadGame;
};

#endif // STARTSCREEN_H
