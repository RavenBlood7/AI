#ifndef GUIBOARD_H
#define GUIBOARD_H

#include "board.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <sstream>
#include <unistd.h> //for sleep function

using namespace std;

class GUIBoard : public Board
{
private:
    QWidget* widget;
    useconds_t delay;  //for how long one should sleep

public:

    GUIBoard();
    GUIBoard(QWidget *w);
    bool sow(int & row, int & col, bool clockwise, int hand);
    void print();

    void setButton(int row, int col, int val);
    void setHand(int val);
};

#endif // GUIBOARD_H
