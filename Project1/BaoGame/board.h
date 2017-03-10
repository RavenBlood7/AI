#ifndef BOARD_H
#define BOARD_H
#include <sstream>

class Board
{
protected:
    int board[4][8];
	int stack1;
	int stack2;
    bool isNamuaVar;

public:
	//constants
    static const bool CLOCKWISE = true;
    static const bool ANTICLOCKWISE = false;
    static const bool PLAYER1 = false;
    static const bool PLAYER2= true;

    //functions
    Board();
    virtual bool sow(int & row, int & col, bool clockwise, int hand);
    virtual int take(int row, int col);
    virtual int capture(int row, int col); //row/col spesifies the cell capturing from

    virtual bool enterSeed(int row, int col, bool clockwise);

	bool isTakasa();
	bool isTakasaNyumba();
    virtual bool enterTakasaSeed(int row, int col, bool clockwise);
    bool isNamua();

    virtual	void print();
    virtual void possibleMoves(bool player) = 0 ;

    bool isLosingPosition();
};

#endif // BOARD_H
