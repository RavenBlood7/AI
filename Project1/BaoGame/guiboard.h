#ifndef GUIBOARD_H
#define GUIBOARD_H

#include "board.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <sstream>

using namespace std;

class GUIBoard : public Board
{
private:
    QWidget* widget;

public:

    GUIBoard();
    GUIBoard(QWidget *w);
    void print();
};

#endif // GUIBOARD_H
