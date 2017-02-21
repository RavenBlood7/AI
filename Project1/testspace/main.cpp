#include "board.h"
#include <iostream>

using namespace std;

int main()
{
	Board b1;
	b1.print();
	
	b1.enterSeed(1, 3, b1.ANTICLOCKWISE);
	b1.print();
	

	return 0;
}