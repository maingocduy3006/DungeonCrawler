#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <vector>

namespace Ui {
class MainWindow;
}

class Level;
class Portal;
class GraphicalUI;
class Character;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(GraphicalUI* gui, QWidget *parent = nullptr);
    ~MainWindow();

    void setButton();
    void connectButtons();

    void draw(Level* level);

    void initLevel(Level* level);
    void addFloor(QLabel* label, int row, int col);
    void addPortal(QLabel* label, Portal* port, int row, int col);

    void setInputChanged(bool status);
    bool hasInputChanged();
    char getLastInput();

    void updateCharacter();
    void updateCharacterList();

    void updatePlayerStatus(int, int, int);
    void setHitpoints(int hp);
    void setStamina(int sta);
    void setStrength(int str);

    bool checkifGameEnd(Level *level);
    void setSaveChanged(bool newSaveChanged);

    bool getSaveChanged() const;

public slots:
    void moveSlot(char move);
    void saveSlot();
private:
    Ui::MainWindow *ui;
    GraphicalUI* gui;
    QLabel* label;
    std::vector<std::vector<QLabel*>> labelField;
    std::vector<std::pair<Character*, QLabel*>> charLabelsList;
    int fieldRow;
    int fieldCol;
    bool saveChanged;
    bool inputChanged;
    char lastInput;
};

#endif // MAINWINDOW_H
