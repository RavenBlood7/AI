#ifndef BOARD_H
#define BOARD_H

class Board
{
private:
    int board[4][8];

public:
    Board();
    bool sow(bool player1,int row, int col, bool clockwise, int hand);

///////////
	void print();

};

#endif // BOARD_H