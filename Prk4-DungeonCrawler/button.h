#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>

namespace Ui {
class Button;
}

class Button : public QPushButton
{
    Q_OBJECT

public:
    explicit Button(char input, QWidget *parent = nullptr);

private:
    char lastInput;
public slots:
    void ButtonClicked();
signals:
    void clickButton(char input);
};

#endif // BUTTON_H
