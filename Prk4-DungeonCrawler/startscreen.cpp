#include "startscreen.h"
#include "ui_startscreen.h"
#include "graphicalui.h"

StartScreen::StartScreen(GraphicalUI* Gui, QWidget *parent):
    QDialog(parent),
    ui(new Ui::StartScreen),
    gui(Gui),
    hasClicked(false)
{
    ui->setupUi(this);
    ui->label->setStyleSheet("background-color: black;");

    QPixmap BackGroundIm(gui->getPath() + "/textures/startscreen.png");
    QPixmap StartButtonIm(gui->getPath() + "/textures/new_game_button.png");
    QPixmap SaveButtonIm(gui->LoadGameIm);
    ui->label->setPixmap(BackGroundIm);
    ui->label->setScaledContents(true);
    ui->pushButton->setIcon(QIcon(StartButtonIm));
    ui->pushButton_2->setIcon(QIcon(SaveButtonIm));
    connect(ui->pushButton, &QPushButton::clicked, this, &StartScreen::clickedNewGame);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &StartScreen::clickedSaveGame);
}

StartScreen::~StartScreen()
{
    delete ui;
}

void StartScreen::clickedNewGame()
{
    hasClicked = true;
    wantToLoadGame = false;
    gui->switchWindow();
}

void StartScreen::clickedSaveGame()
{
    hasClicked = true;
    wantToLoadGame = true;
    gui->switchWindow();
}

bool StartScreen::getWantToLoadGame() const
{
    return wantToLoadGame;
}

void StartScreen::setHasClicked(bool newHasClicked)
{
    hasClicked = newHasClicked;
}

bool StartScreen::getHasClicked() const
{
    return hasClicked;
}

