#include "mainwindow.h"
#include "dungeoncrawler.h"
#include "player.h"
#include "zombie.h"
#include "zombieattack.h"
#include "zombieguard.h"
#include "ui_mainwindow.h"
#include "graphicalui.h"
#include "button.h"
#include "portal.h"
#include "level.h"
#include "door.h"
#include "pit.h"
#include <random>
#include <QMessageBox>

MainWindow::MainWindow(GraphicalUI *gui, QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    gui(gui)
{
    ui->setupUi(this);
    ui->label_2->setStyleSheet("background-color: transparent;");
    ui->label_2->lower();
    ui->groupBox->setStyleSheet("background-color: transparent;");
    ui->label->setStyleSheet("background-color: transparent;");

    QPixmap bloodyFrame (gui->getPath() + "/textures/bloody_frame.png");

    ui->label->setPixmap(bloodyFrame);
    ui->label->setParent(this);
    ui->label->setScaledContents(true);
    ui->widget->setLayout(ui->gridLayout);
    ui->widget_2->setLayout(ui->gridLayout_2);

    ui->label->setParent(ui->groupBox);
    ui->gridLayoutWidget_2->setParent(ui->groupBox);
    ui->label->raise();
    ui->widget_2->raise();

    //Progressbar
    ui->widget_3->setStyleSheet("background-color: transparent; font-size: 25px;");
    ui->widget_3->raise();

    ui->progressBar->setTextVisible(false);
    ui->StaWertLabel->setText("2000");
    ui->StreWertLabel->setText("100");

    ui->SaveButton->raise();
    ui->SaveButton->show();
    this->connect(ui->SaveButton,SIGNAL(clicked()),this,SLOT(saveSlot()));
    initLevel(gui->getDungeonCrawler()->getLevel());
}

MainWindow::~MainWindow()
{
    delete ui;
    for(int i = 0; i < fieldRow; i++){
        for(int j = 0; j < fieldCol; j++){
            delete labelField[i][j];
        }
    }
    charLabelsList.clear();
}

void MainWindow::setButton()
{
    Button* btn1 = new Button('q', ui->widget_2);
    Button* btn2 = new Button('w', ui->widget_2);
    Button* btn3 = new Button('e', ui->widget_2);
    Button* btn4 = new Button('a', ui->widget_2);
    Button* btn5 = new Button('s', ui->widget_2);
    Button* btn6 = new Button('d', ui->widget_2);
    Button* btn7 = new Button('z', ui->widget_2);
    Button* btn8 = new Button('x', ui->widget_2);
    Button* btn9 = new Button('c', ui->widget_2);

    btn1->resize(ui->widget_2->width() / 3, ui->widget_2->height() / 3 );
    btn2->resize(ui->widget_2->width() / 3, ui->widget_2->height() / 3);
    btn3->resize(ui->widget_2->width() / 3, ui->widget_2->height() / 3);
    btn4->resize(ui->widget_2->width() / 3, ui->widget_2->height() / 3);
    btn5->resize(ui->widget_2->width() / 3, ui->widget_2->height() / 3);
    btn6->resize(ui->widget_2->width() / 3, ui->widget_2->height() / 3);
    btn7->resize(ui->widget_2->width() / 3, ui->widget_2->height() / 3);
    btn8->resize(ui->widget_2->width() / 3, ui->widget_2->height() / 3);
    btn9->resize(ui->widget_2->width() / 3, ui->widget_2->height() / 3);

    ui->gridLayout_2->addWidget(btn1,0,0,Qt::AlignCenter);
    ui->gridLayout_2->addWidget(btn2,0,1,Qt::AlignCenter);
    ui->gridLayout_2->addWidget(btn3,0,2,Qt::AlignCenter);
    ui->gridLayout_2->addWidget(btn4,1,0,Qt::AlignCenter);
    ui->gridLayout_2->addWidget(btn5,1,1,Qt::AlignCenter);
    ui->gridLayout_2->addWidget(btn6,1,2,Qt::AlignCenter);
    ui->gridLayout_2->addWidget(btn7,2,0,Qt::AlignCenter);
    ui->gridLayout_2->addWidget(btn8,2,1,Qt::AlignCenter);
    ui->gridLayout_2->addWidget(btn9,2,2,Qt::AlignCenter);

    QPixmap im1(gui->getPath() + "/textures/arrows/arrow_up_left.png");
    QPixmap im2(gui->getPath() + "/textures/arrows/arrow_up.png");
    QPixmap im3(gui->getPath() + "/textures/arrows/arrow_up_right.png");
    QPixmap im4(gui->getPath() + "/textures/arrows/arrow_left.png");
    QPixmap im5(gui->getPath() + "/textures/arrows/arrow_skip.png");
    QPixmap im6(gui->getPath() + "/textures/arrows/arrow_right.png");
    QPixmap im7(gui->getPath() + "/textures/arrows/arrow_down_left.png");
    QPixmap im8(gui->getPath() + "/textures/arrows/arrow_down.png");
    QPixmap im9(gui->getPath() + "/textures/arrows/arrow_down_right.png");

    QIcon icon1(im1);
    QIcon icon2(im2);
    QIcon icon3(im3);
    QIcon icon4(im4);
    QIcon icon5(im5);
    QIcon icon6(im6);
    QIcon icon7(im7);
    QIcon icon8(im8);
    QIcon icon9(im9);

    btn1->setIcon(icon1);
    btn2->setIcon(icon2);
    btn3->setIcon(icon3);
    btn4->setIcon(icon4);
    btn5->setIcon(icon5);
    btn6->setIcon(icon6);
    btn7->setIcon(icon7);
    btn8->setIcon(icon8);
    btn9->setIcon(icon9);

    btn1->setIconSize( btn1->size() );
    btn2->setIconSize( btn2->size() );
    btn3->setIconSize( btn3->size() );
    btn4->setIconSize( btn4->size() );
    btn5->setIconSize( btn5->size() );
    btn6->setIconSize( btn6->size() );
    btn7->setIconSize( btn7->size() );
    btn8->setIconSize( btn8->size() );
    btn9->setIconSize( btn9->size() );

    btn1->setStyleSheet("border:none");
    btn2->setStyleSheet("border:none");
    btn3->setStyleSheet("border:none");
    btn4->setStyleSheet("border:none");
    btn5->setStyleSheet("border:none");
    btn6->setStyleSheet("border:none");
    btn7->setStyleSheet("border:none");
    btn8->setStyleSheet("border:none");
    btn9->setStyleSheet("border:none");
}

void MainWindow::connectButtons()
{
    connect(qobject_cast<Button*>(ui->gridLayout_2->itemAtPosition(0,0)->widget()), &Button::clickButton, this, &MainWindow::moveSlot);
    connect(qobject_cast<Button*>(ui->gridLayout_2->itemAtPosition(0,1)->widget()), &Button::clickButton, this, &MainWindow::moveSlot);
    connect(qobject_cast<Button*>(ui->gridLayout_2->itemAtPosition(0,2)->widget()), &Button::clickButton, this, &MainWindow::moveSlot);
    connect(qobject_cast<Button*>(ui->gridLayout_2->itemAtPosition(1,0)->widget()), &Button::clickButton, this, &MainWindow::moveSlot);
    connect(qobject_cast<Button*>(ui->gridLayout_2->itemAtPosition(1,1)->widget()), &Button::clickButton, this, &MainWindow::moveSlot);
    connect(qobject_cast<Button*>(ui->gridLayout_2->itemAtPosition(1,2)->widget()), &Button::clickButton, this, &MainWindow::moveSlot);
    connect(qobject_cast<Button*>(ui->gridLayout_2->itemAtPosition(2,0)->widget()), &Button::clickButton, this, &MainWindow::moveSlot);
    connect(qobject_cast<Button*>(ui->gridLayout_2->itemAtPosition(2,1)->widget()), &Button::clickButton, this, &MainWindow::moveSlot);
    connect(qobject_cast<Button*>(ui->gridLayout_2->itemAtPosition(2,2)->widget()), &Button::clickButton, this, &MainWindow::moveSlot);
}

void MainWindow::draw(Level *level)
{
    if(gui->getDungeonCrawler()->getIsChangedLevel()){

        for(int i=0; i < fieldRow; i++){
            for (int j=0; j < fieldCol;j++){
                delete labelField[i][j];
                charLabelsList.clear();
                delete ui->gridLayout->itemAtPosition(i,j);
            }
        }
        this->initLevel(level);
        gui->getDungeonCrawler()->setIsChangedLevel(false);
    }
    updateCharacterList();
    int row = fieldRow = level->getBreite()+2;
    int col = fieldCol =level->getHohe()+2;
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            Tile* tile = level->getTile(i,j);

            if(tile->hasCharacter())
            {
                updateCharacter();
            }

            if(typeid(*tile) == typeid(Door))
            {
                Door* door = dynamic_cast<Door*>(tile);
                QLabel* doorLabel = labelField.at(i).at(j);
                if(door->getisOpend()){
                    doorLabel->setPixmap(gui->doors[1]);
                } else{
                    doorLabel->setPixmap(gui->doors[0]);
                }
            }
        }
    }
}

void MainWindow::initLevel(Level* level)
{
    //auto level = gui->getDungeonCrawler()->getLevel();
    int row = level->getBreite()+2;
    int col = level->getHohe()+2; // =12
    /*if(row == 12 && col == 12){
        labelField.resize(12, std::vector<QLabel*>(12));
    }
    else{
        labelField.resize(row, std::vector<QLabel*>(col));
    }*/
    //labelField.resize(row, std::vector<QLabel*>(col));
    labelField.resize(12, std::vector<QLabel*>(12));
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            label = new QLabel(ui->widget);
            Tile* tile = level->getTile(i,j);
            if(tile->getTexture() == "Floor"){
                addFloor(label,i,j);
            }
            if(tile->getTexture() == "Wall"){
                label->setPixmap(gui->WallIm);
                labelField.at(i).at(j) = label;
                ui->gridLayout->addWidget(label,i,j,Qt::AlignCenter);
            }
            if(tile->getTexture() == "Portal"){
                auto port = dynamic_cast<Portal*>(tile);
                addPortal(label,port,i,j);
            }
            if(tile->getTexture() == "CloseDoor"){
                label->setPixmap(gui->doors[0]);
                labelField.at(i).at(j) = label;
                ui->gridLayout->addWidget(label,i,j,Qt::AlignCenter);
            }
            if(tile->getTexture() == "OpenDoor"){
                label->setPixmap(gui->doors[1]);
                labelField.at(i).at(j) = label;
                ui->gridLayout->addWidget(label,i,j,Qt::AlignCenter);
            }
            if(tile->getTexture() == "Switch"){
                label->setPixmap(gui->SwichtIm);
                labelField.at(i).at(j) = label;
                ui->gridLayout->addWidget(label,i,j,Qt::AlignCenter);
            }
            if(tile->getTexture() == "Pit"){
                label->setPixmap(gui->PitIm);
                labelField.at(i).at(j) = label;
                ui->gridLayout->addWidget(label,i,j,Qt::AlignCenter);
            }
            if(tile->getTexture() == "Ramp"){
                label->setPixmap(gui->RampIm);
                labelField.at(i).at(j) = label;
                ui->gridLayout->addWidget(label,i,j,Qt::AlignCenter);
            }
            if(tile->getTexture() == "Levelchanger"){
                label->setPixmap(gui->LevelChangerIm);
                labelField.at(i).at(j) = label;
                ui->gridLayout->addWidget(label,i,j,Qt::AlignCenter);
            }
            if(tile->getTexture() == "Chest"){
                label->setPixmap(gui->ChestIm);
                labelField.at(i).at(j) = label;
                ui->gridLayout->addWidget(label,i,j,Qt::AlignCenter);
            }
            if(tile->hasCharacter())
            {
                QLabel* character = new QLabel(labelField.at(i).at(j));
                //QPixmap charIm;
                if(tile->getCharacter()->getTexture() == "Player"){
                    //charIm = gui->chars[1][1];
                    character->setPixmap(gui->chars[1][1]);
                    ui->progressBar->setMaximum(tile->getCharacter()->getHitpoints());
                }
                else{
                    //charIm = gui->zombies[1];
                    character->setPixmap(gui->zombies[1]);
                }
                //charIm.scaled(labelField.at(i).at(j)->width(), labelField.at(i).at(j)->height(), Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation);
                //character->setPixmap(charIm);
                character->setScaledContents(true);
                character->setStyleSheet("background-color: transparent;");
                character->resize(labelField.at(i).at(j)->width()+1,labelField.at(i).at(j)->height()+10);
                character->show();
                charLabelsList.push_back(std::make_pair(tile->getCharacter(),character));
                ui->gridLayout->addWidget(character,i,j,Qt::AlignCenter);
            }
            label->setScaledContents(true);
            label->setMaximumHeight(ui->widget->height() / row );
            label->setMaximumWidth(ui->widget->width() / col );
        }
    }

}

void MainWindow::addFloor(QLabel* label, int row, int col)
{
    std::random_device dev;
    std::mt19937 rd(dev());
    std::uniform_int_distribution<int> dis(0,4);
    int i = dis(rd);

    label->setPixmap(gui->floors[i]);
    labelField.at(row).at(col) = label;
    ui->gridLayout->addWidget(label,row,col,Qt::AlignCenter);
}

void MainWindow::addPortal(QLabel* label, Portal* port, int row, int col)
{
    int typePort = port->getTypePortal();
    label->setPixmap(gui->portals[typePort]);
    labelField.at(row).at(col) = label;
    ui->gridLayout->addWidget(label,row,col,Qt::AlignCenter);
}

void MainWindow::setInputChanged(bool status)
{
    inputChanged = status;
}

bool MainWindow::hasInputChanged()
{
    return inputChanged;
}

char MainWindow::getLastInput()
{
    return lastInput;
}

void MainWindow::updateCharacter()
{
    std::random_device dev;
    std::mt19937 rd(dev());
    for(auto pair : charLabelsList){
        Character* character = pair.first;
        QLabel* characterLabel = pair.second;
        if(typeid(*character) == typeid(Player)){
            Tile* tile = character->getTile();
            auto i = tile->getRow();
            auto j = tile->getCol();
            std::uniform_int_distribution<std::mt19937::result_type> dis(0,2);

            char moveDirection = tile->getCharacter()->getMoveDirection();
            characterLabel->setParent(labelField.at(i).at(j));
            characterLabel->move(QPoint(0,0));
            switch(moveDirection)
            {
            case 'q':
            case 'a':
            case 'z':
            {
                characterLabel->setPixmap(gui->chars[2][dis(rd)]);
                break;
            }
            case 'w':
            {
                characterLabel->setPixmap(gui->chars[1][dis(rd)]);
                break;
            }
            case 'x':
            {
                characterLabel->setPixmap(gui->chars[0][dis(rd)]);
                break;
            }
            case 'e':
            case 'd':
            case 'c':
            {
                characterLabel->setPixmap(gui->chars[3][dis(rd)]);
                break;
            }
            }
            if(typeid(*tile) == typeid(Pit)){
                labelField.at(i).at(j)->setStyleSheet("background-color: transparent;");
                labelField.at(i).at(j)->raise();

                characterLabel->setParent(this);
                characterLabel->move(ui->gridLayoutWidget->pos() + labelField.at(i).at(j)->pos()+ QPoint(20, 100));
                characterLabel->lower();
            }
            characterLabel->show();
            updatePlayerStatus(character->getHitpoints(), character->getStamina(), character->getStrength());
        }
        else if(typeid(*character) == typeid(Zombie)||typeid(*character) == typeid(ZombieGuard)||typeid(*character) == typeid(ZombieAttack)){
            Tile* tile = character->getTile();
            auto i = tile->getRow();
            auto j = tile->getCol();
            char moveDirection = tile->getCharacter()->getMoveDirection();
            characterLabel->setParent(labelField.at(i).at(j));
            characterLabel->move(QPoint(0,0));
            switch(moveDirection)
            {
            case 'q':
            case 'a':
            case 'z':
            case 'w':
            {
                characterLabel->setPixmap(gui->zombies[0]);
                break;
            }
            case 'x':
            case 'e':
            case 'd':
            case 'c':
            {
                characterLabel->setPixmap(gui->zombies[1]);
                break;
            }
            }
            if(typeid(*tile) == typeid(Pit)){
                labelField.at(i).at(j)->setStyleSheet("background-color: transparent;");
                labelField.at(i).at(j)->raise();

                characterLabel->setParent(this);
                characterLabel->move(ui->gridLayoutWidget->pos() + labelField.at(i).at(j)->pos()+ QPoint(20, 100));
                characterLabel->lower();
            }
            characterLabel->show();
        }
    }
}

void MainWindow::updateCharacterList()
{
    for(auto pair : charLabelsList){
        if(!pair.first->getisAlive()){
            delete pair.second;
            charLabelsList.erase(std::remove(charLabelsList.begin(), charLabelsList.end(), pair), charLabelsList.end());
        }
    }
}

void MainWindow::updatePlayerStatus(int hp, int sta, int str)
{
    setHitpoints(hp);
    setStamina(sta);
    setStrength(str);
}

void MainWindow::setHitpoints(int hp)
{
    ui->progressBar->setValue(hp);
}

void MainWindow::setStamina(int sta)
{
    ui->StaWertLabel->setText(QString::fromStdString(std::to_string(sta)));
}

void MainWindow::setStrength(int str)
{
    ui->StreWertLabel->setText(QString::fromStdString(std::to_string(str)));
}

bool MainWindow::checkifGameEnd(Level *level)
{
    if(level->hasPlayerWin()){
        QMessageBox::information(this,tr("Congratulation"),tr("Thanks for playing"));
        return true;
    }
    if(level->hasPlayerLose()){
        QMessageBox::information(this,tr("Opps"),tr("You have lost!"));
        return true;
    }
    return false;
}

void MainWindow::moveSlot(char move)
{
    lastInput=move;
    inputChanged=true;
}

void MainWindow::saveSlot()
{
    auto Qpath = gui->getPath() + "/levelsavedatei.txt";
    std::string path = Qpath.toStdString();
    gui->getDungeonCrawler()->WriteFile(path);
    QMessageBox::information(this,tr("Mittelung"),tr("Game saved!"));
    saveChanged=true;
}

bool MainWindow::getSaveChanged() const
{
    return saveChanged;
}

void MainWindow::setSaveChanged(bool newSaveChanged)
{
    saveChanged = newSaveChanged;
}
