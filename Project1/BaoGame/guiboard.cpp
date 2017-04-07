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
    if (isLosingPosition())
    {
        int winner;
        if (row > 1)
            winner = 1;
        else winner = 2;
        QLabel* win= widget->findChild<QLabel*>("lblWinner");
        win->setText(QString::fromStdString("WINNER!") + QString::number(winner));
        return false;
    }
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
        stringstream find;
        find << "btn" << row << col;
        QPushButton* btn = wgtBoard->findChild<QPushButton*>(QString::fromStdString(find.str()));
        if (btn)
        {
            btn->setText(QString::number(val));            
            btn->setStyleSheet("background: blue; border: none; outline: none; color: white; max-width:41px; max-height:41px; min-width:41px; min-height:41px; border-radius:20px;");
        }
      else cout << "wgtBoard error" << endl;
}

void GUIBoard::setHand(int val)
{
      QLabel* guiHand = widget->findChild<QLabel*>("lblHand");
      guiHand->setText(QString::number(val));

}

int GUIBoard::capture(int row, int col)

{	int oppRow;
    row == 1? oppRow = 2 : oppRow = 1;
    if (board[oppRow][col] == 0 || (row == 0) || (row == 3))
        return -1;	//cannot capture
    //highlight current
    print();
    setButton(row, col, board[row][col]);
    qApp->processEvents();
    usleep(500000);

    // highlight opposite
   // print();
    //setButton(oppRow, col, board[oppRow][col]);
    //qApp->processEvents();
    //usleep(500000);

    return take(oppRow, col);
}

int GUIBoard::take(int row, int col)
{
    // highlight opposite
    print();
    setButton(row, col, board[row][col]);
    qApp->processEvents();
    usleep(500000);

    int temp = board[row][col];
    board[row][col] = 0;
    return temp;
}

void GUIBoard::possibleMoves(bool player)
{
    disableAll();
    if (player == PLAYER1)
    {
        if (isNamua())
        {
            if (isTakasa())
            {
                for (int i = 0; i < 8; i++)
                    if (board[2][i] != 0)
                        enableButton(2, i);
            }
            else    //must capture
            {
                for (int i = 0; i < 8; i++)
                    if (board[2][i] != 0 && board[1][i] != 0)
                        enableButton(2, i);
            }
        }
        else    //is mtaji
        {


        }
    }
    else
    {
        if (isNamua())
        {
            if (isTakasa())
            {
                for (int i = 0; i < 8; i++)
                    if (board[1][i] != 0)
                        enableButton(1, i);
            }
            else    //must capture
            {
                for (int i = 0; i < 8; i++)
                    if (board[2][i] != 0 && board[1][i] != 0)
                        enableButton(1, i);
            }
        }
        else    //is mtaji
        {


        }
    }
}

void GUIBoard::disableAll()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 8; j++)
            disableButton(i, j);
}

void GUIBoard::disableButton(int row, int col)
{
    QWidget* wgtBoard = widget->findChild<QWidget*>("wgtBoard");
    if (wgtBoard)
    {
        stringstream find;
        find << "btn" << row << col;
        QPushButton* btn = wgtBoard->findChild<QPushButton*>(QString::fromStdString(find.str()));
        if (btn)
        {
            btn->setEnabled(false);
        }
      }
}


void GUIBoard::enableButton(int row, int col)
{
    QWidget* wgtBoard = widget->findChild<QWidget*>("wgtBoard");
    if (wgtBoard)
    {
        stringstream find;
        find << "btn" << row << col;
        QPushButton* btn = wgtBoard->findChild<QPushButton*>(QString::fromStdString(find.str()));
        if (btn)
        {
            btn->setEnabled(true);
            btn->setStyleSheet("background: rgba(255,255,0,0.3) ; border: none; outline: none; color: white; max-width:41px; max-height:41px; min-width:41px; min-height:41px; border-radius:20px;");
        }
      }
}

