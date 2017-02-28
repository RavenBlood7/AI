#ifndef BOARD_H
#define BOARD_H

class Board
{
private:
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
    bool sow(int & row, int & col, bool clockwise, int hand);
	int take(int row, int col);
	int capture(int row, int col); //row/col spesifies the cell capturing from

	bool enterSeed(int row, int col, bool clockwise);

	bool isTakasa();
	bool isTakasaNyumba();
	bool enterTakasaSeed(int row, int col, bool clockwise);
///////////
	void print();

};

#endif // BOARD_H