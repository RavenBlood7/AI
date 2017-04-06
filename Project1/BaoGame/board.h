/**
*	@file baord.h
*	@class Board
*
*	@brief the main area of play in the game
*
*	@section Description
*   Most of the game functionality is in this class including the sowing of the seeds and seeds themselves.
*
*	@section License
*	Copyright belongs to Juan du Preez (15189016)
*
*/

#ifndef BOARD_H
#define BOARD_H
#include <sstream>

class Board
{
protected:
    int board[4][8];    /**< the main 4 x 8 board in which seeds are sown*/
    int stack1;         /**< the initial stack of player 1*/
    int stack2;         /**< the initial stack of player 2*/
    bool isNamuaVar;

    virtual bool sow(int & row, int & col, bool clockwise, int hand); /**< helper function: has sow around functionality*/
    virtual int take(int row, int col); /**< helper function: takes seeds*/
    virtual int capture(int row, int col); /**< helper function: captures the row opposite row and col*/

public:
    static const bool CLOCKWISE = true;
    static const bool ANTICLOCKWISE = false;
    static const bool PLAYER1 = false;
    static const bool PLAYER2= true;

    Board();
    Board(const Board &other); /**< Copy constructor*/
    virtual ~Board(){ };

    virtual bool enterSeed(int row, int col, bool clockwise);   /**< Namua entering a seed functionality*/
    virtual bool enterTakasaSeed(int row, int col, bool clockwise); /**< Namua Takasa situation functionality*/
    virtual bool makeMtajiMove(int row, int col, int clockwise);

    bool isMtajiMove(int row, int col, int clockwise);
    bool isTakasa();        /**< returns true if no captures are possible*/
    bool isTakasaNyumba();  /**< returns true if in Takasa and landed in house*/
    bool isNamua();         /**< returns true if there are still seeds left off the board*/
    bool isLosingPosition();/**< returns true if a player has lost the game*/
    bool isEmpty(int row, int col);

    virtual	void print();   /**< outputs the board and stack variables*/
    virtual void possibleMoves(bool player) {if (player){}}; /**< find out which moves are possible with regards to player*/

};

#endif // BOARD_H
