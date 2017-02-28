#ifndef BOARD_H
#define BOARD_H
#include <sstream>

class Board
{
protected:
    int board[4][8];
	int stack1;
	int stack2;
	bool isNamua;

public:
	//constants
	static const bool CLOCKWISE = true;
	static const bool ANTICLOCKWISE = false;
//functions
    Board();
    virtual bool sow(int & row, int & col, bool clockwise, int hand);
    virtual int take(int row, int col);
    virtual int capture(int row, int col); //row/col spesifies the cell capturing from

    virtual bool enterSeed(int row, int col, bool clockwise);

	bool isTakasa();
	bool isTakasaNyumba();
    virtual bool enterTakasaSeed(int row, int col, bool clockwise);
///////////
    virtual	void print();

};

#endif // BOARD_H
