/**
*	@file guiboard.h
*	@class GUIBoard
*
*	@brief gui interface
*
*	@section Description
*   Uses functionality of Board class and displays it with the widget
*
*	@section License
*	Copyright belongs to Juan du Preez (15189016)
*
*/

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
    QWidget* widget; /**< used for displaying buttons and labels*/
    useconds_t delay;  /**< doesn't work: for usleep() function*/

    void disableButton(int row, int col); /**< disables single button*/
    void enableButton(int row, int col); /**< enables single button*/
public:

    GUIBoard();
    GUIBoard(QWidget *w);
    bool sow(int & row, int & col, bool clockwise, int hand);
    void print(); /**< updates widget with current values*/

    void setButton(int row, int col, int val); /**< sets single button with single value*/
    void setHand(int val); /**< updates hand label with current hand value*/

    int capture(int row, int col);/**< captures opposite seeds if possible. returns -1 if not*/
    int take(int row, int col); /**< removes from single cell in board*/

    void possibleMoves(bool player);/**< makes yellow circles around possible moves*/
    void disableAll();  /**< disables all buttons*/
};

#endif // GUIBOARD_H
