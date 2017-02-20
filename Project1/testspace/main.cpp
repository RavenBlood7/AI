#include "board.h"
#include <iostream>

using namespace std;

int main()
{
	Board b1;
	b1.print();
	
	cout << "verdict: " << b1.sow(1, 2, 0, 1, 8);
	b1.print();
	
	cout << "verdict: " << b1.sow(1, 3, 7, 1, 8);
	b1.print();
	
	cout << "verdict: " << b1.sow(0, 0, 7, 0, 4);
	b1.print();
	return 0;
}