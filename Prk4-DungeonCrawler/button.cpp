#include "button.h"

Button::Button(char input, QWidget *parent) : QPushButton(parent), lastInput(input)
{
    connect(this, &Button::clicked, this, &Button::ButtonClicked);
}

void Button::ButtonClicked()
{
    emit clickButton(lastInput);
}

