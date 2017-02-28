#include "guiboard.h"
#include <sstream>

GUIBoard::GUIBoard()
{
}


GUIBoard::GUIBoard(QWidget *w)
{
    widget = w;
}

void GUIBoard::print()
{
    QWidget *wgtBoard;
    stringstream find;
    //update table
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            find.str("");
            find << "btn" << i << j;
            wgtBoard = widget->findChild<QWidget*>("wgtBoard");//->findChild<QPushButton*>(QString::fromStdString(find.str()))->setText(QString::number(board[i][j]));
            QPushButton* btn = wgtBoard->findChild<QPushButton*>(QString::fromStdString(find.str()));
            if (btn != NULL)
                btn->setText(QString::number(board[i][j]));
        }
    }

    //update stacks
    widget->findChild<QLabel*>("lblP1Stack")->setText(QString::number(stack1));
    widget->findChild<QLabel*>("lblP2Stack")->setText(QString::number(stack2));
}
