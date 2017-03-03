#include "guiboard.h"
#include <sstream>
/////can remove this later for cout
#include <iostream>
#include <QApplication>
using namespace std;

GUIBoard::GUIBoard()
{
    delay = 1;
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
            {
                btn->setText(QString::number(board[i][j]));
                btn->setStyleSheet("background: transparent; border: none; outline: none; color: white; border-radius:50px;");
            }
        }
    }

    //update stacks
    widget->findChild<QLabel*>("lblP1Stack")->setText(QString::number(stack1));
    widget->findChild<QLabel*>("lblP2Stack")->setText(QString::number(stack2));
}

bool GUIBoard::sow(int & row, int & col, bool clockwise, int hand)
{
    print();
    setHand(hand);
    qApp->processEvents();
    usleep(500000);

    int topRow;
    if (row > 1)
        topRow = 2;
    else topRow = 0;

    //enter seed
    board[row][col]++;
    print();
    setButton(row, col, board[row][col]);
    qApp->processEvents();
    usleep(500000);

    //take from hand
    hand--;
    print();
    setHand(hand);
    qApp->processEvents();
    usleep(500000);

    while (hand)
    {
        if (row == topRow)
            clockwise ? col++ : col--;
        else
            clockwise ? col-- : col++;
        if (col > 7)
        {
            col = 7;
            clockwise? row = topRow + 1 : row = topRow;
        }
        else if (col < 0)
        {
            col = 0;
            clockwise? row = topRow : row = topRow + 1;
        }

        //sow into hole
        board[row][col]++;
        print();
        setButton(row, col, board[row][col]);
        qApp->processEvents();
        usleep(500000);

        //update hand
        hand--;
        print();
        setHand(hand);
        qApp->processEvents();
        usleep(500000);
    }
    return board[row][col] == 1;
}

void GUIBoard::setButton(int row, int col, int val)
{
    QWidget* wgtBoard = widget->findChild<QWidget*>("wgtBoard");
//    if (wgtBoard)
 //   {
        stringstream find;
        find << "btn" << row << col;
        QPushButton* btn = wgtBoard->findChild<QPushButton*>(QString::fromStdString(find.str()));
        if (btn)
        {
            btn->setText(QString::number(val));            
            btn->setStyleSheet("background: blue; border: none; outline: none; color: white; max-width:41px; max-height:41px; min-width:41px; min-height:41px; border-radius:20px;");
        }
        ///////////
 //             else cout << "button error" << endl;
 //   }
    ///////////
 //         else cout << "wgtBoard error" << endl;
}

void GUIBoard::setHand(int val)
{
      QLabel* guiHand = widget->findChild<QLabel*>("lblHand");
     // if (guiHand)
          guiHand->setText(QString::number(val));
///////////
     // else cout << "hand error" << endl;
}
